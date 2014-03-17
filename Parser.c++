//
//  Parser.c++
//  Tech1
//
//  Created by Justin Hust on 12/17/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Parser.h"
#include "Lexer.h"
#include "Token.h"

#include <iostream>
#include <cassert>

// ------------------------------------------
Parser::Parser(void) {
  _tokRoot = NULL;
  _tokFocus = NULL;
  
  //_currScope = 0;
  _nextIsNewFocus = false;

}

// ------------------------------------------
Parser::~Parser(void) {
  // no cleanup code yet

}

// ------------------------------------------
Token * Parser::parse(std::istream &iss) {
  Token *tok = NULL;
  
  Lexer l(iss);

  while( (tok = l.lex()) != NULL) {
    accept(tok);
  
  }
  
  assert(_tokRoot != NULL);
  
  return _tokRoot;

}

// ------------------------------------------
void Parser::accept(Token *tok) {
  //assert(_tokFocus != NULL);

  if(tok->getType() == Token_LPAR) {
    _nextIsNewFocus = true;
    //_currScope++;

  } else if(tok->getType() == Token_RPAR ) {  
    // validation OK, so move back up to parent
    _tokFocus = _tokFocus->getParent();
    _nextIsNewFocus = false;
    //_currScope--;

  } else {
    //tok->setScope(uCurrScope_);
    
    if(_tokRoot == NULL) {
      _tokRoot = tok;
      _tokFocus = tok;
    
    } else {
      _tokFocus->addChild(tok);
    
      if(_nextIsNewFocus) {
        _tokFocus = tok;
      
      }
      
    }

    _nextIsNewFocus = false;
  
  }

}
