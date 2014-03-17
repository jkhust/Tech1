//
//  Reporter.c++
//  Tech1
//
//  Created by Justin Hust on 12/8/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "Reporter.h"

// ---------------------------------------------------------
Reporter::Reporter(void) {
  _sReportPath = "/users/jkhust/Documents/Coding/Tech1/Tech1/Logs";
  
  _chanAll = new std::ofstream( std::string(_sReportPath + "/log_all.txt").c_str() );
  _chanSys = new std::ofstream( std::string(_sReportPath + "/log_sys.txt").c_str() );
  _chanConsole = &std::cout;
  _chanResources = new std::ofstream( std::string(_sReportPath + "/log_res.txt").c_str() );
  _chanVideo = new std::ofstream( std::string(_sReportPath + "/log_video.txt").c_str() );
  _chanAudio = new std::ofstream( std::string(_sReportPath + "/log_audio.txt").c_str() );
  _chanScripting = new std::ofstream(std::string(_sReportPath + "/log_scripting.txt").c_str() );
  _chanFatalErrors = &std::cout;
  
}

// ---------------------------------------------------------
Reporter::~Reporter(void) {
  if(_chanAll != NULL) {
    delete _chanAll;
    _chanAll = NULL;
  
  }
  
  if(_chanSys != NULL) {
    delete _chanSys;
    _chanSys = NULL;
  
  }

  if(_chanResources != NULL) {
    delete _chanResources;
    _chanResources = NULL;
  
  }

  if(_chanVideo != NULL) {
    delete _chanVideo;
    _chanVideo = NULL;
  
  }
 
  if(_chanAudio != NULL) {
    delete _chanAudio;
    _chanAudio = NULL;
  
  }
 
  if(_chanScripting != NULL) {
    delete _chanScripting;
    _chanScripting = NULL;
  
  }

}

// ---------------------------------------------------------
void Reporter::system(const std::string &s) {
  if(_chanSys != NULL) {
    (*_chanSys) << s;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[System] " << s;
  
  }

}

// ---------------------------------------------------------
void Reporter::console(const std::string &s) {
  if(_chanConsole != NULL) {
    (*_chanConsole) << s;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[Console] " << s;
  
  }

}

// ---------------------------------------------------------
void Reporter::resources(const std::string &s) {
  if(_chanResources != NULL) {
    (*_chanResources) << s;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[Resources] " << s;
  
  }

}

// ---------------------------------------------------------
void Reporter::video(const std::string &s) {
  if(_chanVideo != NULL) {
    (*_chanVideo) << s;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[Video] " << s;
  
  }

}

// ---------------------------------------------------------
void Reporter::audio(const std::string &s) {
  if(_chanAudio != NULL) {
    (*_chanAudio) << s;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[Audio] " << s;
  
  }

}

// ---------------------------------------------------------
void Reporter::scripting(const std::string &s) {
  if(_chanScripting != NULL) {
    (*_chanScripting) << s;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[Scripting] " << s;
  
  }

}

// ---------------------------------------------------------
void Reporter::fatalError(const std::string &s) {
  if(_chanFatalErrors != NULL) {
    (*_chanFatalErrors) << s << std::endl;
    
  }

  if(_chanAll != NULL) {
    (*_chanAll) << "[Fatal Error] " << s << std::endl;
  
  }
  
  exit(-1);

}

// ---------------------------------------------------------
std::ostream * Reporter::getScripting(void) {
  return _chanScripting;

}