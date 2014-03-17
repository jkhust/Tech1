//
//  Lexer.h
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Lexer_h
#define Tech1_Lexer_h

#include <iostream>
#include <sstream>
#include "Token.h"

// *************************************************************
class Lexer {
private:
  // DATA
    std::istream & _iss;
    char _chNext;               // peeked next char
    char _chSkip;               // store skipped chars, never read.
  
    int _currLine;
    int _currLineStart;
  
  // UNIMPLEMENTED
    Lexer & operator = (const Lexer & lexOther_);
    Lexer & operator == (const Lexer & lexOther_);
    Lexer(Lexer &LexOther_);
    
  // PRIVATE ROUTINES
    bool peekNext(void);       
    bool nextIs(char c) const;
    bool nextIsAlpha(void) const;
    bool nextIsNumeric(void) const;
    bool nextIsSymbol(void) const;
    
    bool nextNextIs(char c);
    bool nextNextIsNumeric(void);
    bool nextTwoAre(char c1_, char c2_);
  
    void skipWhitespace(void);
    void skipChar(void);

  // CALLED FROM lex()
    Token * lexIdentifier(void);
    Token * lexNumber(void);
    Token * lexString(void);
    Token * lexSymbol(void);

public:
  // CREATORS
    Lexer(std::istream &iss);
    ~Lexer(void);
  
  // MANIPULATORS
    void reset(void);
    Token * lex(void);
  
};

#endif
