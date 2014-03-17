//
//  TestDraw.c++
//  Tech1
//
//  Created by Justin Hust on 12/14/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>

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
  // --- init ----
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    char err[80];
    snprintf(err, 80, "Failed SDL Init: %s.\n", SDL_GetError());
    std::cout << err << std::endl;
    
  }

  SDL_Window *sdlWindow = NULL;
  if((sdlWindow = SDL_CreateWindow("Tech1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                resWidth, resHeight, SDL_WINDOW_SHOWN)) == NULL) {
    char err[80];
    snprintf(err, 80, "Failed Window Init: %s.\n", SDL_GetError());
    std::cout << err << std::endl;
    
  }
  
  SDL_Surface *windowSurf = SDL_GetWindowSurface(sdlWindow);
 
  ResourceMgr rm;
  rm.Register("images/space_800x600.png");
  rm.Register("images/bomb.png");
  rm.Register("images/bullet.png");
  
  ImageResource *imgBack = dynamic_cast<ImageResource *> (rm.get("images/space_800x600.png"));
  ImageResource *imgBomb = dynamic_cast<ImageResource *> (rm.get("images/bomb.png"));
  ImageResource *imgBullet = dynamic_cast<ImageResource *> (rm.get("images/bullet.png"));
 
 
  // ----- main code ------
  SDLClock c;
  while(c.getSecsElapsed() < 3.0f) {
    imgBack->draw(resWidth / 2, resHeight/2, windowSurf);
    imgBomb->draw(600, 200, windowSurf);
    imgBullet->draw(200, 300, windowSurf);

    
    SDL_UpdateWindowSurface(sdlWindow);

    c.tick();
  
  }
  
  rm.unregister("images/bullet.png");
  rm.unregister("images/bomb.png");
  rm.unregister("images/space_800x600.png");
  
  
  
  // --- cleanup ----
  SDL_FreeSurface(windowSurf);
  windowSurf = NULL;
  
  SDL_DestroyWindow(sdlWindow);
  sdlWindow = NULL;
  
  SDL_Quit();
  return 0;

}