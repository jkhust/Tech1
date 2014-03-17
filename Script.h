//
//  Script.h
//  Tech1
//
//  Created by Justin Hust on 12/22/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Script_h
#define Tech1_Script_h

#include "Environment.h"
#include "Token.h"

class ScriptInstance {
private:
  // DATA
    Environment _env;
    ScriptToken * _tokCode;
    System & _sys;
    std::ostream & _os;

public:
  // CREATORS
    ScriptInstance(ScriptToken *tokCode, System &sys, std::ostream &os);
    ~ScriptInstance(void);
    
  // MANIPULATORS
    void set(const std::string &sField, Variant &val);
  
  // ACCESSORS
    void call(const std::string &sFuncName);
    bool hasFunction(const std::string &sFuncName);
    Variant get(const std::string &sField);

};

#endif