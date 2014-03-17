//
//  Lexer.c++
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Lexer.h"
#include <cassert>
#include "Util.h"

const unsigned long MAX_INT = 2147483647;
const double MIN_FLOAT = -3.175495E+38;
const double MAX_FLOAT = 3.402823E+38;

const char *symbols = "`~!@#$%^&*()-=+[{]};:',<.>/?";

// -----------------------------------------------------------
Lexer::Lexer(std::istream & iss) : _iss(iss) {
  // bind to the input stream
  _chNext = 0;
  _chSkip = 0;
  
  _currLine = 1;
  _currLineStart = 0;

}

// -----------------------------------------------------------
Lexer::~Lexer(void) {


}

// -----------------------------------------------------------
bool Lexer::peekNext(void) {
  _chNext = _iss.peek();
  
  return (_chNext != EOF);
  
}

// -----------------------------------------------------------
bool Lexer::nextIs(char c) const {
  return(_chNext == c);
  
}

// -----------------------------------------------------------
bool Lexer::nextIsAlpha(void) const {
  return( (_chNext >= 'a' && _chNext <= 'z') ||
         (_chNext >= 'A' && _chNext <= 'Z'));

}

// -----------------------------------------------------------
bool Lexer::nextIsNumeric(void) const {
  return( (_chNext >= '0' && _chNext <= '9') );
  
}

// -----------------------------------------------------------
bool Lexer::nextIsSymbol(void) const {
  char *searchResult = strchr(symbols, _chNext);
  
  return(searchResult != NULL);
  
}

// -----------------------------------------------------------
bool Lexer::nextNextIs(char c) {
  char c1;
  char c2;
  
  c1 = _iss.get();
  c2 = _iss.get();
  
  _iss.putback(c2);
  _iss.putback(c1);
  
  return (c2 == c);
  
}

// -----------------------------------------------------------
bool Lexer::nextNextIsNumeric(void) {
  char c1;
  char c2;
  
  c1 = _iss.get();
  c2 = _iss.get();
  
  _iss.putback(c2);
  _iss.putback(c1);
  
  return ( c2 >= '0' && c2 <= '9');
  
}

// -----------------------------------------------------------
bool Lexer::nextTwoAre(char c1_, char c2_) {
  char c1;
  char c2;
  
  c1 = _iss.get();
  c2 = _iss.get();
  
  _iss.putback(c2);
  _iss.putback(c1);
   
  return ((c1 == c1_) && (c2 == c2_));
  
}

// -----------------------------------------------------------
void Lexer::skipChar(void) {
  if(_chNext != EOF) {
    _chSkip = _iss.get();
    peekNext();
    
  }
  
}

// -----------------------------------------------------------
void Lexer::skipWhitespace(void) {
  while( peekNext() ) {    
    // **** WHITESPACE *****
    if(nextIs(' ') || nextIs('\t')) {
      skipChar();
      
    } else if( nextIs('\n')) {
      skipChar();
      
      _currLine++;
      _currLineStart = _iss.tellg();
    
        
    // **** single line comment ******
    } else if (nextTwoAre('/', '/')) {
      skipChar();
      skipChar();
      
      // skip anything until the newline
      while(peekNext() && !nextIs('\n')) {
        skipChar();
        
      }
      
      // skip the newline that terminates the comment
      if(nextIs('\n')) {
        skipChar();
       
        _currLine++;
        _currLineStart = _iss.tellg();
        
      }
      
      // double line comment
    } else if ( nextTwoAre('/', '*') ) {
      // eat it
      skipChar();
      skipChar();
      
      while( peekNext() && !nextTwoAre('*', '/')) {
        if(nextIs('\n')) {
          skipChar();
          
          _currLine++;
          _currLineStart = _iss.tellg();
          
        } else {
          skipChar();
          
        }
        
      }
      
      // if broke out of comment, and not EOF, finish the comment.
      if( !nextIs(EOF)) {
        skipChar();
        skipChar();
        
      }
      
      // anything else, then we must be done.
    } else {
      break;
      
    }
    
  }
  
}

// -----------------------------------------------------------
Token * Lexer::lex(void) {
  skipWhitespace();
  
  if(!peekNext())
    return NULL;
  
  Token *tok = NULL;
  
  
  if(nextIsAlpha()) {
    tok = lexIdentifier();
        
    // positive or negative integer or float.
  } else if( nextIsNumeric() 
             || (nextIs('-') && nextNextIsNumeric() ) 
             || (nextIs('-') && nextNextIs('.') )      // TODO: ambiguous on 3rd peek.  could be a problem.
             || (nextIs('.') && nextNextIsNumeric() ) 
           ) {
           
    tok = lexNumber();
    
  } else if(peekNext() && nextIs('"')) {
    tok = lexString();
    
  } else if(peekNext() && nextIsSymbol()) {
    tok = lexSymbol();
    
  } else {
    tok = NULL;
    
  }
  
  assert(tok != NULL);
  //std::cout << tok->toString() << std::endl;
  return tok;

}

// -----------------------------------------------------------
Token * Lexer::lexIdentifier(void) {
  // save these now because we'll move once the token comes back.
  unsigned int line = _currLine;
  unsigned int col = _iss.tellg();
  col = col - _currLineStart + 1;
  
  

  // read our first ALPHA.  we know it'll be there because we've
  // already peeked for it in the scanner, which is why we are here
  std::string sIdent;
  sIdent += _iss.get();
  
  // now keep reading either numbers or digits or underscores
  while( peekNext() && (nextIsAlpha() || nextIsNumeric() || nextIs('_') ) )
    sIdent += _iss.get();
    
  // *** lowercase it ***
  string_toLower(sIdent);


  Token *tok = NULL;
  
  if(sIdent == "if") {
    tok = new IfToken();   

  } else if(sIdent == "script") {
    return new ScriptToken(); 

  } else if(sIdent == "defun") {
    return new DefunToken(); 

  } else if(sIdent == "dotimes") {
    tok = new DoTimesToken();

  } else if(sIdent == "while") {
    tok = new WhileToken();
    
  } else if(sIdent == "false") {
    tok = new BooleanLiteralToken(false);
    
  } else if(sIdent == "true") {
    tok = new BooleanLiteralToken(true);

  } else if(sIdent == "bool") {
    tok = new BoolToken();

  } else if(sIdent == "int") {
    tok = new IntToken();
    
  } else if(sIdent == "float") {
    tok = new FloatToken();

  } else if(sIdent == "string") {
    tok = new StringToken();

  } else if(sIdent == "vec3") {
    tok = new Vec3Token();

  } else if(sIdent == "progn") {
    tok = new PrognToken();

  } else if(sIdent == "print") {
    tok = new PrintToken(); 

  } else if(sIdent == "println") {
    tok = new PrintlnToken(); 
    
  } else if(sIdent == "and") {
    tok = new AndToken(); 

  } else if(sIdent == "or") {
    tok = new OrToken(); 
    
  } else if(sIdent == "not") {
    tok = new NotToken(); 

  } else if(sIdent == "randi") {
    tok = new RandomIntToken(); 

  } else if(sIdent == "randf") {
    tok = new RandomFloatToken(); 
    
  // **** game-specific keywords ****
  } else if(sIdent == "playsound") {
    tok = new PlaySoundToken(); 

  } else if(sIdent == "draw") {
    tok = new DrawToken(); 
            
  } else {
    tok = new IdentifierToken(sIdent);
    
  }
  
  assert(tok != NULL);
  
  tok->setLineCol(line, col);
  return tok;

}

// -----------------------------------------------------------
#define READPHASE_INT 0
#define READPHASE_DEC 1
#define READPHASE_EXP 2

// number can start with . or - or a digit.
Token * Lexer::lexNumber(void) {
  // save these now because we'll move once the token comes back.
  unsigned int line = _currLine;
  unsigned int col = _iss.tellg();
  col = col - _currLineStart + 1;
  
  

  int iSign = 0;
  int readphase;
  
  if(nextIs('-')) {
    skipChar();
    iSign = -1;
    readphase = READPHASE_INT;
    
  } else if(nextIs('.')) {
    skipChar();
    iSign = 1;
    readphase = READPHASE_DEC;
    
  } else {
    iSign = 1;
    readphase = READPHASE_INT;
    
  }
  
  
  
  char c = 0;
  int charval = 0;
  
  int iNumSigFigs = 0;
  bool bInSigFigs = false;
  int skippedUntilDec = 0;
  
  long num = 0;
  bool bIntOverflow = false;
  
  int expBy = 0;
  
  int eSign = 0;
  long eVal = 0;
  
  // eat any leading nonzero numbers.  
  while(peekNext()) {
    if(nextIsNumeric()) {
      if(readphase == READPHASE_INT) {
        // start counting sig figs if needed
        if(!nextIs('0')) 
          bInSigFigs = true;
        
        if(bInSigFigs) {
          c = _iss.get();
          charval = c - '0';
          
          // num * 10 + charval <= MAX_INT is OK
          if(num <= ((MAX_INT - charval) / 10)) {
            num = num * 10 + charval;
            iNumSigFigs++;
            
          } else {
            bIntOverflow = true;
            // keep track of skipped digits in case we turn into a real.
            skippedUntilDec++;
            
          }
          
        } else {
          skipChar();
          
        }
        
        // if in decimal mode,
      } else if(readphase == READPHASE_DEC) {
        
        if(!nextIs('0')) 
          bInSigFigs = true;
        
        // if we are counting them, and have room for more
        if(bInSigFigs) {
          if(iNumSigFigs < 9) {
            // add to our final number
            iNumSigFigs++;
            
            c = _iss.get();
            charval = c - '0';
            
            num = num * 10 + charval;
            
            // each decimal place means we move the exponent value left 1 at the end.
            expBy = expBy - 1;
            
          } else {
            skipChar();
            
          }
          
        } else {
          skipChar();
          expBy = expBy - 1;
          
        }
        
        // if in exponent mode, just accumulate the exponent value
      } else if(readphase == READPHASE_EXP) {
        char c = _iss.get();
        int charval = c - '0';
        
        eVal = eVal * 10 + charval;
        
      }
      
      // . must come after int, and have a digit after.
    } else if(nextIs('.') && (readphase == READPHASE_INT) && 
              nextNextIsNumeric()) {
      // as soon as we become a decimal number, figure out how
      // far over we are.
      // 234567890xx.003 9 + 2 - 1 = 10
      expBy = skippedUntilDec;
      
      // eat the decimal
      skipChar();
      readphase = READPHASE_DEC;
      
      // exponent [e|E][+\-]
    } else if((nextIs('e') || nextIs('E')) && 
              ((readphase == READPHASE_INT) || (readphase == READPHASE_DEC))  &&
              (nextNextIs('+') || nextNextIs('-') || nextNextIsNumeric())) {
      
      // skip the E.
      skipChar();
      readphase = READPHASE_EXP;
      
      // get for sign and skip those, too.
      if(nextIs('+')) {
        eSign = 1;
        skipChar();
        
      } else if(nextIs('-')) {
        eSign = -1;
        skipChar();
        
      } else if(nextIsNumeric()) {
        eSign = 1;
        // don't skip the number by mistake!
        
      }
      
      // any other case, don't calculate.
    } else {
      break;
      
    }
    
  }
  
  // ****** lexing is done.  now calculate answer. *****
  // INTEGER
  if(readphase == READPHASE_INT) {
    assert(!bIntOverflow);
  
    Token *tok = new IntegerLiteralToken(iSign * num);   
    tok->setLineCol(line, col);
    return tok;
  
  // REAL NUMBER
  } else {
    // final sig figs accounts for how many minus dec digits plus any E value.
    expBy = expBy + (eSign * eVal);
    
    // otherwise, the number is good.
    double dNum = iSign * num;
    
    // TODO: convert to a lookup table instead of busy-looping.
    while(expBy < 0) {
      dNum = dNum / 10;
      expBy++;
      
    }
    
    while(expBy > 0) {
      dNum = dNum * 10;
      expBy--;
      
    }
    
    assert( (dNum >= MIN_FLOAT) && (dNum <= MAX_FLOAT));

    Token *tok = new FloatLiteralToken(dNum); 
    tok->setLineCol(line, col);
    return tok;
    
  }
 
  assert(!"Didn't find any valid number.");
  return NULL;

}

// -----------------------------------------------------------
Token * Lexer::lexString(void) {
  // save these now because we'll move once the token comes back.
  unsigned int line = _currLine;
  unsigned int col = _iss.tellg();
  col = col - _currLineStart + 1;
  

  // if first char EOF, done.
  // if first char is a letter, use it.
  // if first char is a quote
  //              if second char is an EOF, done
  //              if second char is a letter, we are done at the first quote
  //              if second char is a quote, too, then it's escape quote.  keep going.
  std::string s;
  
  // skip the open quote that got us here
  skipChar();
  
  while(peekNext()) {
    // use any non-escaped character we find.
    if(  !nextIs('"')) {
      s += _iss.get();
      
      // *** check 2nd to find if escape char, or end of string ***
    } else {
      // if double quote with out an escape quote,
      if( ! nextNextIs('"')) {
        // done with string
        skipChar();
        break;
        
      // if escaped quote,
      } else {
        // skip first and just use second
        skipChar();
        s += _iss.get();
        
      }
      
    }
    
  }
  
  Token *tok = new StringLiteralToken(s);
  tok->setLineCol(line, col);
  return tok;
  
}

// -----------------------------------------------------------
Token * Lexer::lexSymbol(void) {
  // save these now because we'll move once the token comes back.
  unsigned int line = _currLine;
  unsigned int col = _iss.tellg();
  col = col - _currLineStart + 1;

  std::string s;
  
  // try to handle <=, >=, ==, != before any single symbols
  if( nextTwoAre('<', '=') ||
      nextTwoAre('>', '=') ||
      nextTwoAre('+', '+') ||
      nextTwoAre('-', '-') ||
      nextTwoAre('+', '=') ||
      nextTwoAre('-', '=') ||
      nextTwoAre('*', '=') ||
      nextTwoAre('/', '=') ||
      nextTwoAre('=', '=') ||
      nextTwoAre('!', '=')
    ) {
                     
    s += _iss.get();
    s += _iss.get();
    
  } else {
    s += _iss.get();
    
  }
  
  Token *tok = NULL;
  
  if(s == "(") {
    tok = new LPARToken();
  
  } else if(s == ")") {
    tok = new RPARToken();

  } else if(s == "@") {
    // pre-build env access into mini-tree
    tok = new EnvAccessToken();

  } else if(s == "[") {
    // pre-build vec3 brackets into mini-tree
    tok = new SquareBracketsToken();

  } else if(s == "]") {
    tok = new CloseSquareBracketToken();
    
  } else if(s == ":") {
    tok = new ColonToken();

  } else if(s == "==") {
    tok = new EqualsToken();
  
  } else if(s == "!=") {
    tok = new NotEqualsToken();
    
  } else if(s == "<") {
    tok = new LessThanToken();
  
  } else if(s == "<=") {
    tok = new LessOrEqualToken();
    
  } else if(s == ">") {
    tok = new GreaterThanToken();
    
  } else if(s == ">=") {
    tok = new GreaterOrEqualToken();
  
  } else if(s == "=") {
    tok = new AssignToken();

  } else if(s == "++") {
    tok = new PlusPlusToken();

  } else if(s == "--") {
    tok = new MinusMinusToken();

  } else if(s == "+=") {
    tok = new PlusEqualsToken();

  } else if(s == "-=") {
    tok = new MinusEqualsToken();

  } else if(s == "*=") {
    tok = new TimesEqualsToken();

  } else if(s == "/=") {
    tok = new DivideEqualsToken();

  } else if(s == "+") {
    tok = new PlusToken();
    
  } 
  
//  } else if(sym.equals("-")) {
//    return (Token *) new ReservedMinusToken(); 
//    
//  } else if(sym.equals("*")) {
//    return (Token *) new ReservedTimesToken();  
// 
//  } else if(sym.equals("/")) {
//    return (Token *) new ReservedDivideToken();  
//


//  if(tok == NULL) {
//    std::cout << "found " << s << std::endl;
//  
//  }

  assert(tok != NULL);
  tok->setLineCol(line, col);
  
  if(tok->getType() == Token_EnvAccess) {
    Token *tokEnv = lexIdentifier();
    Token *tokColon = lexSymbol();
    Token *tokField = lexIdentifier();
    
    assert(tokColon->getType() == Token_Colon);
  
    tok->addChild(tokEnv);
    tok->addChild(tokColon);
    tok->addChild(tokField);
  
  } else if(tok->getType() == Token_SquareBrackets) {
    Token *tokLeft = lex();
    Token *tokMiddle = lex();
    Token *tokRight = lex();
    Token *tokCloseBracket = lex(); // get whitespace and close bracket
    
    tok->addChild(tokLeft);
    tok->addChild(tokMiddle);
    tok->addChild(tokRight);
    
  }
 
  return tok;
  
}