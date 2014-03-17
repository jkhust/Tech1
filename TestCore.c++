// --------
// includes
// --------

#include <iostream> // cout, endl
#include <fstream>
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Vector.h"
#include "Clock.h"
#include "Reporter.h"
#include "Resource.h"
#include "Lexer.h"
#include "Parser.h"
#include "Environment.h"
#include "System.h"

// -----------
// Defines
// -----------
#define TEST_VECTOR
//#define TEST_CLOCK
//#define TEST_REPORTER
//#define TEST_RESOURCEMGR
#define TEST_VARIANT
#define TEST_LEXER
#define TEST_PARSER
#define TEST_SCRIPT
#define TEST_SYSTEM

// -----------
// Vector
// -----------
#ifdef TEST_VECTOR 

TEST(Vector, create) {
  {
    Vec3 v;
    ASSERT_TRUE(v.x == 0);
    ASSERT_TRUE(v.y == 0);
    ASSERT_TRUE(v.z == 0);

  }

  {
    Vec3 v(3, 5, 7);
    ASSERT_TRUE(v.x == 3.0f);
    ASSERT_TRUE(v.y == 5.0f);
    ASSERT_TRUE(v.z == 7.0f);

  }

  {
    Vec3 v(1, -3, 12);
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -3.0f);
    ASSERT_TRUE(v.z == 12.0f);

  }
  
  {
    Vec3 v1(1, -3, 12);
    ASSERT_TRUE(v1.x == 1.0f);
    ASSERT_TRUE(v1.y == -3.0f);
    ASSERT_TRUE(v1.z == 12.0f);
    
    Vec3 v2 = v1;
    ASSERT_TRUE(v2.x == 1.0f);
    ASSERT_TRUE(v2.y == -3.0f);
    ASSERT_TRUE(v2.z == 12.0f);
    
  }

  {
    Vec3 v1(1, 3, 5);
    ASSERT_TRUE(v1.x == 1.0f);
    ASSERT_TRUE(v1.y == 3.0f);
    ASSERT_TRUE(v1.z == 5.0f);
    
    v1 = Vec3(2, 4, 6);
    ASSERT_TRUE(v1.x == 2.0f);
    ASSERT_TRUE(v1.y == 4.0f);
    ASSERT_TRUE(v1.z == 6.0f);
    
  }

}

// --------
TEST(Vector, subscript) {
  {
    Vec3 v(1, 3, 5);
    ASSERT_TRUE(v[0] == 1.0f);
    ASSERT_TRUE(v[1] == 3.0f);
    ASSERT_TRUE(v[2] == 5.0f);
    
    v = Vec3(-2, 4, -6);
    ASSERT_TRUE(v[0] == -2.0f);
    ASSERT_TRUE(v[1] == 4.0f);
    ASSERT_TRUE(v[2] == -6.0f);
    
  }

}

// --------
TEST(Vector, add) {
  {
    Vec3 v;
    v = v + Vec3(1, -2, 3);
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -2.0f);
    ASSERT_TRUE(v.z == 3.0f);

  }

  {
    Vec3 v(2, 4, 6);
    v = v + Vec3(0, 0, 0) + Vec3(1, 2, 4);
    ASSERT_TRUE(v.x == 3.0f);
    ASSERT_TRUE(v.y == 6.0f);
    ASSERT_TRUE(v.z == 10.0f);

  }
  
  {
    Vec3 v;
    v += Vec3(1, -2, 3);
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -2.0f);
    ASSERT_TRUE(v.z == 3.0f);

  }

  {
    Vec3 v(2, 4, 6);
    v += Vec3(0, 0, 0);
    ASSERT_TRUE(v.x == 2.0f);
    ASSERT_TRUE(v.y == 4.0f);
    ASSERT_TRUE(v.z == 6.0f);

  }

}

// --------
TEST(Vector, subtract) {
  {
    Vec3 v;
    v = v - Vec3(1, -2, 3);
    ASSERT_TRUE(v.x == -1.0f);
    ASSERT_TRUE(v.y == 2.0f);
    ASSERT_TRUE(v.z == -3.0f);

  }

  {
    Vec3 v(2, 2, 6);
    v = v - Vec3(1, 3, 2);
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -1.0f);
    ASSERT_TRUE(v.z == 4.0f);

  }

  {
    Vec3 v;
    v -= Vec3(1, -2, 3);
    ASSERT_TRUE(v.x == -1.0f);
    ASSERT_TRUE(v.y == 2.0f);
    ASSERT_TRUE(v.z == -3.0f);

  }

  {
    Vec3 v(2, 2, 6);
    v -= Vec3(1, 3, 2);
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -1.0f);
    ASSERT_TRUE(v.z == 4.0f);

  }


}

// --------
TEST(Vector, scale) {
  {
    Vec3 v(1, -2, 3);
    v = v * 0.25;
    
    ASSERT_TRUE(v.x == 0.25f);
    ASSERT_TRUE(v.y == -0.5f);
    ASSERT_TRUE(v.z == 0.75f);

  }

  {
    Vec3 v(1, -2, 3);
    v = v * 6;
    
    ASSERT_TRUE(v.x == 6.0f);
    ASSERT_TRUE(v.y == -12.0f);
    ASSERT_TRUE(v.z == 18.0f);

  }
  
  {
    Vec3 v(1, -2, 3);
    v *= 6;
    
    ASSERT_TRUE(v.x == 6.0f);
    ASSERT_TRUE(v.y == -12.0f);
    ASSERT_TRUE(v.z == 18.0f);

  }
  
  {
    Vec3 v(1, -2, 3);
    v *= 0;
    
    ASSERT_TRUE(v.x == 0.0f);
    ASSERT_TRUE(v.y == 0.0f);
    ASSERT_TRUE(v.z == 0.0f);
    ASSERT_TRUE(v.mag() == 0.0f);

  }
  
  {
    Vec3 v(27, -3, 9);
    v = v / -3.0f;
    
    ASSERT_TRUE(v.x == -9.0f);
    ASSERT_TRUE(v.y == 1.0f);
    ASSERT_TRUE(v.z == -3.0f);

  }

  {
    Vec3 v(27, -3, 9);
    v /= -3.0f;
    
    ASSERT_TRUE(v.x == -9.0f);
    ASSERT_TRUE(v.y == 1.0f);
    ASSERT_TRUE(v.z == -3.0f);

  }

  {
    Vec3 v(1, -2, 3);
    v = v / 1.0f;
    
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -2.0f);
    ASSERT_TRUE(v.z == 3.0f);

  }

  {
    Vec3 v(1, -2, 3);
    v /= 1.0f;
    
    ASSERT_TRUE(v.x == 1.0f);
    ASSERT_TRUE(v.y == -2.0f);
    ASSERT_TRUE(v.z == 3.0f);

  }

}

// --------
TEST(Vector, equality) {
  {
    Vec3 v(0, 0, 0);
    
    ASSERT_TRUE( v == Vec3(0, 0, 0) );
    ASSERT_TRUE( v != Vec3(0, 0, 1) );
  
  }
  
  
  {
    Vec3 v1(0, 1, 2);
    Vec3 v2(0, 1, 2);
    
    ASSERT_TRUE(v1 == v2);

  }

  {
    Vec3 v1(0, 1, 2);
    Vec3 v2(0, 1, 0);
    
    ASSERT_TRUE(v1 == (v2 + Vec3(0, 0, 2) )   );

  }
    
}

// --------
TEST(Vector, mag) {
  {
    Vec3 v;
    ASSERT_TRUE(v.mag() == 0.0f);

  }

  {
    Vec3 v(3, 5, 7);
    ASSERT_TRUE(v.mag() == sqrtf(83.0f) );

  }

  {
    Vec3 v(1, -3, 12);
    ASSERT_TRUE(v.mag() == sqrtf(154.0f) );

  }
  
}

// --------
TEST(Vector, distance) {
  {
    Vec3 u(4, 0, 0);
    Vec3 v(4, 0, 3);
    
    Vec3 w = v - u;
    ASSERT_TRUE(w.mag() == 3.0f);
    
    w = u - v;
    ASSERT_TRUE(w.mag() == 3.0f);

  }

  {
    Vec3 u(4, 4, 1);
    Vec3 v(5, 4, 2);
    
    Vec3 w = v - u;
    ASSERT_TRUE(w.mag() == sqrtf(2.0f) );
    
    w = u - v;
    ASSERT_TRUE(w.mag() == sqrtf(2.0f) );

  }
    
}

// --------
TEST(Vector, normalize) {
  {
    Vec3 v(1, 4, 12);
    v.normalize();
  
    ASSERT_TRUE( v.x == (1.0f / sqrtf(161.0f) ) );
    ASSERT_TRUE( v.y == (4.0f / sqrtf(161.0f) ) );
    ASSERT_TRUE( v.z == (12.0f / sqrtf(161.0f) ) );
  
  }
  
  {
    Vec3 v(0, -1, 0);
    v.normalize();
  
    ASSERT_TRUE( v.x == 0.0f );
    ASSERT_TRUE( v.y == -1.0f );
    ASSERT_TRUE( v.z == 0.0f );
  
  }

}

#endif

// -----------
// Clock
// -----------
#ifdef TEST_CLOCK

TEST(Clock, getSecsElapsed) {
  SDLClock c;
  c.tick();
  
  while(c.getSecsElapsed() == 0) { c.tick(); }
  
  ASSERT_TRUE( c.getSecsElapsed() > 0 );

}

TEST(Clock, wait) {
  SDLClock c;
  c.tick();
  
  float fElapsed = 0;
  
  while( fElapsed < 2000.0f) { 
    c.tick();
    fElapsed += c.getFrameTicks();
    
  }
  
  ASSERT_TRUE( fElapsed >= 2000.0f );
  ASSERT_TRUE( c.getSecsElapsed() >= 1.5f );

}

TEST(Clock, moveObject) {
  float vel = 5.0f;   // spaces per second.
  float pos = 0.0f;
  
  SDLClock c;
  c.tick();
  
  while( c.getSecsElapsed() < 2.0f ) {
    c.tick();
    pos += vel * c.getFrameSecs();
  
  }
  
  ASSERT_TRUE( (int) pos == 10 );
  
}

#endif

// ---------------
// Reporter 
// ---------------
#ifdef TEST_REPORTER

TEST(Reporter, consoleCheck) {
  Reporter r;
  r.system("Sys 1 2 3\n");
  r.console("Console 1 2 3\n");
  r.resources("Res 1 2 3\n");
  r.video("Video 1 2 3\n");
  r.audio("Audio 1 2 3\n");
  r.scripting("Scripting 1 2 3\n");
  
  r.system("Sys 4 5 6\n");
  r.console("Console 4 5 6\n");
  r.resources("Res 4 5 6\n");
  r.video("Video 4 5 6\n");
  r.audio("Audio 4 5 6\n");
  r.scripting("Scripting 4 5 6\n");
  
  //r.fatalError("Forced Exit");
  
  ASSERT_TRUE(true);
    
}

#endif

// ---------------
// Resource Manager
// ---------------
#ifdef TEST_RESOURCEMGR

TEST(ResourceMgr, registerImage) {
  ResourceMgr rm;
  rm.Register("images/menu_back.png");
  
  ImageResource *res = dynamic_cast<ImageResource *> (rm.get("images/menu_back.png"));
    
  ASSERT_TRUE(res->getWidth() == 442);
  ASSERT_TRUE(res->getHeight() == 403);
    
  rm.unregister("images/menu_back.png");
    
  SDL_Quit();
  
}

// -----------
TEST(ResourceMgr, registerSprite) {
  ResourceMgr rm;
  rm.Register("images/mario_sprites.png");
  rm.RegisterSprite("bulletBill", "images/mario_sprites.png", 128, 98, 194, 164);
  
  ImageResource *resImage = dynamic_cast<ImageResource *> (rm.get("images/mario_sprites.png"));
  ASSERT_TRUE(resImage->getWidth() == 662);
  ASSERT_TRUE(resImage->getHeight() == 501);
    
  SpriteResource *resSprite = dynamic_cast<SpriteResource *> (rm.get("bulletBill"));
  ASSERT_TRUE( resSprite->getWidth() == 67);
  ASSERT_TRUE( resSprite->getHeight() == 67);
      
  rm.unregister("bulletBill");
  rm.unregister("images/mario_sprites.png");
    
  SDL_Quit();

}

// -----------
TEST(ResourceMgr, registerSound) {
  int sdlInitResult = SDL_Init(SDL_INIT_AUDIO);
  ASSERT_TRUE(sdlInitResult >= 0);

  
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  ASSERT_TRUE(audioInitResult != -1);
  

  ResourceMgr rm;
  rm.Register("sounds/menu_enter.wav");
  
  SoundResource *wav = dynamic_cast<SoundResource *> (rm.get("sounds/menu_enter.wav"));
  ASSERT_TRUE(wav != NULL);

  rm.unregister("sounds/menu_enter.wav");
    
  Mix_CloseAudio();
  SDL_Quit();

}

// -----------
TEST(ResourceMgr, registerSoundAndPlay) {
  int sdlInitResult = SDL_Init(SDL_INIT_AUDIO);
  ASSERT_TRUE(sdlInitResult >= 0);

  
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  ASSERT_TRUE(audioInitResult != -1);
  

  ResourceMgr rm;
  rm.Register("sounds/menu_enter.wav");
  
  SoundResource *wav = dynamic_cast<SoundResource *> (rm.get("sounds/menu_enter.wav"));
  ASSERT_TRUE(wav != NULL);

  wav->play();

  SDLClock c;
  while(c.getSecsElapsed() < 1.0f) {
    c.tick();
  
  }

  rm.unregister("sounds/menu_enter.wav");
    
  Mix_CloseAudio();
  SDL_Quit();
  
}

// -----------
TEST(ResourceMgr, registerMusic) {
  int sdlInitResult = SDL_Init(SDL_INIT_AUDIO);
  ASSERT_TRUE(sdlInitResult >= 0);

  
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  ASSERT_TRUE(audioInitResult != -1);
  
  ResourceMgr rm;
  rm.Register("music/beat1.mus.wav");
  
  MusicResource *mus = dynamic_cast<MusicResource *> (rm.get("music/beat1.mus.wav"));
  ASSERT_TRUE(mus != NULL);
  
  rm.unregister("music/beat1.mus.wav");
    
  Mix_CloseAudio();
  SDL_Quit();

}

// -----------
TEST(ResourceMgr, registerMusicAndPlay) {
  int sdlInitResult = SDL_Init(SDL_INIT_AUDIO);
  ASSERT_TRUE(sdlInitResult >= 0);

  
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  ASSERT_TRUE(audioInitResult != -1);
  

  ResourceMgr rm;
  rm.Register("music/beat1.mus.wav");
  
  MusicResource *mus = dynamic_cast<MusicResource *> (rm.get("music/beat1.mus.wav"));
  ASSERT_TRUE(mus != NULL);
  
  mus->play();

  SDLClock c;
  while(c.getSecsElapsed() < 1.0f) {
    c.tick();
  
  }
  
  rm.unregister("music/beat1.mus.wav");
    
  Mix_CloseAudio();
  SDL_Quit();

}

#endif

// -----------
// Variant
// -----------
#ifdef TEST_VARIANT

TEST(Variant, variant_bool) {
  Variant v(false);
  ASSERT_TRUE(v.isBoolean());
  ASSERT_TRUE(v == false);
  
  v = true;  
  ASSERT_TRUE(v.isBoolean());
  ASSERT_TRUE(v == true);
    
}

// -----------
TEST(Variant, variant_int) {
  Variant v(1234);
  ASSERT_TRUE(v.isInteger());
  ASSERT_TRUE(v == 1234);
  
  v = -1;
  ASSERT_TRUE(v.isInteger());
  ASSERT_TRUE(v == -1);
    
}

// -----------
TEST(Variant, variant_float) {
  Variant v(3.14159265f);
  ASSERT_TRUE(v.isFloat());
  ASSERT_TRUE(v == 3.1415926535f);
  
  v = 1.618f;
  ASSERT_TRUE(v.isFloat());
  ASSERT_TRUE(v == 1.618f);
  
  v = 0.0f;
  ASSERT_TRUE(v.isFloat());
  //ASSERT_TRUE(v == 0);
  ASSERT_TRUE(v == 0.0f);

}

// -----------
TEST(Variant, variant_string) {
  Variant v("hello");
  ASSERT_TRUE(v.isString());
  ASSERT_TRUE(v == "hello");

}

// -----------
TEST(Variant, variant_vec3) {
  Variant v( Vec3(0, 1, 2) );

  ASSERT_TRUE( v.isVec3() );
  ASSERT_TRUE( v == Vec3(0, 1, 2) );

  Variant v2( Vec3(0, 1, 2) );
  ASSERT_TRUE(v == v2);

}

// -----------
TEST(Variant, variant_vec3_mag) {
  Variant v( Vec3(0, 3, 4) );

  ASSERT_TRUE( v.mag() == 5.0f ); 

}

// -----------
TEST(Variant, variant_vec3_normalize) {
  Variant v( Vec3(0, 3, 4) );
  v.normalize();

  ASSERT_TRUE( v.x() == 0.0f ); 
  ASSERT_TRUE( v.y() == 0.6f ); 
  ASSERT_TRUE( v.z() == 0.8f ); 

}

// -----------
TEST(Variant, variant_equality) {
  Variant v = "hello";
  Variant w = "world";
  Variant x = "hello";

  ASSERT_TRUE(v == x);
  ASSERT_TRUE(v != w);
  

  Variant a = 3;
  Variant b = 4;
  Variant c = 3;
   
  ASSERT_TRUE(a == c);
  ASSERT_TRUE(a != b);
  ASSERT_TRUE(b != c);

  
     
  Variant f = 7.0f;
  Variant g = 0.0f;
  Variant h = 7.0f;
  
  ASSERT_TRUE(f == h);
  ASSERT_TRUE(f != g);
  
  
  Variant j = false;
  Variant k = true;
  Variant l = false;
  
  ASSERT_TRUE(j == l);
  ASSERT_TRUE(j != k);


  ASSERT_TRUE(v != l);
  ASSERT_TRUE(k != b);
  ASSERT_TRUE(a != w);
  ASSERT_TRUE(c != g);
  ASSERT_TRUE(c != "hello");
  
}

// -----------
TEST(Variant, arith) {
  {
    Variant v(5);
    ++v;
    
    ASSERT_TRUE(v == 6);
    
    --v; --v;
    ASSERT_TRUE(v == 4);

    ++v; 
    ASSERT_TRUE(v == 5);
    
  }

  {
    Variant v(5);

    v += 3;
    ASSERT_TRUE(v == 8);

    v -= 4;
    ASSERT_TRUE(v == 4);

    v *= 5;
    ASSERT_TRUE(v == 20);

    v /= 2;
    ASSERT_TRUE(v == 10);

  }
  
  {
    Variant v(3);

    v += 5.5f;
    ASSERT_TRUE(v == 8.5f);

    v -= 4.0f;
    ASSERT_TRUE(v == 4.5f);

    v *= 5.0f;
    ASSERT_TRUE(v == 22.5f);

    v /= 2.5f;
    ASSERT_TRUE(v == 9.0f);

  }
  
  {
    Variant f(12.0f);

    f += 4.0f;
    ASSERT_TRUE(f == 16.0f);

    f -= 8.0f;
    ASSERT_TRUE(f == 8.0f);

    f *= 5.0f;
    ASSERT_TRUE(f == 40.0f);

    f /= 4;
    ASSERT_TRUE(f == 10.0f);

  }

}

#endif

// -----------
// Lexer
// -----------
#ifdef TEST_LEXER

TEST(Lexer, comments) {
  {
    std::istringstream iss(" // new program \n");

    Lexer l( iss );
    Token *tok = l.lex();

    ASSERT_TRUE(tok == NULL);
  }

  {
    std::istringstream iss(" /* new program */ \n // another program \n /* more */ ");

    Lexer l( iss );
    Token *tok = l.lex();

    ASSERT_TRUE(tok == NULL);
    
  }

}

// -------
TEST(Lexer, ident1) {
  std::istringstream iss(" asdf ");

  Lexer l( iss );
  Token *tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Identifier);
  ASSERT_TRUE( dynamic_cast<IdentifierToken *> (tok)->getVal() == "asdf");
  ASSERT_TRUE(tok->toString() == "1:2\tident\t asdf");
  
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -------
TEST(Lexer, ident2) {
  std::istringstream iss(" a b ");

  Lexer l( iss );
  
  
  Token *tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Identifier);
  ASSERT_TRUE( dynamic_cast<IdentifierToken *> (tok)->getVal() == "a");
  ASSERT_TRUE(tok->toString() == "1:2\tident\t a");
  
  delete tok;
  tok = NULL;

  // ---

  tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Identifier);
  ASSERT_TRUE( dynamic_cast<IdentifierToken *> (tok)->getVal() == "b");
  ASSERT_TRUE(tok->toString() == "1:4\tident\t b");
  
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
    
}

// -------------
TEST(Lexer, if1) {
  std::istringstream iss("if");

  Lexer l( iss );
  Token *tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_If);
  ASSERT_TRUE(tok->toString() == "1:1\treserv\t IF");
  
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, if2) {
  std::istringstream iss("    if ");

  Lexer l( iss );
  Token *tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_If);
  ASSERT_TRUE(tok->toString() == "1:5\treserv\t IF");
  
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, if3) {
  std::istringstream iss(" \n \n     IF ");

  Lexer l( iss );
  Token *tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_If);
  ASSERT_TRUE(tok->toString() == "3:6\treserv\t IF");
  
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, loops) {
  std::istringstream iss(" dotimes ");

  Lexer l( iss );
  Token *tok = l.lex();

  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_DoTimes);
  ASSERT_TRUE(tok->toString() == "1:2\treserv\t DOTIMES");
  
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, if_ident) {
  std::istringstream iss(" \n    IF \n  foo \n    BAR \n IF\n ");
  Lexer l( iss );
  
  // if 
  Token *tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_If);
  ASSERT_TRUE(tok->toString() == "2:5\treserv\t IF");
  delete tok;
  tok = NULL;
  
  // foo
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Identifier);
  ASSERT_TRUE( dynamic_cast<IdentifierToken *> (tok)->getVal() == "foo");
  ASSERT_TRUE(tok->toString() == "3:3\tident\t foo");
  delete tok;
  tok = NULL;
  
  // bar
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Identifier);
  ASSERT_TRUE(dynamic_cast<IdentifierToken *> (tok)->getVal() == "bar");
  ASSERT_TRUE(tok->toString() == "4:5\tident\t bar");
  delete tok;
  tok = NULL;
  
  // second if
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_If);
  ASSERT_TRUE(tok->toString() == "5:2\treserv\t IF");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, lexBooleans) {
  std::istringstream iss(" \n  false \n   true ");
  Lexer l( iss );
  
  Token *tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_BooleanLiteral);
  ASSERT_TRUE(dynamic_cast<BooleanLiteralToken *> (tok)->getVal() == false);
  ASSERT_TRUE(tok->toString() == "2:3\tbool\t FALSE");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_BooleanLiteral);
  ASSERT_TRUE(dynamic_cast<BooleanLiteralToken *> (tok)->getVal() == true);
  ASSERT_TRUE(tok->toString() == "3:4\tbool\t TRUE");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );

}

// -----------
TEST(Lexer, lexInts) {
  std::istringstream iss(" 100 \n    -23 \n   0  7 \n128 \n 65305");
  Lexer l( iss );
  
  Token *tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == 100);
  ASSERT_TRUE(tok->toString() == "1:2\tint\t 100");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == -23);
  ASSERT_TRUE(tok->toString() == "2:5\tint\t -23");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == 0);
  ASSERT_TRUE(tok->toString() == "3:4\tint\t 0");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == 7);
  ASSERT_TRUE(tok->toString() == "3:7\tint\t 7");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == 128);
  ASSERT_TRUE(tok->toString() == "4:1\tint\t 128");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == 65305);
  ASSERT_TRUE(tok->toString() == "5:2\tint\t 65305");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, lexStrings) {
  std::istringstream iss(" \"who\" \n  false \n  \"is\" \n   0  \"it\" ");
  Lexer l( iss );
  
  Token *tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_StringLiteral);
  ASSERT_TRUE(dynamic_cast<StringLiteralToken *> (tok)->getVal() == "who");
  ASSERT_TRUE(tok->toString() == "1:2\tstring\t who");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_BooleanLiteral);
  ASSERT_TRUE(dynamic_cast<BooleanLiteralToken *> (tok)->getVal() == false);
  ASSERT_TRUE(tok->toString() == "2:3\tbool\t FALSE");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_StringLiteral);
  ASSERT_TRUE(dynamic_cast<StringLiteralToken *> (tok)->getVal() == "is");
  ASSERT_TRUE(tok->toString() == "3:3\tstring\t is");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_IntegerLiteral);
  ASSERT_TRUE(dynamic_cast<IntegerLiteralToken *> (tok)->getVal() == 0);
  ASSERT_TRUE(tok->toString() == "4:4\tint\t 0");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_StringLiteral);
  ASSERT_TRUE(dynamic_cast<StringLiteralToken *> (tok)->getVal() == "it");
  ASSERT_TRUE(tok->toString() == "4:7\tstring\t it");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, lexFloats) {
  std::istringstream iss(" 100.03 \n    -23.79 \n   -17.0  7.0 \n0.0 \n .001 \n  -0.124");
  Lexer l( iss );
  
  Token *tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == 100.03f);
  ASSERT_TRUE(tok->toString() == "1:2\tfloat\t 100.03");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == -23.79f);
  ASSERT_TRUE(tok->toString() == "2:5\tfloat\t -23.79");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == -17.0f);
  ASSERT_TRUE(tok->toString() == "3:4\tfloat\t -17");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == 7.0f);
  ASSERT_TRUE(tok->toString() == "3:11\tfloat\t 7");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == 0.0f);
  ASSERT_TRUE(tok->toString() == "4:1\tfloat\t 0");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == 0.001f);
  ASSERT_TRUE(tok->toString() == "5:2\tfloat\t 0.001");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_FloatLiteral);
  ASSERT_TRUE(dynamic_cast<FloatLiteralToken *> (tok)->getVal() == -0.124f);
  ASSERT_TRUE(tok->toString() == "6:3\tfloat\t -0.124");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, parens) {
  std::istringstream iss(" ( asdf ) ");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_LPAR);
  ASSERT_TRUE(tok->toString() == "1:2\treserv\t (");
  delete tok;
  tok = NULL;
  
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Identifier);
  ASSERT_TRUE(dynamic_cast<IdentifierToken *> (tok)->getVal() == "asdf");
  ASSERT_TRUE(tok->toString() == "1:4\tident\t asdf");
  delete tok;
  tok = NULL;
  
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_RPAR);
  ASSERT_TRUE(tok->toString() == "1:9\treserv\t )");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, declarations) {
  std::istringstream iss(" bool int float string vec3 ");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Bool);
  ASSERT_TRUE(tok->toString() == "1:2\treserv\t BOOL");
  delete tok;
  tok = NULL;
  

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Int);
  ASSERT_TRUE(tok->toString() == "1:7\treserv\t INT");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Float);
  ASSERT_TRUE(tok->toString() == "1:11\treserv\t FLOAT");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_String);
  ASSERT_TRUE(tok->toString() == "1:17\treserv\t STRING");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Vec3);
  ASSERT_TRUE(tok->toString() == "1:24\treserv\t VEC3");
  delete tok;
  tok = NULL;
   
  ASSERT_TRUE( l.lex() == NULL );

}

// -----------
TEST(Lexer, comparators) {
  std::istringstream iss(" == != < <= > >= ");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Equals);
  ASSERT_TRUE(tok->toString() == "1:2\top\t EQ");
  delete tok;
  tok = NULL;

  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_NotEquals);
  ASSERT_TRUE(tok->toString() == "1:5\top\t NEQ");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_LessThan);
  ASSERT_TRUE(tok->toString() == "1:8\top\t LT");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_LessOrEqual);
  ASSERT_TRUE(tok->toString() == "1:10\top\t LE");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_GreaterThan);
  ASSERT_TRUE(tok->toString() == "1:13\top\t GT");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_GreaterOrEqual);
  ASSERT_TRUE(tok->toString() == "1:15\top\t GE");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, arithmetic) {
  std::istringstream iss(" = + ++");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Assign);
  ASSERT_TRUE(tok->toString() == "1:2\top\t ASSIGN");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Plus);
  ASSERT_TRUE(tok->toString() == "1:4\top\t PLUS");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_PlusPlus);
  ASSERT_TRUE(tok->toString() == "1:6\top\t PLUSPLUS");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, logicalOps) {
  std::istringstream iss(" and or not");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_And);
  ASSERT_TRUE(tok->toString() == "1:2\treserv\t AND");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Or);
  ASSERT_TRUE(tok->toString() == "1:6\treserv\t OR");
  delete tok;
  tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Not);
  ASSERT_TRUE(tok->toString() == "1:9\treserv\t NOT");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );

}

// -----------
TEST(Lexer, progn) {
  std::istringstream iss(" \n\n  progn ");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_Progn);
  ASSERT_TRUE(tok->toString() == "3:3\treserv\t PROGN");
  delete tok;
  tok = NULL;
  
  ASSERT_TRUE( l.lex() == NULL );
  
}

// -----------
TEST(Lexer, envAccess) {
  std::istringstream iss(" @sys:frameTicks ");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_EnvAccess);
  ASSERT_TRUE(tok->toString() == "1:2\tsymbol\t ENVACCESS");
  delete tok;
  tok = NULL;
    
  ASSERT_TRUE( l.lex() == NULL );

}

// -----------
TEST(Lexer, Squarebrackets) {
  std::istringstream iss("[ 3.2 1.1 2.4 ] ");

  Lexer l( iss );
  Token *tok = NULL;
  
  tok = l.lex();
  ASSERT_TRUE(tok != NULL);
  ASSERT_TRUE(tok->getType() == Token_SquareBrackets);
  ASSERT_TRUE(tok->toString() == "1:1\treserv\t SQUAREBRACKETS");
  ASSERT_TRUE(tok->getNumChildren() == 3);
  delete tok;
  tok = NULL;
    
  ASSERT_TRUE( l.lex() == NULL );

}

#endif

// ---------------
// Parser
// ---------------
#ifdef TEST_PARSER

TEST(Parser, parseInt) {
  std::istringstream iss("(int x 5)");

  Parser p;
  Token *tok = p.parse( iss );
  
  ASSERT_TRUE( tok->getType() == Token_Int );
  ASSERT_TRUE( tok->toString() == "1:2\treserv\t INT");
  ASSERT_TRUE( tok->getNumChildren() == 2 );
  
  Token * t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_Identifier );
  ASSERT_TRUE( t->toString() == "1:6\tident\t x");
  ASSERT_TRUE( dynamic_cast<IdentifierToken *>(t)->getVal() == "x");
  
  t = tok->getChild(1);
  ASSERT_TRUE( t->getType() == Token_IntegerLiteral );
  ASSERT_TRUE( t->toString() == "1:8\tint\t 5");
  ASSERT_TRUE( dynamic_cast<IntegerLiteralToken *>(t)->getVal() == 5);  

}

// -----------
TEST(Parser, parseBool) {
  std::istringstream iss("( bool b true ) ");

  Parser p;
  Token *tok = p.parse( iss );
  
  ASSERT_TRUE( tok->getType() == Token_Bool );
  ASSERT_TRUE( tok->toString() == "1:3\treserv\t BOOL");
  ASSERT_TRUE( tok->getNumChildren() == 2 );
  
  Token * t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_Identifier );
  ASSERT_TRUE( t->toString() == "1:8\tident\t b");
  ASSERT_TRUE( dynamic_cast<IdentifierToken *>(t)->getVal() == "b");
  
  t = tok->getChild(1);
  ASSERT_TRUE( t->getType() == Token_BooleanLiteral );
  ASSERT_TRUE( t->toString() == "1:10\tbool\t TRUE");
  ASSERT_TRUE( dynamic_cast<BooleanLiteralToken *>(t)->getVal() == true);  

}

// -----------
TEST(Parser, parse_vec3) {
  {
    std::istringstream iss("( vec3 pos ) ");

    Parser p;
    Token *tok = p.parse( iss );
    
    ASSERT_TRUE( tok->getType() == Token_Vec3 );
    ASSERT_TRUE( tok->toString() == "1:3\treserv\t VEC3");
    ASSERT_TRUE( tok->getNumChildren() == 1 );
    
    Token * t = tok->getChild(0);
    ASSERT_TRUE( t->getType() == Token_Identifier );
    ASSERT_TRUE( t->toString() == "1:8\tident\t pos");
    ASSERT_TRUE( dynamic_cast<IdentifierToken *>(t)->getVal() == "pos");
   
  }
    
  {
    std::istringstream iss("( vec3 pos [0.0 1.0 2.0] ) ");

    Parser p;
    Token *tok = p.parse( iss );
    
    ASSERT_TRUE( tok->getType() == Token_Vec3 );
    ASSERT_TRUE( tok->toString() == "1:3\treserv\t VEC3");
    ASSERT_TRUE( tok->getNumChildren() == 2 );
    
    Token * t = tok->getChild(0);
    ASSERT_TRUE( t->getType() == Token_Identifier );
    ASSERT_TRUE( t->toString() == "1:8\tident\t pos");
    ASSERT_TRUE( dynamic_cast<IdentifierToken *>(t)->getVal() == "pos");

    t = tok->getChild(1);
    ASSERT_TRUE( t->getType() == Token_SquareBrackets );
    ASSERT_TRUE( t->toString() == "1:12\treserv\t SQUAREBRACKETS");
    ASSERT_TRUE( t->getNumChildren() == 3);

    Token *tokChild = t->getChild(0);
    ASSERT_TRUE( tokChild->getType() == Token_FloatLiteral );
    ASSERT_TRUE( tokChild->toString() == "1:13\tfloat\t 0");
    ASSERT_TRUE( dynamic_cast<FloatLiteralToken *>(tokChild)->getVal() == 0.0f );

    tokChild = t->getChild(1);
    ASSERT_TRUE( tokChild->getType() == Token_FloatLiteral );
    ASSERT_TRUE( tokChild->toString() == "1:17\tfloat\t 1");
    ASSERT_TRUE( dynamic_cast<FloatLiteralToken *>(tokChild)->getVal() == 1.0f );

    tokChild = t->getChild(2);
    ASSERT_TRUE( tokChild->getType() == Token_FloatLiteral );
    ASSERT_TRUE( tokChild->toString() == "1:21\tfloat\t 2");
    ASSERT_TRUE( dynamic_cast<FloatLiteralToken *>(tokChild)->getVal() == 2.0f );
   
  }

}

// -----------
TEST(Parser, playSound) {
  std::istringstream iss("( playsound \"sounds/menu_back.wav\" ) ");

  Parser p;
  Token *tok = p.parse( iss );
  
  ASSERT_TRUE( tok->getType() == Token_PlaySound);
  ASSERT_TRUE( tok->toString() == "1:3\treserv\t PLAYSOUND");
  ASSERT_TRUE( tok->getNumChildren() == 1 );
  
  Token * t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_StringLiteral );
  ASSERT_TRUE( t->toString() == "1:13\tstring\t sounds/menu_back.wav");
  ASSERT_TRUE( dynamic_cast<StringLiteralToken *>(t)->getVal() == "sounds/menu_back.wav"); 

}

// -----------
TEST(Parser, draw) {
  std::istringstream iss("( draw \"fireball\" 50.0 30.0 ) ");

  Parser p;
  Token *tok = p.parse( iss );
  
  ASSERT_TRUE( tok->getType() == Token_Draw );
  ASSERT_TRUE( tok->toString() == "1:3\treserv\t DRAW");
  ASSERT_TRUE( tok->getNumChildren() == 3 );
  
  Token * t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_StringLiteral );
  ASSERT_TRUE( t->toString() == "1:8\tstring\t fireball");
  ASSERT_TRUE( dynamic_cast<StringLiteralToken *>(t)->getVal() == "fireball"); 

  t = tok->getChild(1);
  ASSERT_TRUE( t->getType() == Token_FloatLiteral );
  ASSERT_TRUE( t->toString() == "1:19\tfloat\t 50");
  ASSERT_TRUE( dynamic_cast<FloatLiteralToken *>(t)->getVal() == 50.0f); 

  t = tok->getChild(2);
  ASSERT_TRUE( t->getType() == Token_FloatLiteral );
  ASSERT_TRUE( t->toString() == "1:24\tfloat\t 30");
  ASSERT_TRUE( dynamic_cast<FloatLiteralToken *>(t)->getVal() == 30.0f); 

}

// -----------
TEST(Parser, progn_print_println) {
  // 1 (progn (println "Hello There!") 
  // 2  (print "How" " are" " you?")
  std::istringstream iss("(progn (println \"Hello there!\") \n (print \"How\" \" are\" \" you?\") " );

  Parser p;
  Token *tok = p.parse(iss);

  ASSERT_TRUE( tok->getType() == Token_Progn );
  ASSERT_TRUE( tok->toString() == "1:2\treserv\t PROGN");
  ASSERT_TRUE( tok->getNumChildren() == 2 );
  
  
  // println
  Token *t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_Println );
  ASSERT_TRUE( t->toString() == "1:9\treserv\t PRINTLN");
  ASSERT_TRUE( t->getNumChildren() == 1 );
    
  Token *tokChild = t->getChild(0);
  ASSERT_TRUE( tokChild != NULL);
  ASSERT_TRUE( tokChild->getType() == Token_StringLiteral );
  ASSERT_TRUE( tokChild->toString() == "1:17\tstring\t Hello there!");
  ASSERT_TRUE( dynamic_cast<StringLiteralToken *>(tokChild)->getVal() == "Hello there!");
  ASSERT_TRUE( tokChild->getNumChildren() == 0 );
 
 
  // print
  t = tok->getChild(1);
  ASSERT_TRUE( t->getType() == Token_Print );
  ASSERT_TRUE( t->toString() == "2:3\treserv\t PRINT");
  ASSERT_TRUE( t->getNumChildren() == 3 );
    
  tokChild = t->getChild(0);
  ASSERT_TRUE( tokChild->getType() == Token_StringLiteral );
  ASSERT_TRUE( tokChild->toString() == "2:9\tstring\t How");
  ASSERT_TRUE( dynamic_cast<StringLiteralToken *>(tokChild)->getVal() == "How");
  ASSERT_TRUE( tokChild->getNumChildren() == 0 );

  tokChild = t->getChild(1);
  ASSERT_TRUE( tokChild->getType() == Token_StringLiteral );
  ASSERT_TRUE( tokChild->toString() == "2:15\tstring\t  are");
  ASSERT_TRUE( dynamic_cast<StringLiteralToken *>(tokChild)->getVal() == " are");
  ASSERT_TRUE( tokChild->getNumChildren() == 0 );

  tokChild = t->getChild(2);
  ASSERT_TRUE( tokChild->getType() == Token_StringLiteral );
  ASSERT_TRUE( tokChild->toString() == "2:22\tstring\t  you?");
  ASSERT_TRUE( dynamic_cast<StringLiteralToken *>(tokChild)->getVal() == " you?");
  ASSERT_TRUE( tokChild->getNumChildren() == 0 );
    
}

// -----------
TEST(Parser, envAccess) {
  std::istringstream iss("@sys:frameTicks" );

  Parser p;
  Token *tok = p.parse(iss);

  ASSERT_TRUE( tok->getType() == Token_EnvAccess );
  ASSERT_TRUE( tok->toString() == "1:1\tsymbol\t ENVACCESS");
  ASSERT_TRUE( tok->getNumChildren() == 3 );
  
  Token *t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_Identifier );
  ASSERT_TRUE( t->toString() == "1:2\tident\t sys");
  ASSERT_TRUE( t->getNumChildren() == 0 );

  t = tok->getChild(1);
  ASSERT_TRUE( t->getType() == Token_Colon );
  ASSERT_TRUE( t->toString() == "1:5\tsymbol\t COLON");
  ASSERT_TRUE( t->getNumChildren() == 0 );
  
  t = tok->getChild(2);
  ASSERT_TRUE( t->getType() == Token_Identifier );
  ASSERT_TRUE( t->toString() == "1:6\tident\t frameticks");
  ASSERT_TRUE( t->getNumChildren() == 0 );
  
}

// -----------
TEST(Parser, envAccess2) {
  std::istringstream iss("(int i @sys:frameTicks)" );

  Parser p;
  Token *tok = p.parse(iss);

  ASSERT_TRUE( tok->getType() == Token_Int );
  ASSERT_TRUE( tok->toString() == "1:2\treserv\t INT");
  ASSERT_TRUE( tok->getNumChildren() == 2 );
  
  Token *t = tok->getChild(0);
  ASSERT_TRUE( t->getType() == Token_Identifier );
  ASSERT_TRUE( t->toString() == "1:6\tident\t i");
  ASSERT_TRUE( t->getNumChildren() == 0 );

  t = tok->getChild(1);
  ASSERT_TRUE( t->getType() == Token_EnvAccess );
  ASSERT_TRUE( t->toString() == "1:8\tsymbol\t ENVACCESS");
  ASSERT_TRUE( t->getNumChildren() == 3 );
  
  // envaccess children
  Token *t2 = t->getChild(0);
  ASSERT_TRUE( t2->getType() == Token_Identifier );
  ASSERT_TRUE( t2->toString() == "1:9\tident\t sys");
  ASSERT_TRUE( t2->getNumChildren() == 0 );

  t2 = t->getChild(1);
  ASSERT_TRUE( t2->getType() == Token_Colon );
  ASSERT_TRUE( t2->toString() == "1:12\tsymbol\t COLON");
  ASSERT_TRUE( t2->getNumChildren() == 0 );
  
  t2 = t->getChild(2);
  ASSERT_TRUE( t2->getType() == Token_Identifier );
  ASSERT_TRUE( t2->toString() == "1:13\tident\t frameticks");
  ASSERT_TRUE( t2->getNumChildren() == 0 );
   
}

#endif

// -----------
// Script
// -----------
#ifdef TEST_SCRIPT

TEST(execute, print_println) {
  // 1 (progn (println "Hello There!") 
  // 2  (print "How" " are" " you?")
  std::istringstream iss("(progn (println \"Hello there!\") \n (print \"How\" \" are\" \" you?\") " );

  Parser p;
  Token *tok = p.parse(iss);


  Environment envLocal;
  System sys;
  std::ostringstream oss;
  
  tok->execute(envLocal, sys, oss);

  ASSERT_TRUE(oss.str() == "Hello there!\nHow are you?");
  
}

// -----------------------------------------
TEST(execute, literals) {
  std::istringstream iss("(progn (println \"Begin.\") false true \"hello\" 5 123.4 0 (println \"End.\") )");

  Parser p;
  Token *tok = p.parse(iss);

  Environment envLocal;
  System sys;
  std::ostringstream oss;
  
  tok->getChild(0)->execute(envLocal, sys, oss);
  ASSERT_TRUE( oss.str() == "Begin.\n");
  
  ASSERT_TRUE( tok->getChild(1)->execute(envLocal, sys, oss) == false );
  ASSERT_TRUE( tok->getChild(2)->execute(envLocal, sys, oss) == true );
  ASSERT_TRUE( tok->getChild(3)->execute(envLocal, sys, oss) == "hello");
  ASSERT_TRUE( tok->getChild(4)->execute(envLocal, sys, oss) == 5);
  ASSERT_TRUE( tok->getChild(5)->execute(envLocal, sys, oss) == 123.4f);
  ASSERT_TRUE( tok->getChild(6)->execute(envLocal, sys, oss) == 0);

  tok->getChild(7)->execute(envLocal, sys, oss);
  ASSERT_TRUE( oss.str() == "Begin.\nEnd.\n");
  
}

// -----------------------------------------
TEST(execute, declarations) {
  std::istringstream iss("(progn (println \"Begin.\") (bool b1) (bool b2 false) (bool b3 true) (int i) (int j -3) (int k 7) (int l 0) (float f) (float g 3.14) (float h -1.618) (float t 0.0) (vec3 pos [0.0 1.0 2.0]) (println \"End.\") )");

  Parser p;
  Token *tok = p.parse(iss);

  Environment envLocal;
  System sys;
  std::ostringstream oss;

  tok->execute(envLocal, sys, oss);

  ASSERT_TRUE( envLocal.get("b1") == false );
  ASSERT_TRUE( envLocal.get("b2") == false );
  ASSERT_TRUE( envLocal.get("b3") == true );

  ASSERT_TRUE( envLocal.get("i") == 0 );
  ASSERT_TRUE( envLocal.get("j") == -3 );
  ASSERT_TRUE( envLocal.get("k") == 7 );
  ASSERT_TRUE( envLocal.get("l") == 0 );

  ASSERT_TRUE( envLocal.get("f") == 0.0f);
  ASSERT_TRUE( envLocal.get("g") == 3.14f );
  ASSERT_TRUE( envLocal.get("h") == -1.618f);
  ASSERT_TRUE( envLocal.get("t") == 0.0f);
  
  ASSERT_TRUE( envLocal.get("pos") == Variant(Vec3(0, 1, 2)) );
    
  ASSERT_TRUE( oss.str() == "Begin.\nEnd.\n" );

}

// -----------------------------------------
TEST(execute, localVars) {
  std::istringstream iss("(progn (bool b true) (int x 3) (float f 7.02) (string s \"locvar\") b x f s (println \"Done.\") ) ");

  Parser p;
  Token *tok = p.parse(iss);

  Environment envLocal;
  System sys;
  std::ostringstream oss;

  tok->execute(envLocal, sys, oss);

  ASSERT_TRUE( envLocal.get("b") == true );
  ASSERT_TRUE( envLocal.get("x") == 3 );
  ASSERT_TRUE( envLocal.get("f") == 7.02f );
  ASSERT_TRUE( envLocal.get("s") == "locvar" );
  ASSERT_TRUE( oss.str() == "Done.\n" );
  
  ASSERT_TRUE( tok->getChild(4)->execute(envLocal, sys, oss) == true) ;
  ASSERT_TRUE( tok->getChild(5)->execute(envLocal, sys, oss) == 3) ;
  ASSERT_TRUE( tok->getChild(6)->execute(envLocal, sys, oss) == 7.02f) ;
  ASSERT_TRUE( tok->getChild(7)->execute(envLocal, sys, oss) == "locvar") ;
  
}

// -----------------------------------------
TEST(execute, conditionals) {
  {
    std::istringstream iss("(progn (bool b true) (println \"Begin.\") (if (== b true) (progn (int x 3) (println x)) (float y 7.12)) (println \"End.\") )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("b") == true );
    ASSERT_TRUE( envLocal.get("x") == 3 );
    ASSERT_TRUE( oss.str() == "Begin.\n3\nEnd.\n" );
  
  }
    
  {
    std::istringstream iss("(progn (bool b false) (println \"Begin.\") (if (== b true) (int x 3) (progn (float y 7.12) (println y) )) (println \"End.\") )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("b") == false );
    ASSERT_TRUE( envLocal.get("y") == 7.12f );
    ASSERT_TRUE( oss.str() == "Begin.\n7.12\nEnd.\n" );
  
  }
  
}

// -----------------------------------------
TEST(execute, dotimes_loop) {
  {
    std::istringstream iss("(dotimes 5 (println \"hello\"))");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( oss.str() == "hello\nhello\nhello\nhello\nhello\n" );
  
  }

  {
    std::istringstream iss("(progn (float f 2.0) (dotimes 7 (+= f 3.0) )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("f") == 23.0f );
  
  }
  
  {
    std::istringstream iss("(progn (bool b false) (dotimes 3 (= b (not b)) ) )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("b") == true );
  
  }
  
}

// -----------------------------------------
TEST(execute, while_loop) {
  {
    std::istringstream iss("(progn (int i 0) (while (!= i 5) (progn (print i \"..\") (++ i) ) ) (println \"Done.\") )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( oss.str() == "0..1..2..3..4..Done.\n" );
  
  }
  
}

// -----------------------------------------
TEST(execute, randomVals) {
  srand(0);

  {
    std::istringstream iss("(progn (int i 0) (= i (randi 5 15) ) )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    int i = envLocal.get("i").getInteger();

    ASSERT_TRUE( i >= 5 && i < 15 );
  
  }
  
  {
    std::istringstream iss("(progn (int i 0) (= i (randi -10 2) ) )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    int i = envLocal.get("i").getInteger();

    ASSERT_TRUE( i >= -10 && i < 2 );
  
  }
  
  {
    std::istringstream iss("(progn (float f 0.0) (= f (randf -3.0 3.0) ) )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    float f = envLocal.get("f").getFloat();

    ASSERT_TRUE( f >= -3.0f && f < 3.0f );
  
  }
  
  {
    std::istringstream iss("(progn (float f 0.0) (= f (randf 5.0 20.0) ) )");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    float f = envLocal.get("f").getFloat();

    ASSERT_TRUE( f >= 5.0 && f < 20.0f );
  
  }
  
}

// -----------------------------------------
TEST(execute, logicalOps) {
  // ******** AND *********
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (bool b1 false) (bool b2 false) (bool b3 false) (if (and b1 b2 b3) (println \"All true.\") (println \"Not all true.\")) )");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b1") == false);
    ASSERT_TRUE(envLocal.get("b2") == false);
    ASSERT_TRUE(envLocal.get("b3") == false);
    ASSERT_TRUE(oss.str() == "Not all true.\n");

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (bool b1 false) (bool b2 true) (bool b3 false) (if (and b1 b2 b3) (println \"All true.\") (println \"Not all true.\")) )");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b1") == false);
    ASSERT_TRUE(envLocal.get("b2") == true);
    ASSERT_TRUE(envLocal.get("b3") == false);
    ASSERT_TRUE(oss.str() == "Not all true.\n");

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (bool b1 true) (bool b2 true) (bool b3 true) (if (and b1 b2 b3) (println \"All true.\") (println \"Not all true.\")) )");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b1") == true);
    ASSERT_TRUE(envLocal.get("b2") == true);
    ASSERT_TRUE(envLocal.get("b3") == true);
    ASSERT_TRUE(oss.str() == "All true.\n");

  }

  // ****** OR ********
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (bool b1 false) (bool b2 false) (bool b3 false) (if (or b1 b2 b3) (println \"Some true.\") (println \"None true.\")) )");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b1") == false);
    ASSERT_TRUE(envLocal.get("b2") == false);
    ASSERT_TRUE(envLocal.get("b3") == false);
    ASSERT_TRUE(oss.str() == "None true.\n");

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (bool b1 false) (bool b2 false) (bool b3 true) (if (or b1 b2 b3) (println \"Some true.\") (println \"None true.\")) )");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b1") == false);
    ASSERT_TRUE(envLocal.get("b2") == false);
    ASSERT_TRUE(envLocal.get("b3") == true);
    ASSERT_TRUE(oss.str() == "Some true.\n");

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (int x 3) (bool b2 false) (bool b3 false) (if (or (== x 3) b2 b3) (println \"Some true.\") (println \"None true.\")) )");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("x") == 3);
    ASSERT_TRUE(envLocal.get("b2") == false);
    ASSERT_TRUE(envLocal.get("b3") == false);
    ASSERT_TRUE(oss.str() == "Some true.\n");

  }
  
  // ****** NOT *******
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (float f 7.0) (if (not (== f 7.0)) (println \"f is not 7.0\") (println \"f is 7.0\")))");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("f") == 7.0f);
    ASSERT_TRUE(oss.str() == "f is 7.0\n");

  }
 
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;
  
    std::istringstream iss("(progn (float f 3.0) (if (not (== f 7.0)) (println \"f is not 7.0\") (println \"f is 7.0\")))");
    
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("f") == 3.0f);
    ASSERT_TRUE(oss.str() == "f is not 7.0\n");

  }
  
}

// -----------------------------------------
TEST(execute, arithmetic) {
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(progn (int i 7) (++ i) (++ i) (print \"i is \" i))");
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 9);
    ASSERT_TRUE(oss.str() == "i is 9");

  }

  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (++ i) (-- i) (-- i) (print \"i is \" i))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 6);
    ASSERT_TRUE(oss.str() == "i is 6");

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (+= i 3))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 10);

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (-= i 3))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 4);

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (*= i 3))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 21);

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (/= i 3))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 2);

  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (+= i 3.5))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 10.5f);

  }

  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 7) (-= i 1.5))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 5.5f);

  }

//  {
//    Environment envLocal;
//    System sys;
//    std::ostringstream oss;  
//    
//    std::istringstream iss("(progn (int i 7) (*= i 8.1))");
//    Parser p;
//    Token *tok = p.parse(iss);
//    
//    tok->execute(envLocal, sys, oss);
//    
//    ASSERT_TRUE(envLocal.get("i") == 56.7f);
//
//  }
  
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;  
    
    std::istringstream iss("(progn (int i 10) (/= i 2.5))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 4.0f);

  }

}

// -----------------------------------------
TEST(execute, assign) {
  Environment envLocal;
  System sys;
  std::ostringstream oss;
  
  {
    std::istringstream iss("(progn (bool b false) (int i 3) (float f 1.12) (string s \"hello\"))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b") == false);
    ASSERT_TRUE(envLocal.get("i") == 3);
    ASSERT_TRUE(envLocal.get("f") == 1.12f);
    ASSERT_TRUE(envLocal.get("s") == "hello");

  }


  {
    std::istringstream iss("(progn (= b true) (= i 7) (= f 3.14) (= s \"world!\"))");
    Parser p;
    Token *tok = p.parse(iss);
    
    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("b") == true);
    ASSERT_TRUE(envLocal.get("i") == 7);
    ASSERT_TRUE(envLocal.get("f") == 3.14f);
    ASSERT_TRUE(envLocal.get("s") == "world!");

  }

}

// -----------------------------------------
TEST(execute, equality) {
  {
    std::istringstream iss("(progn (bool b1 true) (bool b2 false) (if (== b1 b2) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("b1") == true );
    ASSERT_TRUE( envLocal.get("b2") == false );
    ASSERT_TRUE( oss.str() == "Different.\n" );
  
  }

  {
    std::istringstream iss("(progn (bool b1 true) (bool b2 true) (if (== b1 b2) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("b1") == true );
    ASSERT_TRUE( envLocal.get("b2") == true );
    ASSERT_TRUE( oss.str() == "Same.\n" );
  
  }
  
  {
    std::istringstream iss("(progn (int i) (int j 127) (if (== i j) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("i") == 0 );
    ASSERT_TRUE( envLocal.get("j") == 127 );
    ASSERT_TRUE( oss.str() == "Different.\n" );
  
  }
  
  {
    std::istringstream iss("(progn (int i 127) (int j 127) (if (== i j) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("i") == 127 );
    ASSERT_TRUE( envLocal.get("j") == 127 );
    ASSERT_TRUE( oss.str() == "Same.\n" );
  
  }
  
  {
    std::istringstream iss("(progn (int i 127) (int j 127) (if (!= i j) (println \"Different.\") (println \"Same.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("i") == 127 );
    ASSERT_TRUE( envLocal.get("j") == 127 );
    ASSERT_TRUE( oss.str() == "Same.\n" );
  
  }
  
  {
    std::istringstream iss("(progn (int i 0) (int j 127) (if (!= i j) (println \"Different.\") (println \"Same.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("i") == 0 );
    ASSERT_TRUE( envLocal.get("j") == 127 );
    ASSERT_TRUE( oss.str() == "Different.\n" );
  
  }

  {
    std::istringstream iss("(progn (float f 64.0) (float g 64.0) (if (== f g) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("f") == 64.0f );
    ASSERT_TRUE( envLocal.get("g") == 64.0f );
    ASSERT_TRUE( oss.str() == "Same.\n" );
  
  }
  
  {
    std::istringstream iss("(progn (string s \"Test\") (string t \"Test\") (if (== s t) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("s") == "Test" );
    ASSERT_TRUE( envLocal.get("t") == "Test" );
    ASSERT_TRUE( oss.str() == "Same.\n" );
  
  }

  {
    std::istringstream iss("(progn (string s \"Test\") (string t \"Test2\") (if (== s t) (println \"Same.\") (println \"Different.\"))) ");

    Parser p;
    Token *tok = p.parse(iss);

    Environment envLocal;
    System sys;
    std::ostringstream oss;

    tok->execute(envLocal, sys, oss);

    ASSERT_TRUE( envLocal.get("s") == "Test" );
    ASSERT_TRUE( envLocal.get("t") == "Test2" );
    ASSERT_TRUE( oss.str() == "Different.\n" );
  
  }
  
}

// -----------------------------------------
TEST(execute, defun) {
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(defun \"SimpleHello\" (println \"Hello.\"))");
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(oss.str() == "Hello.\n");

  }

  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(defun \"ComplexFunc\" (progn (int i 7) (++ i) (++ i) (-- i) (print \"i is \" i))");
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 8);
    ASSERT_TRUE(oss.str() == "i is 8");

  }

}

// -----------------------------------------
TEST(execute, main) {
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(script \"test execute main 1\" (defun \"main\" (println \"Hello.\")))");
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(oss.str() == "Hello.\n");

  }

  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(script \"test execute main 2\" (defun \"main\" (progn (int i 7) (++ i) (++ i) (-- i) (print \"i is \" i) ) ) )");
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE(envLocal.get("i") == 8);
    ASSERT_TRUE(oss.str() == "i is 8");

  }

}

// -----------------------------------------
TEST(execute, callFunc) {
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(script \"test callfunc 1\"  (defun \"main\" (println)) (defun \"print_hello\" (println \"Hello2.\")))");
    Parser p;
    Token *tok = p.parse(iss);

    ScriptToken *tokScript = dynamic_cast<ScriptToken *>(tok);
    tokScript->call("print_hello", envLocal, sys, oss);
    
    ASSERT_TRUE(oss.str() == "Hello2.\n");

  }

  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(script  \"test callfunc 2\" (defun \"main\" (int x 0))      (defun \"plx\" (println \"x is \" x))     (defun \"incx\" (++ x) )  )");
    Parser p;
    Token *tok = p.parse(iss);

    // dyncast so we can do some calls.
    ScriptToken *tokScript = dynamic_cast<ScriptToken *>(tok);
    tokScript->call("main", envLocal, sys, oss);
    tokScript->call("plx", envLocal, sys, oss);
    tokScript->call("incx", envLocal, sys, oss);
    tokScript->call("incx", envLocal, sys, oss);
    tokScript->call("plx", envLocal, sys, oss);
        
    ASSERT_TRUE(envLocal.get("x") == 2);
    ASSERT_TRUE(oss.str() == "x is 0\nx is 2\n");

  }

}

// -----------------------------------------
TEST(execute, hasFunction) {
  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(script  \"test hasFunction 1\" (defun \"main\" (println)) (defun \"print_hello\" (println \"Hello2.\")))");
    Parser p;
    Token *tok = p.parse(iss);

    ScriptToken *tokScript = dynamic_cast<ScriptToken *>(tok);
    
    ASSERT_TRUE( tokScript->hasFunction("main") );
    ASSERT_TRUE( tokScript->hasFunction("print_hello") );
    ASSERT_TRUE( ! tokScript->hasFunction("think") );
    ASSERT_TRUE( ! tokScript->hasFunction("render") );
    
  }

  {
    Environment envLocal;
    System sys;
    std::ostringstream oss;    
    
    std::istringstream iss("(script  \"test hasFunction 2\" (defun \"main\" (int x 0))      (defun \"plx\" (println \"x is \" x))     (defun \"incx\" (++ x) )  )");
    Parser p;
    Token *tok = p.parse(iss);

    // dyncast so we can do some calls.
    ScriptToken *tokScript = dynamic_cast<ScriptToken *>(tok);

    ASSERT_TRUE( tokScript->hasFunction("main") );
    ASSERT_TRUE( tokScript->hasFunction("plx") );
    ASSERT_TRUE( tokScript->hasFunction("incx") );
    ASSERT_TRUE( ! tokScript->hasFunction("think") );
    ASSERT_TRUE( ! tokScript->hasFunction("render") );

  }

}

// -----------------------------------------
TEST(execute, playSounds) {
  int sdlInitResult = SDL_Init(SDL_INIT_AUDIO);
  ASSERT_TRUE(sdlInitResult >= 0);

  
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  ASSERT_TRUE(audioInitResult != -1);
  
  
  Environment envLocal;
  System sys;
    sys.Register("sounds/menu_enter.wav");
    sys.Register("sounds/menu_back.wav");
    sys.Register("sounds/explodelow.wav");
    
  {
    std::istringstream iss("( PlaySound \"sounds/menu_enter.wav\" )" );

    std::ostringstream oss;
  
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    SDLClock c;
    while(c.getSecsElapsed() < 1.0f) {
      c.tick();
    
    }
  
  }
  
  {
    std::istringstream iss("( PlaySound    \"sounds/menu_back.wav\" )" );

    std::ostringstream oss;
    
    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    SDLClock c;
    while(c.getSecsElapsed() < 1.0f) {
      c.tick();
    
    }
  
  }
  
  {
    std::istringstream iss("(progn (string s \"sounds/explodelow.wav\") (playsound s)" );

    std::ostringstream oss;

    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    SDLClock c;
    while(c.getSecsElapsed() < 2.0f) {
      c.tick();
    
    }
  
  }
  
  Mix_CloseAudio();
  SDL_Quit();
  
}

// -----------------------------------------
TEST(execute, envAccess_read) {
  Environment envLocal;
  System sys;
    sys.env().declare("frameticks", Variant(13));
  std::ostringstream oss;
  
  {
    std::istringstream iss("(progn (int i @sys:frameticks) (println i \" ticks.\") )" );

    Parser p;
    Token *tok = p.parse(iss);

    tok->execute(envLocal, sys, oss);
    
    ASSERT_TRUE( sys.env().get("frameticks") == 13); 
    ASSERT_TRUE( envLocal.get("i") == 13); 
    ASSERT_TRUE( oss.str() == "13 ticks.\n");
     
  }

}

// -----------------------------------------
TEST(execute, exec) {
  int sdlInitResult = SDL_Init(SDL_INIT_AUDIO);
  ASSERT_TRUE(sdlInitResult >= 0);

  
  int audioInitResult = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  ASSERT_TRUE(audioInitResult != -1);
  
  System sys;
    sys.Register("sounds/explodelow.wav");
    sys.exec("(playsound \"sounds/explodelow.wav\")");

  while(sys.clock()->getSecsElapsed() < 2.0f) {
    sys.clock()->tick();
  
  }
  
  Mix_CloseAudio();
  SDL_Quit();

}

// -----------------------------------------
TEST(script, test_1) {
  System sys;
    sys.Register("scripts/test_1.scr");

  ScriptInstance *scrInst = sys.createScriptInstance("scripts/test_1.scr");
  scrInst->call("think");
  scrInst->call("draw");
  scrInst->call("think");
  scrInst->call("draw");
  scrInst->call("think");
  scrInst->call("draw");
  
  ASSERT_TRUE( scrInst->get("i") == 6);
  ASSERT_TRUE( scrInst->get("f") == 78.0f);
  ASSERT_TRUE( scrInst->get("b") == true);
  ASSERT_TRUE( scrInst->get("s") == "hello world!");

}

#endif

// -----------
// System
// -----------
#ifdef TEST_SYSTEM

TEST(system, init) {
  {
    System sys;
      sys.init(640, 480);
    
      sys.Register("images/bomb.png");
      sys.Register("sounds/explodelow.wav");
      
      while(sys.clock()->getSecsElapsed() < 4.0f) {
        sys.clock()->tick();
                
      }
  
    sys.shutdown();
  
  }

}

// -----------------------------------------
TEST(system, init_twice) {
  {
    System sys;
      sys.init(320, 240);
    
      sys.Register("images/bomb.png");
      sys.Register("sounds/explodelow.wav");
      
      while(sys.clock()->getSecsElapsed() < 2.0f) {
        sys.clock()->tick();
                
      }
  
    sys.shutdown();
  
  }

  {
    System sys;
      sys.init(640, 480);
    
      sys.Register("images/bomb.png");
      sys.Register("sounds/explodelow.wav");
      
      while(sys.clock()->getSecsElapsed() < 4.0f) {
        sys.clock()->tick();
                
      }
  
    sys.shutdown();
  
  }

}

#endif