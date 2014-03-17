//
//  System.h
//  Tech1
//
//  Created by Justin Hust on 12/18/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_System_h
#define Tech1_System_h

#include <iostream>
#include "Reporter.h"
#include "Environment.h"
#include "SDL2/SDL.h"

class AbstractClock;
class Environment;
class Resource;
class ResourceMgr;
class SpriteResource;
class Variant;
class ScriptInstance;

// ----------------------------------------------
class System {
private:
  // DATA
    AbstractClock * _clock;    // clock
    Environment _envSys;
    Reporter _rpt;
    ResourceMgr *_resMgr;
    
    SDL_Surface *_screen;
    SDL_Window *_sdlWindow;

public:
  // CREATORS
    System(void);
    ~System(void);
    
  // MANIPULATORS
    void init(int w, int h);
    void shutdown(void);

    void setScreen(SDL_Surface *toSurf);
    void presentScreen(void);
                    
  // ACCESSORS
    AbstractClock * clock(void);

  // DELEGATION
      Environment & env(void);
  
    // resource mgr
      Resource * Register(const std::string &sPathKey);
      void unregister(const std::string &sPathKey);
      SpriteResource * RegisterSprite(const std::string &sSpriteKey, const std::string &sImgKey,
                                      unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
      void draw(const std::string &sPathKey, float x, float y);
      void playSound(const std::string &sPathKey);
  
    // scripting
      ScriptInstance * createScriptInstance(const std::string &sPathKey);
      std::ostream * getScriptingChannel(void);
      
      void exec(const std::string &sCode);
  
};

#endif
