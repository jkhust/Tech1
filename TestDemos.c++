//
//  TestDemos.c++
//  Tech1
//
//  Created by Justin Hust on 12/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Clock.h"
#include "Reporter.h"
#include "Resource.h"
#include "Lexer.h"
#include "Parser.h"
#include "Environment.h"
#include "System.h"
#include "Util.h"

// -----------------------------------------
//TEST(demos, bombs) {
//  {
//    srand(0);
//    
//    System sys;
//      sys.init(640, 480);
//    
//      sys.Register("images/bomb.png");
//      sys.Register("sounds/explodelow.wav");
//      
//      int i = 0;
//      bool exploded[3];
//      float x[3];
//      float y[3];
//      float fExplodeTimer = 1.0f;
//
//      while(sys.clock()->getSecsElapsed() < 4.0f) {
//        sys.clock()->tick();
//        fExplodeTimer -= sys.clock()->getFrameSecs();
//        
//        // track an explosion
//        if(fExplodeTimer < 0.0f) {
//          sys.playSound("sounds/explodelow.wav");
//          
//          exploded[i] = true;
//          x[i] = random_float(100, 540);
//          y[i] = random_float(100, 380);
//          ++i;
//          
//          fExplodeTimer = 1.0f;
//        
//        }
//        
//        // draw
//        for(int j=0;j<i;j++) {
//          sys.draw("images/bomb.png", x[j], y[j]);
//        
//        }
//       
//        sys.presentScreen();
//                         
//      }
//  
//    sys.shutdown();
//  
//  }
//
//}

// -----------------------------------------
TEST(demos, bomb_walk) {
  {
    srand(0);
    
    System sys;
      sys.init(640, 480);
    
      sys.Register("images/mario_sprites.png");
      sys.RegisterSprite("bomb_walk1", "images/mario_sprites.png", 127, 212, 127+16, 212+16);
      sys.RegisterSprite("bomb_walk2", "images/mario_sprites.png", 141, 212, 141+16, 212+16);
      sys.Register("images/bomb.png");
      sys.Register("sounds/scurry.wav");
      sys.Register("sounds/explodelow.wav");
      
      enum bomb_state { bomb_startup, bomb_walking, bomb_exploding, bomb_exploded };
      bomb_state st = bomb_startup;
      
      float pos[3] = {100.0f, 300.0f, 0.0f};
      float vel[3] = {20.0f, -20.0f, 0.0f};
      
      float cdNextState;
      float cdFrame;
      float cdSound;
      int iFrame;
      
      while(sys.clock()->getSecsElapsed() < 8.0f) {
        sys.clock()->tick();
                
        switch(st) {
          case bomb_startup: {
            st = bomb_walking;
            cdNextState = 3.0f;

            pos[0] = 100.0f;
            vel[0] = 300.0f;
            cdFrame = 0.3f;
            cdSound = 0.0f;
            iFrame = 0;
          
            } break;
        
          case bomb_walking: {
              float fFrameSecs = sys.clock()->getFrameSecs();
              cdNextState -= fFrameSecs;
              cdFrame -= fFrameSecs;
              cdSound -= fFrameSecs;
          
              if(cdNextState < 0.0f) {
                st = bomb_exploding;
              
              } else {
                // frame transition
                cdFrame -= sys.clock()->getFrameSecs();
              
                if(cdFrame < 0.0f) {
                  iFrame++;
                  iFrame %= 2;
                  cdFrame = 0.3f;
                
                }
                
                // sound
                if(cdSound < 0.0f) {
                  sys.playSound("sounds/scurry.wav");
                  cdSound = 1.0f;
                
                }
              
         
                pos[0] += vel[0] * fFrameSecs;
//                pos[1] += vel[1] * fFrameSecs;
                 
                if(iFrame == 0)
                  sys.draw("bomb_walk1", pos[0], pos[1]);
                else if(iFrame == 1) 
                  sys.draw("bomb_walk2", pos[0], pos[1]);
                     
                          
              }
            
            } break;
            
          case bomb_exploding: {
            sys.playSound("sounds/explodelow.wav");
            st = bomb_exploded;
          
            } break;
          
          case bomb_exploded: {
            sys.draw("images/bomb.png", pos[0], pos[1]);
          
            } break;
        
        }

        sys.presentScreen();
                         
    }
  
    sys.shutdown();
  
  }

}