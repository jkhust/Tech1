//
//  Resource.h
//  Tech1
//
//  Created by Justin Hust on 12/8/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Resource_h
#define Tech1_Resource_h

#include "Token.h"
#include "Script.h"
#include <iostream>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"

// -----------------------------------------------------------
class Resource {
protected:
  // DATA
  std::string _sAbsPath;

public:
  // CREATORS
    Resource(const std::string &sAbsPath);
    virtual ~Resource(void);

  // MANIPULATORS
    virtual void load(void) = 0;

};

// -----------------------------------------------------------
class ImageResource : public Resource {
protected:
  SDL_Surface *_surf;

public:
  // CREATORS
    ImageResource(const std::string &sAbsPath);
    ~ImageResource(void);
  
  // MANIPULATORS
    void load(void);
    void draw(unsigned int x, unsigned int y, SDL_Surface *toSurf) const;
    
  // ACCESSORS
    unsigned int getWidth(void) const;
    unsigned int getHeight(void) const;
    unsigned int getBackColor(void) const;
    SDL_Surface * getSurface(void) const;

};

// -----------------------------------------------------------
class SpriteResource : public Resource {
protected:
  // DATA
    ImageResource *_fromImage;
 
    unsigned int _x1;
    unsigned int _y1;
    unsigned int _x2;
    unsigned int _y2;
 
public:
  // CREATORS
    SpriteResource(ImageResource *fromImage, 
                   unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
    ~SpriteResource(void);
  
  // MANIPULATORS
    void draw(unsigned int x, unsigned int y, SDL_Surface *toSurf) const;
    void load(void) { }
    
  // ACCESSORS
    unsigned int getWidth(void) const;
    unsigned int getHeight(void) const;
    unsigned int getBackColor(void) const;

};

// -----------------------------------------------------------
class SoundResource : public Resource {
protected:
  // DATA
    Mix_Chunk * _chunk;
  
public:
  // CREATORS
    SoundResource(const std::string &sAbsPath);
    ~SoundResource(void);

  // MANIPULATORS
    void load(void);
    void play(void);
  
  // ACCESSORS
  
};

// -----------------------------------------------------------
class MusicResource : public Resource {
protected:
  // DATA
    Mix_Music * _music;
  
public:
  // CREATORS
    MusicResource(const std::string &sAbsPath);
    ~MusicResource(void);

  // MANIPULATORS
    void load(void);
    void play(void);
    void stop(void);
  
    void pause(void);
    void resume(void);
  
  // ACCESSORS
  
};

// -----------------------------------------------------------
class ScriptResource : public Resource {
protected:
  // DATA
    Token * _tokCode;
    
public:
  // CREATORS
    ScriptResource(const std::string &sAbsPath);
    ~ScriptResource(void);

  // MANIPULATORS
    void load(void);
  
  // ACCESSORS
    ScriptInstance * createInstance(System &sys, std::ostream &os) const;
  
};

// -----------------------------------------------------------
class ResourceMgr {
private:
  // DATA
    std::string _sBasePath;
    std::map<std::string, Resource *> _resources;

public:
  // CREATORS
    ResourceMgr(void);

  // MANIPULATORS
    // register a resource - image, sound, or script.
    // based on the type of resource, will perform proper loading.
    Resource * Register(const std::string & pathKey);
    void unregister(const std::string &pathKey);
    
  // ACCESSORS
    Resource * get(const std::string & pathKey) const;

    SpriteResource * RegisterSprite(const std::string &spriteKey, const std::string &imageKey, 
                        unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
    
    void PlaySound(const std::string &sPathKey) const;
        
  // RegisterSprites("fonts/ffta_font.png", "A", "Z", 10, 10, 100)
  // skips blank pixels and produces accurate left/right coords for sprite.
  // 
  // concatimagekey makes "font.png" "A" become "font.png_A" as the resource identifier.
  // used to allow distinct fonts.
  //void RegisterSprites(const char *nameStart_, const char *nameEnd_, const char *imagePathKey_,
  //                                  u32 uLeft_, u32 uTop_, u32 uBottom_, bool bConcatImageKey);
  
};

#endif
