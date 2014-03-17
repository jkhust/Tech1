//
//  Script.c++
//  Tech1
//
//  Created by Justin Hust on 12/22/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Script.h"

#include "Token.h"
#include <iostream>

ScriptInstance::ScriptInstance(ScriptToken * tokCode, System &sys, std::ostream &os) : _sys(sys), _os(os) {
  _tokCode = tokCode;

}

// ----------------------------------------------------
ScriptInstance::~ScriptInstance(void) {
  // do NOT delete code token

}

// ----------------------------------------------------
void ScriptInstance::call(const std::string &sFuncName) {
  _tokCode->call(sFuncName, _env, _sys, _os);

}

// ----------------------------------------------------
bool ScriptInstance::hasFunction(const std::string &sFuncName) {
  return _tokCode->hasFunction(sFuncName);

}

// ----------------------------------------------------
void ScriptInstance::set(const std::string &sField, Variant &val) {
  _env.set(sField, val);

}

// ----------------------------------------------------
Variant ScriptInstance::get(const std::string &sField) {
  return _env.get(sField);

}