//
//  Environment.c++
//  Tech1
//
//  Created by Justin Hust on 12/14/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Environment.h"

// ---------------------------------------------------
Environment::Environment(void) {
  // no init yet

}

// ---------------------------------------------------
Environment::~Environment(void) {
  // no cleanup yet

}

// ---------------------------------------------------
void Environment::declare(const std::string &sKey, const Variant &defaultVal) {
  _vars.insert( std::make_pair(sKey, defaultVal));

}

// ---------------------------------------------------
void Environment::set(const std::string &sKey, const Variant &val) {
  std::map<std::string, Variant>::iterator it = _vars.find(sKey);
  assert(it != _vars.end() );
  // todo: re-enable this: assert(it->second.getType() == val.getType());
  
  it->second = val;

}

// ---------------------------------------------------
Variant Environment::get(const std::string &sKey) const {
  std::map<std::string, Variant>::const_iterator it = _vars.find(sKey);
  assert(it != _vars.end() );
  
  return it->second;

}

// ---------------------------------------------------
EnvironmentMgr::EnvironmentMgr(void) {
  // no init yet

}

// ---------------------------------------------------
EnvironmentMgr::~EnvironmentMgr(void) {
  // no cleanup yet

}

// ---------------------------------------------------
Environment * EnvironmentMgr::create(const std::string &sKey) {
  Environment * newEnv = new Environment();

  _envs.insert( std::make_pair(sKey, newEnv ) );
  
  return newEnv;

}

// ---------------------------------------------------
Environment * EnvironmentMgr::lookup(const std::string &sKey) {
  std::map<std::string, Environment *>::iterator it = _envs.find(sKey);
  assert( it != _envs.end() );
  
  return dynamic_cast<Environment *>(it->second);

}

// ---------------------------------------------------
