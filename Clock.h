//
//  Clock.h
//  Tech1
//
//  Created by Justin Hust on 12/8/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Clock_h
#define Tech1_Clock_h

class AbstractClock {
protected:
  // DATA
    unsigned int _startTicks;
    unsigned int _prevTicks;
    unsigned int _currTicks;
    
    unsigned int _frameMSecs;
    
    float _frameSecs;
    float _secsElapsed;

public:
  // CREATORS
    AbstractClock(void);
    virtual ~AbstractClock(void);

  // MANIPULATORS
    virtual void tick(void) = 0;

  // ACCESSORS
    unsigned int getPrevTicks(void) const;
    unsigned int getCurrTicks(void) const;
    
    unsigned int getFrameTicks(void) const;
    float getFrameSecs(void) const;
    float getSecsElapsed(void) const;
  
};

// ---------------------------------------------------
class SDLClock : public AbstractClock {
public:
  void tick(void);

};

#endif
