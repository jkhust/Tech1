//
//  Reporter.h
//  Tech1
//
//  Created by Justin Hust on 12/8/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Reporter_h
#define Tech1_Reporter_h

#include <stdio.h>
#include <iostream>

// ---------------------------------------------------------
class Reporter {
private:
  // UNIMPLEMENTED
    Reporter & operator = (const Reporter & r);
    bool operator == (const Reporter & r);
    Reporter(const Reporter & r);

  // DATA 
    // base path for reporting
    std::string _sReportPath;
    
    // all report channels
    std::ostream * _chanAll;
    std::ostream * _chanSys;
    std::ostream * _chanConsole;
    std::ostream * _chanResources;
    std::ostream * _chanVideo;
    std::ostream * _chanAudio;
    std::ostream * _chanScripting;
    std::ostream * _chanFatalErrors;
    
    // add more channels for editor, warnings, AI, etc.

public:
  // CREATORS
    Reporter(void);
    ~Reporter(void);

  // MANIPULATORS 
    // report to the proper channel
    void system(const std::string &s);
    void console(const std::string &s);
    void resources(const std::string &s);
    void video(const std::string &s);
    void audio(const std::string &s);
    void scripting(const std::string &s);
    void fatalError(const std::string &s);

  // ACCESSORS
    std::ostream * getScripting(void);

};

#endif