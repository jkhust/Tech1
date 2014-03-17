//
//  TestAnimate.c++
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
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"

#include "Clock.h"
#include "Reporter.h"
#include "Resource.h"

const int resWidth = 1136;
const int resHeight = 640;

// -----------------------------------------------------------------
int main(int argc, char *argv[]) {
  Reporter rpt;

  // --- init ----
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    char err[80];
    snprintf(err, 80, "Failed SDL Init: %s.\n", SDL_GetError());
    rpt.fatalError( std::string(err));
  
  }

  SDL_Window *sdlWindow = NULL;
  if((sdlWindow = SDL_CreateWindow("Tech1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                resWidth, resHeight, SDL_WINDOW_SHOWN)) == NULL) {
    char err[80];
    snprintf(err, 80, "Failed Window Init: %s.\n", SDL_GetError());
    rpt.fatalError( std::string(err));
  }
  
  SDL_Surface *windowSurf = SDL_GetWindowSurface(sdlWindow);
 
  ResourceMgr rm;
  rm.Register("images/mario_back.png");
  rm.Register("images/mario_sprites.png");
  rm.RegisterSprite("goomba1", "images/mario_sprites.png", 295, 76, 295 + 16, 76 + 16);
  rm.RegisterSprite("goomba2", "images/mario_sprites.png", 276, 76, 276 + 16, 76 + 16);
  
  
  ImageResource *imgBack = dynamic_cast<ImageResource *> (rm.get("images/mario_back.png"));
  
  SpriteResource *sprites[2] = {NULL, NULL};
  sprites[0] = dynamic_cast<SpriteResource *> (rm.get("goomba1"));
  sprites[1] = dynamic_cast<SpriteResource *> (rm.get("goomba2"));
 
  // ----- main code ------
  float fPos = 600;
  float fVel = -50;  // pps
  int iSprite = 0;
  float fSteps = 0.0f;
  
  SDLClock c;
  while(c.getSecsElapsed() < 8.0f) {
    float fDist = fVel * c.getFrameSecs();
    fPos = fPos + fDist;

    fSteps += abs(fDist);
    std::cout << fSteps << std::endl;
    if(fSteps >= 5.0f) {
      fSteps = 0.0f;
      iSprite++;
      iSprite %= 2;
            
    }
    
    imgBack->draw(400, 300, windowSurf);
    
    sprites[iSprite]->draw((int) fPos, 300, windowSurf);

    SDL_UpdateWindowSurface(sdlWindow);

    c.tick();
  
  }
  
  rm.unregister("goomba2");
  rm.unregister("goomba1");
  rm.unregister("images/mario_sprites.png");
  rm.unregister("images/mario_back.png");
  
  // --- cleanup ----
  SDL_FreeSurface(windowSurf);
  windowSurf = NULL;
  
  SDL_DestroyWindow(sdlWindow);
  sdlWindow = NULL;
  
  SDL_Quit();
  return 0;

}