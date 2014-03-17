//
//  TestScript.c++
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
#include "stdlib.h"

#include "SDL2/SDL.h"
#include "SDL2_mixer/SDL_mixer.h"

#include "Clock.h"
#include "Token.h"
#include "Parser.h"
#include "Resource.h"
#include "Reporter.h"
#include "Environment.h"
#include "System.h"
#include <sstream>

const int resWidth = 1136;
const int resHeight = 640;

// -----------------------------------------------------------------
int main(int argc, char *argv[]) {
  Reporter rpt;
  
  // --- init ----
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    char err[80];
    snprintf(err, 80, "Failed Window Init: %s.\n", SDL_GetError());
    rpt.fatalError(err);
    
  }
  
  SDL_Window *sdlWindow = NULL;
  if((sdlWindow = SDL_CreateWindow("Tech1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                resWidth, resHeight, SDL_WINDOW_SHOWN)) == NULL) {
    char err[80];
    snprintf(err, 80, "Failed Window Init: %s.\n", SDL_GetError());
    rpt.fatalError(err);
    
  }
  
  SDL_Surface *windowSurf = SDL_GetWindowSurface(sdlWindow);
 
 
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  assert(audioInitResult != -1);


  Environment envLocal;
  System sys;
    sys.setScreen(windowSurf);
    sys.Register("images/bullet.png");
    sys.Register("sounds/menu_enter.wav");
    sys.Register("sounds/explodelow.wav");
  std::ostringstream oss;
  
  
  Parser p1;
  std::istringstream issDraw("(draw \"images/bullet.png\" 300.0 200.0)");
  Token *tokDraw = p1.parse(issDraw);
  
  Parser p2;
  std::istringstream issPlaySound("(playsound \"sounds/menu_enter.wav\")");
  Token *tokPlaySound = p2.parse(issPlaySound);
  
  Parser p3;
  std::istringstream issPlaySound2("(playsound \"sounds/explodelow.wav\")");
  Token *tokPlaySound2 = p3.parse(issPlaySound2);
  
  
  tokPlaySound->execute(envLocal, sys, oss);
  
  float fSoundTimer = 0.0f;
  
  // ----- main code ------
  while(sys.clock()->getSecsElapsed() < 8.0f) {
    sys.clock()->tick();
    
    tokDraw->execute(envLocal, sys, oss);
    
    fSoundTimer += sys.clock()->getFrameSecs();
    if(fSoundTimer > 3.0f) {
      fSoundTimer = 0.0f;
      tokPlaySound2->execute(envLocal, sys, oss);
    
    }
  
    SDL_UpdateWindowSurface(sdlWindow);

  }
  
  // ----------------------
  sys.unregister("sounds/explodelow.wav");
  sys.unregister("images/bullet.png");
  
  // --- cleanup ----
  SDL_FreeSurface(windowSurf);
  windowSurf = NULL;
  
  SDL_DestroyWindow(sdlWindow);
  sdlWindow = NULL;
  
  SDL_Quit();
  return 0;

}