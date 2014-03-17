//
//  System.c++
//  Tech1
//
//  Created by Justin Hust on 12/18/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>

#include "System.h"
#include "Clock.h"
#include "Environment.h"
#include "Resource.h"
#include "Parser.h"

#include <cassert>

// ------------------------------------------
System::System(void) {
  _clock = new SDLClock();
  _resMgr = new ResourceMgr();

}

// ------------------------------------------
System::~System(void) {
  delete _clock;
  _clock = NULL;
  
  delete _resMgr;
  _resMgr = NULL;

}

// ------------------------------------------
void System::init(int w, int h) {
  // -------- SDL -----------
  std::string sInitMsg = "System init...";
  _rpt.system(sInitMsg);

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    char err[80];
    snprintf(err, 80, "Failed SDL Init: %s.\n", SDL_GetError());
    _rpt.system(err);
    
  }
  
  _rpt.system("OK.\n");
  
  
  // ------- VIDEO -----------
  char chVideoInitMsg[80];
  snprintf(chVideoInitMsg, 80, "Video init %dx%d...", w, h);
  
  sInitMsg = chVideoInitMsg;
    
  _rpt.video(sInitMsg);
  
  SDL_Window *sdlWindow = NULL;
  if((sdlWindow = SDL_CreateWindow("Tech1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                w, h, SDL_WINDOW_SHOWN)) == NULL) {
    char err[80];
    snprintf(err, 80, "Failed Window Init: %s.\n", SDL_GetError());
    _rpt.video(err);
    
  }
  
  SDL_Surface *windowSurf = SDL_GetWindowSurface(sdlWindow);

  assert(windowSurf != NULL);

  _screen = windowSurf;
  _sdlWindow = sdlWindow;
  
  _rpt.video("OK.\n");

  // ------------------
  sInitMsg = "Audio init...";
  
  _rpt.audio(sInitMsg);

  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  assert(audioInitResult != -1);

  _rpt.audio("OK.\n");

}

// ------------------------------------------
void System::shutdown(void) {
  Mix_CloseAudio();
  SDL_Quit();

}

// ------------------------------------------
void System::setScreen(SDL_Surface *toSurf) {
  _screen = toSurf;

}

// ------------------------------------------
void System::presentScreen(void) {
  assert(_sdlWindow != NULL);

  SDL_UpdateWindowSurface(_sdlWindow);

}

// ------------------------------------------
AbstractClock * System::clock(void) {
  return _clock;

}

// ------------------------------------------
Environment & System::env(void) {
  return _envSys;
  
}

// ------------------------------------------
Resource * System::Register(const std::string &sPathKey) {
  std::string sMsg = "Register ";
  sMsg += sPathKey;
  sMsg += "\n";

  _rpt.resources(sMsg);
  
  return _resMgr->Register(sPathKey);

}

// ------------------------------------------
SpriteResource * System::RegisterSprite(const std::string &sSpriteKey, const std::string &sImgKey, 
                                        unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
   
  std::string sMsg = "RegisterSprite ";
  sMsg += sSpriteKey;
  sMsg += ", ";
  sMsg += sImgKey;
  sMsg += "\n";

  _rpt.resources(sMsg);
  
  return _resMgr->RegisterSprite(sSpriteKey, sImgKey, x1, y1, x2, y2);
                               
}

// ------------------------------------------
void System::unregister(const std::string &sPathKey) {
  std::string sMsg = "unregister ";
  sMsg += sPathKey;
  sMsg += "\n";

  _rpt.resources(sMsg);

  _resMgr->unregister(sPathKey);

}

// ------------------------------------------
void System::draw(const std::string &sPathKey, float x, float y) {
  assert(_screen != NULL);

  ImageResource *img = dynamic_cast<ImageResource *>(_resMgr->get(sPathKey));
  img->draw(x, y, _screen);

}

// ------------------------------------------
void System::playSound(const std::string &sPathKey) {
  std::string sMsg = "playSound ";
  sMsg += sPathKey;
  sMsg += "\n";
  
  _rpt.audio(sMsg);
  
  _resMgr->PlaySound(sPathKey);

}

// ------------------------------------------
ScriptInstance * System::createScriptInstance(const std::string &sPathKey) {
  std::string sMsg = "createScriptInstance ";
  sMsg += sPathKey;
  sMsg += "\n";
  
  _rpt.scripting(sMsg);
  

  ScriptResource *scr = dynamic_cast<ScriptResource *>( _resMgr->get(sPathKey) );
  assert(scr != NULL);

  ScriptInstance *scrInst = scr->createInstance(*this, (*_rpt.getScripting())  );
  assert(scrInst != NULL);
  
  if(scrInst->hasFunction("__init__"))
    scrInst->call("__init__");

  return scrInst;
  
}

// ------------------------------------------
std::ostream * System::getScriptingChannel(void) {
  return _rpt.getScripting();

}

// ------------------------------------------
void System::exec(const std::string &sCode) {
  std::istringstream iss(sCode);
  
  Parser p;
  Token *tokCode = p.parse(iss);

  Environment env;
  tokCode->execute(env, *this, *(this->getScriptingChannel()));

}

// ------------------------------------------
