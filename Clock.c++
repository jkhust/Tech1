//
//  Clock.c++
//  Tech1
//
//  Created by Justin Hust on 12/8/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Clock.h"
#include "SDL2/SDL_Timer.h"  // looks in sys/lib/frameworks?

// ---------------------------------------------------------
AbstractClock::AbstractClock(void) {
  _startTicks = 0;
  _prevTicks = 0;
  _currTicks = 0;
  
  _frameMSecs = 0;
  _frameSecs = 0.0f;
  
}

// ---------------------------------------------------------
AbstractClock::~AbstractClock(void) {
  // no cleanup code.
  
}

// ---------------------------------------------------------
unsigned int AbstractClock::getPrevTicks(void) const {
  return _prevTicks;
  
}

// ---------------------------------------------------------
unsigned int AbstractClock::getCurrTicks(void) const {
  return _currTicks;
  
}

// ---------------------------------------------------------
unsigned int AbstractClock::getFrameTicks(void) const {
  return _frameMSecs; 
  
}

// ---------------------------------------------------------
float AbstractClock::getFrameSecs(void) const {
  return _frameSecs; 
  
}

// ---------------------------------------------------------
float AbstractClock::getSecsElapsed(void) const {
  return _secsElapsed;
  
}

// ---------------------------------------------------------
void SDLClock::tick(void) {
  unsigned int newTicks = SDL_GetTicks();
  
  if(_startTicks == 0) {
    _startTicks = newTicks;
    _prevTicks = newTicks;
    _currTicks = newTicks;
    
  } else {
    _prevTicks = _currTicks;
    _currTicks = newTicks;
 
  }
  
  // convert ms delta to secs delta.
  _frameMSecs = _currTicks - _prevTicks;
  _frameSecs = ((float) _frameMSecs) / 1000.0f;
  _secsElapsed = ((float) _currTicks - (float) _startTicks) / 1000.0f;

}