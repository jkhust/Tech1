//
//  Parser.h
//  Tech1
//
//  Created by Justin Hust on 12/17/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Parser_h
#define Tech1_Parser_h

#include <iostream>
#include <sstream>

class Token;

class Parser {
private:
  // DATA
    Token * _tokRoot;
    Token * _tokFocus;
    
    unsigned int _currScope;
    bool _nextIsNewFocus;

  // METHODS
    void accept(Token *tok);

public:
  // CREATORS
    Parser(void);
    ~Parser(void);
  
  // MANIPULATORS
  
  // ACCESSORS
    Token * parse(std::istream &iss);

};

#endif
