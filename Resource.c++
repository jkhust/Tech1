//
//  Resource.cpp
//  AI_Demo1
//
//  Created by Justin Hust on 7/13/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "Resource.h"
#include "Parser.h"
#include "Util.h"
#include "Script.h"

// -----------------------------------------------------------
Resource::Resource(const std::string &sAbsPath) {
  _sAbsPath = sAbsPath;

}

// -----------------------------------------------------------
Resource::~Resource(void) {
  // no cleanup code yet.

}


// -----------------------------------------------------------
ImageResource::ImageResource(const std::string &sAbsPath) : Resource(sAbsPath) {
  assert( sAbsPath != "" );
  _surf = NULL;

}

// -----------------------------------------------------------
ImageResource::~ImageResource(void) {
  assert(_surf != NULL);

  SDL_FreeSurface(_surf);
  _surf = NULL;

}

// -----------------------------------------------------------
void ImageResource::load(void) {
  _surf = IMG_Load(_sAbsPath.c_str());
  
  assert(_surf != NULL);
  
  // create optimized image based on screen format
//  SDL_Surface *surfOptimized = SDL_DisplayFormatAlpha(_surf);
//  SDL_FreeSurface(_surf);
//  
//  _surf = surfOptimized;
//
//  assert(_surf != NULL);
  
}


// -----------------------------------------------------------
unsigned int ImageResource::getWidth(void) const {
  assert(_surf);
  
  return _surf->w;
  
}


// -----------------------------------------------------------
unsigned int ImageResource::getHeight(void) const {
  assert(_surf);
  
  return _surf->h;
  
} 

// -----------------------------------------------------------
// get back color.  used for sprite sheets.
// http://sdl.beuc.net/sdl.wiki/SDL_PixelFormat
//
unsigned int ImageResource::getBackColor(void) const {
  assert(_surf != NULL);
  
  SDL_LockSurface(_surf);
  
  unsigned int topLeftPixel = *((unsigned int *)_surf->pixels);

  SDL_UnlockSurface(_surf);

  return topLeftPixel;
  
} 

// -----------------------------------------------------------
void ImageResource::draw(unsigned int x, unsigned int y, SDL_Surface *toSurf) const {
  assert(_surf != NULL);
  assert(toSurf != NULL);
  
  // use enter src
  SDL_Rect srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = _surf->w;
  srcRect.h = _surf->h;
  
  SDL_Rect destRect;
  destRect.w = srcRect.w;
  destRect.h = srcRect.h;
  destRect.x = x - (destRect.w / 2);
  destRect.y = y - (destRect.h / 2);
  
  SDL_BlitSurface(_surf, &srcRect, toSurf, &destRect);
  
}

// -----------------------------------------------------------
SDL_Surface * ImageResource::getSurface(void) const {
  return _surf;
  
}

// -----------------------------------------------------------
SpriteResource::SpriteResource(ImageResource *fromImage, 
                               unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) 
                              : Resource("") {
  assert(fromImage != NULL);
  
  _fromImage = fromImage;
  
  _x1 = x1;
  _y1 = y1;
  _x2 = x2;
  _y2 = y2;
  
}

// -----------------------------------------------------------
SpriteResource::~SpriteResource(void) {
  // no cleanup code yet.
  
}

// -----------------------------------------------------------
void SpriteResource::draw(unsigned int x, unsigned int y, SDL_Surface *toSurf) const {  
  // use sprite coords from surf
  SDL_Rect srcRect;
  srcRect.x = _x1;
  srcRect.y = _y1;
  srcRect.w = this->getWidth();
  srcRect.h = this->getHeight();
  
  // destination will be the same dimensions
  SDL_Rect destRect;
  destRect.w = srcRect.w;
  destRect.h = srcRect.h;
  destRect.x = x - (destRect.w / 2);
  destRect.y = y - (destRect.h / 2);
  
  SDL_BlitSurface(_fromImage->getSurface(), &srcRect, toSurf, &destRect);

}

// -----------------------------------------------------------
unsigned int SpriteResource::getWidth(void) const {
  return( _x2 - _x1 + 1);
  
}

// -----------------------------------------------------------
unsigned int SpriteResource::getHeight(void) const {
  return( _y2 - _y1 + 1);
  
}

// -----------------------------------------------------------
SoundResource::SoundResource(const std::string & sAbsPath) : Resource(sAbsPath) {
  assert(sAbsPath != "");
  _chunk = NULL;

}

// -----------------------------------------------------------
SoundResource::~SoundResource(void) {
  if(_chunk) {
    Mix_FreeChunk(_chunk);
    _chunk = NULL;
    
  }
  
}

// -----------------------------------------------------------
void SoundResource::load(void) {
  _chunk = Mix_LoadWAV(_sAbsPath.c_str());
  
  assert(_chunk);
  
}

// -----------------------------------------------------------
void SoundResource::play(void) {
  assert(_chunk);

  Mix_PlayChannel( -1, _chunk, 0 );

}

// -----------------------------------------------------------
MusicResource::MusicResource(const std::string &sAbsPath) : Resource(sAbsPath) {
  _music = NULL; 
  
}

// -----------------------------------------------------------
MusicResource::~MusicResource(void) {
  assert(_music != NULL);
  
  Mix_FreeMusic(_music);

}

// -----------------------------------------------------------
void MusicResource::load(void) {
  _music = Mix_LoadMUS(_sAbsPath.c_str());
  
  assert(_music);

}

// -----------------------------------------------------------
void MusicResource::play(void) {
  // if( Mix_PlayingMusic() == 0 ) { //Play the music if( Mix_PlayMusic( music, -1 ) == -1 ) { return 1; } } 

  Mix_PlayMusic( _music, -1 );
  
}

// -----------------------------------------------------------
void MusicResource::stop(void) {
  // unimplemented.
  
}

// -----------------------------------------------------------
void MusicResource::pause(void) {
  // unimplemented.
  
}

// -----------------------------------------------------------
void MusicResource::resume(void) {
   // unimplemented.
  
}

// -----------------------------------------------------------
ScriptResource::ScriptResource(const std::string &sAbsPath) : Resource(sAbsPath) {
  _tokCode = NULL;
  
}

// -----------------------------------------------------------
ScriptResource::~ScriptResource(void) {
  // TODO: fix mem leak here
  _tokCode = NULL;

}

// -----------------------------------------------------------
void ScriptResource::load(void) {
  std::ifstream ifs(_sAbsPath.c_str());
  
  Parser p;
  _tokCode = p.parse(ifs);

  assert(_tokCode != NULL);

}

// -----------------------------------------------------------
ScriptInstance * ScriptResource::createInstance(System &sys, std::ostream &os) const {
  ScriptInstance *si = new ScriptInstance( dynamic_cast<ScriptToken *>( _tokCode), sys, os );
  return si;

}
  
// -----------------------------------------------------------
ResourceMgr::ResourceMgr(void) {
  _sBasePath = "/Users/jkhust/Documents/Coding/Tech1/Tech1/Resources";

}

// -----------------------------------------------------------
Resource * ResourceMgr::Register(const std::string &sPathKey) {
  std::string sFilePath = _sBasePath + "/" + sPathKey;

  // make lowercase
  std::string sExt4 = sPathKey.substr(sPathKey.length() - 4);
  std::string sExt8 = sPathKey.substr(sPathKey.length() - 8);

  // allocate the new resource
  Resource * resNew = NULL;
  
  if(sExt4 == ".PNG" || sExt4 == ".png") {
    resNew = new ImageResource(sFilePath);

  } else if(sExt8 == ".MUS.WAV" || sExt8 == ".mus.wav") {
    resNew = new MusicResource(sFilePath);

  } else if(sExt4 == ".WAV" || sExt4 == ".wav") {
     resNew = new SoundResource(sFilePath);
  
  } else if(sExt4 == ".SCR" || sExt4 == ".scr") {
     resNew = new ScriptResource(sFilePath);
      
  } else {
    assert("Unknown resource type.");
    //sys.Report(CHAN_RESOURCES, "Unknown resource type!");
    
  }
  
  assert(resNew);
  resNew->load();
  
  _resources.insert( std::make_pair(sPathKey, resNew) );
  
  return resNew;
  
}

// -----------------------------------------------------------
SpriteResource * ResourceMgr::RegisterSprite(const std::string &spriteKey, const std::string &imageKey, 
                                 unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  // get the image resource
  ImageResource * img = dynamic_cast<ImageResource *>( get(imageKey) );
  assert(img != NULL);
  
  // create sprite referring to it
  SpriteResource *resSprite = new SpriteResource(img, x1, y1, x2, y2);
  
  _resources.insert( std::make_pair(spriteKey, resSprite) );

  return resSprite;
  
}

// -----------------------------------------------------------
void ResourceMgr::PlaySound(const std::string &sPathKey) const {
  std::map <std::string, Resource *>::const_iterator it = _resources.find(sPathKey);
  
  assert(it != _resources.end() );
  
  SoundResource *snd = dynamic_cast<SoundResource *>(it->second);
  snd->play();
  
}

// -----------------------------------------------------------
Resource * ResourceMgr::get(const std::string &sPathKey) const {
  std::map <std::string, Resource *>::const_iterator it = _resources.find(sPathKey);
  
  assert(it != _resources.end() );
  
  return static_cast<Resource *> (it->second);
  
}

// -----------------------------------------------------------
void ResourceMgr::unregister(const std::string &pathKey) {
  _resources.erase(pathKey);
  
}