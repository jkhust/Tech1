//
//  Token.h
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Token_h
#define Tech1_Token_h

#include <sstream>
#include "Variant.h"
#include "Environment.h"
#include "System.h"

class System;

// *************************************************************
enum TokenType {
  Token_None = 0,
  
  // top-level of script
  Token_Script,
  Token_Defun,
  Token_Progn,
  Token_LPAR,
  Token_RPAR,

  // basic literals
  Token_BooleanLiteral,
  Token_IntegerLiteral,
  Token_FloatLiteral,
  Token_StringLiteral,

  Token_Identifier,
  Token_Symbol,
  
  // reserved - data definition
  Token_Bool,
  Token_Int,
  Token_Float,
  Token_String,
  Token_Vec3,
  
  // reserved - arithmetic
  Token_Assign,
  Token_Plus,
  Token_Minus,
  Token_Times,
  Token_Divide,
  
  Token_PlusEquals,
  Token_MinusEquals,
  Token_TimesEquals,
  Token_DivideEquals,
  
  Token_PlusPlus,
  Token_MinusMinus,

  // reserved - control structures
  Token_If,
  Token_DoTimes,     // (dotimes 5 (++ x))
  Token_While,       // (while cond (progn ...))

  // reserved - comparators
  Token_Equals,
  Token_NotEquals,
  Token_LessThan,
  Token_LessOrEqual,
  Token_GreaterThan,
  Token_GreaterOrEqual,

  // reserved - logical operators
  Token_And,
  Token_Or,
  Token_Not,

  // reserved - I/O
  Token_Print,
  Token_Println,
  
  // reserved - game system calls
  Token_PlaySound,
  Token_Draw,
  Token_RandomInt,
  Token_RandomFloat,
  
  Token_EnvAccess,      // @sys:frameTicks
  Token_Colon,
  
  Token_SquareBrackets,    // for (vec3 pos [1 -1 0])
  Token_CloseSquareBracket // unused
  
};

// ------------------
enum ReturnType {
  Return_Undeclared = 0,
  Return_Void,
  Return_Boolean,
  Return_Integer,
  Return_Float,
  Return_String,
  Return_Vec3

};

// ------------------
class Token {
private:
  // UNIMPLEMENTED
    Token & operator = (const Token & s);
    Token & operator == (const Token & s);
    Token(const Token &tokOther);

protected:
  // DATA
    TokenType _typ;
    ReturnType _rt;
    
    unsigned int _line;
    unsigned int _col;
    
    Token * _parent;
    Token * _operands;  // first-child next-sibling link structure
    Token * _link;
  
public:
  // CREATORS
    Token(void);
    virtual ~Token(void);
    
  // MANIPULATORS
    void setLineCol(unsigned int line, unsigned int col);
    void addChild(Token *tokChild);
    void setParent(Token *tokParent);
  
    virtual Variant execute(Environment &envLocal, System &sys, std::ostream &oss) = 0;
  
  // ACCESSORS
    TokenType getType(void) const;
    ReturnType getReturnType(void) const;
    Token * getParent(void) const;
    virtual std::string toString(void) const = 0;

    unsigned int getNumChildren(void) const;
    Token * getChild(unsigned int i) const;
    Token * getLink(void) const;

};

// -----------------
class BooleanLiteralToken : public Token {
private:
  // DATA
    bool _bVal;

public:
  // CREATORS
    BooleanLiteralToken(bool bVal);
    ~BooleanLiteralToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
 
  // ACCESSORS
    bool getVal(void) const;
    std::string toString(void) const;

};

// -----------------
class IntegerLiteralToken : public Token {
private:
  // DATA
    int _iVal;

public:
  // CREATORS
    IntegerLiteralToken(int iVal);
    ~IntegerLiteralToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
     
  // ACCESSORS
    int getVal(void) const;
    std::string toString(void) const;

};

// -----------------
class FloatLiteralToken : public Token {
private:
  // DATA
    float _fVal;

public:
  // CREATORS
    FloatLiteralToken(float fVal);
    ~FloatLiteralToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    float getVal(void) const;
    std::string toString(void) const;

};

// -----------------
class StringLiteralToken : public Token {
private:
  // DATA
    std::string _sVal;

public:
  // CREATORS
    StringLiteralToken(const std::string &sVal);
    ~StringLiteralToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string getVal(void) const;
    std::string toString(void) const;

};

// -----------------
class SquareBracketsToken : public Token {
public:
  // CREATORS
    SquareBracketsToken(void);
    ~SquareBracketsToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class CloseSquareBracketToken : public Token {
public:
  // CREATORS
    CloseSquareBracketToken(void);
    ~CloseSquareBracketToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class IdentifierToken : public Token {
private:
  // DATA
    std::string _sVal;

public:
  // CREATORS
    IdentifierToken(const std::string &sVal);
    ~IdentifierToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string getVal(void) const;
    std::string toString(void) const;

};

// -----------------
class LPARToken : public Token {
private:
  // NO DATA
  
public:
  // CREATORS
    LPARToken(void);
    ~LPARToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;
  
};

// -----------------
class RPARToken : public Token {
private:
  // NO DATA
  
public:
  // CREATORS
    RPARToken(void);
    ~RPARToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;
  
};

// -----------------
class BoolToken : public Token {
public:
  // CREATORS
    BoolToken(void);
    ~BoolToken(void);
    
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
 
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class IntToken : public Token {
public:
  // CREATORS
    IntToken(void);
    ~IntToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
 
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class FloatToken : public Token {
public:
  // CREATORS
    FloatToken(void);
    ~FloatToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class StringToken : public Token {
public:
  // CREATORS
    StringToken(void);
    ~StringToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class Vec3Token : public Token {
public:
  // CREATORS
    Vec3Token(void);
    ~Vec3Token(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class PrognToken : public Token {
public:
  // CREATORS
    PrognToken(void);
    ~PrognToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};


// -----------------
class IfToken : public Token {
public:
  // CREATORS
    IfToken(void);
    ~IfToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class DoTimesToken : public Token {
public:
  // CREATORS
    DoTimesToken(void);
    ~DoTimesToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class WhileToken : public Token {
public:
  // CREATORS
    WhileToken(void);
    ~WhileToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class AssignToken : public Token {
public:
  // CREATORS
    AssignToken(void);
    ~AssignToken(void);
 
   // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class PlusToken : public Token {
public:
  // CREATORS
    PlusToken(void);
    ~PlusToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class PlusPlusToken : public Token {
public:
  // CREATORS
    PlusPlusToken(void);
    ~PlusPlusToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class MinusMinusToken : public Token {
public:
  // CREATORS
    MinusMinusToken(void);
    ~MinusMinusToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class PlusEqualsToken : public Token {
public:
  // CREATORS
    PlusEqualsToken(void);
    ~PlusEqualsToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class MinusEqualsToken : public Token {
public:
  // CREATORS
    MinusEqualsToken(void);
    ~MinusEqualsToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class TimesEqualsToken : public Token {
public:
  // CREATORS
    TimesEqualsToken(void);
    ~TimesEqualsToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class DivideEqualsToken : public Token {
public:
  // CREATORS
    DivideEqualsToken(void);
    ~DivideEqualsToken(void);
 
  // MANIPULATORSxx
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};


// -----------------
class EqualsToken : public Token {
public:
  // CREATORS
    EqualsToken(void);
    ~EqualsToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class NotEqualsToken : public Token {
public:
  // CREATORS
    NotEqualsToken(void);
    ~NotEqualsToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class LessThanToken : public Token {
public:
  // CREATORS
    LessThanToken(void);
    ~LessThanToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class LessOrEqualToken : public Token {
public:
  // CREATORS
    LessOrEqualToken(void);
    ~LessOrEqualToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class GreaterThanToken : public Token {
public:
  // CREATORS
    GreaterThanToken(void);
    ~GreaterThanToken(void);
    
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys,  std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class GreaterOrEqualToken : public Token {
public:
  // CREATORS
    GreaterOrEqualToken(void);
    ~GreaterOrEqualToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class AndToken : public Token {
public:
  // CREATORS
    AndToken(void);
    ~AndToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class OrToken : public Token {
public:
  // CREATORS
    OrToken(void);
    ~OrToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class NotToken : public Token {
public:
  // CREATORS
    NotToken(void);
    ~NotToken(void);
 
  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};


// -----------------
class PrintToken : public Token {
public:
  // CREATORS
    PrintToken(void);
    ~PrintToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class PrintlnToken : public Token {
public:
  // CREATORS
    PrintlnToken(void);
    ~PrintlnToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys,  std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};


// -----------------
class PlaySoundToken : public Token {
public:
  // CREATORS
    PlaySoundToken(void);
    ~PlaySoundToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class DrawToken : public Token {
public:
  // CREATORS
    DrawToken(void);
    ~DrawToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class RandomIntToken : public Token {
public:
  // CREATORS
    RandomIntToken(void);
    ~RandomIntToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class RandomFloatToken : public Token {
public:
  // CREATORS
    RandomFloatToken(void);
    ~RandomFloatToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class EnvAccessToken : public Token {
public:
  // CREATORS
    EnvAccessToken(void);
    ~EnvAccessToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class ColonToken : public Token {
public:
  // CREATORS
    ColonToken(void);
    ~ColonToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class ScriptToken : public Token {
public:
  // CREATORS
    ScriptToken(void);
    ~ScriptToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    Variant call(const std::string &sName, Environment &envLocal, System &sys, std::ostream &oss);
    bool hasFunction(const std::string &sName);
    
  // ACCESSORS
    std::string toString(void) const;

};

// -----------------
class DefunToken : public Token {
public:
  // CREATORS
    DefunToken(void);
    ~DefunToken(void);

  // MANIPULATORS
    Variant execute(Environment &envLocal, System &sys, std::ostream &oss);
    
  // ACCESSORS
    std::string toString(void) const;

};

#endif
