//
//  Environment.h
//  Tech1
//
//  Created by Justin Hust on 12/14/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Environment_h
#define Tech1_Environment_h

#include <map>
#include "Variant.h"
 
enum Environment_Type {
  Environment_Globals = 0,
  Environment_Player = 1

};

// ---------------------------------------------------
class Environment {
private:
  // DATA
    std::map<std::string, Variant> _vars;

public:
  // CREATORS
    Environment(void);
    ~Environment(void);
  
  // MANIPULATORS
    void declare(const std::string &sKey, const Variant &defaultVal);
    void set(const std::string &sKey, const Variant &val);

  // ACCESSORS
    Variant get(const std::string &sKey) const;
    
};

// ---------------------------------------------------
class EnvironmentMgr {
private:
  // DATA
    std::map<std::string, Environment *> _envs;
    
public:
  // CREATORS
    EnvironmentMgr(void);
    ~EnvironmentMgr(void);

  // MANIPULATORS
    Environment * create(const std::string &sKey);
    
  // ACCESSORS
    Environment * lookup(const std::string &sKey);

};

#endif