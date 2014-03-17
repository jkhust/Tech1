//
//  Token.c++
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Token.h"
#include "Environment.h"
#include "System.h"
#include "Util.h"

#include <iostream>
#include <sstream>
#include <cassert>

// ------------------------------------------------------
Token::Token(void) {
  _typ = Token_None;

  _line = 0;
  _col = 0;
  
  _parent = NULL;
  _operands = NULL;
  _link = NULL;
  
}

// ------------------------------------------------------
Token::~Token(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
void Token::setLineCol(unsigned int line, unsigned int col) {
  _line = line;
  _col = col;

}

// ------------------------------------------------------
void Token::setParent(Token *tokParent) {
  assert(tokParent != NULL);

  _parent = tokParent;

}

// ------------------------------------------------------
void Token::addChild(Token *tokChild) {
  assert(tokChild != NULL);

  // set its parent to us
  tokChild->setParent(this);
  
  // follow operand chain to end if need to
  if(this->_operands == NULL)
    this->_operands = tokChild;
    
  else {
    Token *lastOperand = this->_operands;
    
    while(lastOperand->getLink())
      lastOperand = lastOperand->getLink();
  
    lastOperand->_link = tokChild;
  
  }

}

// ------------------------------------------------------
TokenType Token::getType(void) const {
  return _typ;
  
}

// ------------------------------------------------------
ReturnType Token::getReturnType(void) const {
  return _rt;

}

// ------------------------------------------------------
Token * Token::getParent(void) const {
  return _parent;
  
}

// ------------------------------------------------------
unsigned int Token::getNumChildren(void) const {
  unsigned int n = 0;
  
  Token *operand = this->_operands;
    
  while(operand) {
    n++;
    
    operand = operand->getLink();
  
  }
  
  return n;

}

// ------------------------------------------------------
Token * Token::getChild(unsigned int i) const {
  assert(i >= 0);

  Token *operand = this->_operands;
  
  unsigned int n = 0;
        
  while(operand) {
    if(n == i)
      return operand;
  
    n++;
    operand = operand->getLink();
  
  }
  
  assert(!"Child not found at index.");
  return NULL;

}

// ------------------------------------------------------
Token * Token::getLink(void) const {
  return _link;

}

// ------------------------------------------------------
BooleanLiteralToken::BooleanLiteralToken(bool bVal) {
  _typ = Token_BooleanLiteral;
  _rt = Return_Boolean;
  _bVal = bVal;

}

// ------------------------------------------------------
BooleanLiteralToken::~BooleanLiteralToken(void) {
  // no cleanup code

}

// ------------------------------------------------------
bool BooleanLiteralToken::getVal(void) const {
  return _bVal;

}

// ------------------------------------------------------
std::string BooleanLiteralToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tbool\t ";
    
  if(_bVal) {
    ss << "TRUE";
    
  } else {
    ss << "FALSE";
  
  }
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant BooleanLiteralToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  return Variant(_bVal);

}

// ------------------------------------------------------
IntegerLiteralToken::IntegerLiteralToken(int iVal) {
  _typ = Token_IntegerLiteral;
  _rt = Return_Integer;
  _iVal = iVal;

}

// ------------------------------------------------------
IntegerLiteralToken::~IntegerLiteralToken(void) {
  // no cleanup code

}

// ------------------------------------------------------
int IntegerLiteralToken::getVal(void) const {
  return _iVal;

}

// ------------------------------------------------------
std::string IntegerLiteralToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tint\t " << _iVal;
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant IntegerLiteralToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  return Variant(_iVal);

}

// ------------------------------------------------------
FloatLiteralToken::FloatLiteralToken(float fVal) {
  _typ = Token_FloatLiteral;
  _rt = Return_Float;
  _fVal = fVal;

}

// ------------------------------------------------------
FloatLiteralToken::~FloatLiteralToken(void) {
  // no cleanup code

}

// ------------------------------------------------------
float FloatLiteralToken::getVal(void) const {
  return _fVal;

}

// ------------------------------------------------------
std::string FloatLiteralToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tfloat\t " << _fVal;
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant FloatLiteralToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  return Variant(_fVal);

}

// ------------------------------------------------------
StringLiteralToken::StringLiteralToken(const std::string &sVal) {
  _typ = Token_StringLiteral;
  _rt = Return_String;
  _sVal = sVal;

}

// ------------------------------------------------------
StringLiteralToken::~StringLiteralToken(void) {
  // no cleanup code

}

// ------------------------------------------------------
std::string StringLiteralToken::getVal(void) const {
  return _sVal;

}

// ------------------------------------------------------
std::string StringLiteralToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tstring\t " << _sVal;
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant StringLiteralToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  return Variant(_sVal);

}

// ------------------------------------------------------
SquareBracketsToken::SquareBracketsToken(void) {
  _typ = Token_SquareBrackets;
  _rt = Return_Vec3;

}

// ------------------------------------------------------
SquareBracketsToken::~SquareBracketsToken(void) {
  // no cleanup code

}

// ------------------------------------------------------
std::string SquareBracketsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t SQUAREBRACKETS";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant SquareBracketsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();

  assert(numChildren == 3);
  
  Variant valLeft = this->getChild(0)->execute(envLocal, sys, oss);
  Variant valMiddle = this->getChild(1)->execute(envLocal, sys, oss);
  Variant valRight = this->getChild(2)->execute(envLocal, sys, oss);
  
  assert(valLeft.isNumeric());
  assert(valMiddle.isNumeric());
  assert(valRight.isNumeric());

  return Variant( Vec3(valLeft.toFloat(), valMiddle.toFloat(), valRight.toFloat() ) );

}

// ------------------------------------------------------
CloseSquareBracketToken::CloseSquareBracketToken(void) {
  _typ = Token_CloseSquareBracket;
  _rt = Return_Void;

}

// ------------------------------------------------------
CloseSquareBracketToken::~CloseSquareBracketToken(void) {
  // no cleanup code

}

// ------------------------------------------------------
std::string CloseSquareBracketToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t CLOSESQBRACKET";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant CloseSquareBracketToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Never executed.");
  return Variant();

}

// ------------------------------------------------------
IdentifierToken::IdentifierToken(const std::string &sVal) {
  _typ = Token_Identifier;
  _rt = Return_Undeclared;
  _sVal = sVal;
  
}
  
// ------------------------------------------------------
IdentifierToken::~IdentifierToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string IdentifierToken::getVal(void) const {
  return _sVal;

}

// ------------------------------------------------------
std::string IdentifierToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tident\t " << _sVal;
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant IdentifierToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  return envLocal.get(_sVal);

}

// ------------------------------------------------------
LPARToken::LPARToken(void) {
  _typ = Token_LPAR;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
LPARToken::~LPARToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string LPARToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t (";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant LPARToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Never called.");
  return Variant();

}

// ------------------------------------------------------
RPARToken::RPARToken(void) {
  _typ = Token_RPAR;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
RPARToken::~RPARToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string RPARToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t )";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant RPARToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Never called.");
  return Variant();

}

// ------------------------------------------------------
BoolToken::BoolToken(void) {
  _typ = Token_Bool;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
BoolToken::~BoolToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string BoolToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t BOOL";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant BoolToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();

  assert(numChildren == 1 || numChildren == 2);
  assert(this->getChild(0)->getType() == Token_Identifier);
  
  IdentifierToken *tokIdent = dynamic_cast<IdentifierToken *>(this->getChild(0));
  
  Variant val;
  
  if(this->getNumChildren() == 2) {
    Token *tokRHS = this->getChild(1);
    assert(tokRHS->getReturnType() == Return_Boolean);
    
    val = tokRHS->execute(envLocal, sys, oss);
  
  } else { 
    val = false;
    
  }

  // add to local environment
  envLocal.declare(tokIdent->getVal(), val);
  
  return Variant();
  
}

// ------------------------------------------------------
IntToken::IntToken(void) {
  _typ = Token_Int;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
IntToken::~IntToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string IntToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t INT";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant IntToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();

  assert(numChildren == 1 || numChildren == 2);
  assert(this->getChild(0)->getType() == Token_Identifier);
  
  IdentifierToken *tokIdent = dynamic_cast<IdentifierToken *>(this->getChild(0));
  
  Variant val;
  
  if(this->getNumChildren() == 2) {
    Token *tokRHS = this->getChild(1);
    // assert(tokRHS->getReturnType() == Return_Integer);
    
    val = tokRHS->execute(envLocal, sys, oss);
  
  } else { 
    val = 0;
    
  }

  // add to local environment
  envLocal.declare(tokIdent->getVal(), val);
  
  return Variant();
  
}

// ------------------------------------------------------
FloatToken::FloatToken(void) {
  _typ = Token_Float;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
FloatToken::~FloatToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string FloatToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t FLOAT";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant FloatToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();

  assert(numChildren == 1 || numChildren == 2);
  assert(this->getChild(0)->getType() == Token_Identifier);
  
  IdentifierToken *tokIdent = dynamic_cast<IdentifierToken *>(this->getChild(0));
  
  Variant val;
  
  if(this->getNumChildren() == 2) {
    Token *tokRHS = this->getChild(1);
    assert(tokRHS->getReturnType() == Return_Float);
    
    val = tokRHS->execute(envLocal, sys, oss);
  
  } else { 
    val = 0.0f;
    
  }

  // add to local environment
  envLocal.declare(tokIdent->getVal(), val);
  
  return Variant();
  
}

// ------------------------------------------------------
StringToken::StringToken(void) {
  _typ = Token_String;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
StringToken::~StringToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string StringToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t STRING";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant StringToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();

  assert(numChildren == 1 || numChildren == 2);
  assert(this->getChild(0)->getType() == Token_Identifier);
  
  IdentifierToken *tokIdent = dynamic_cast<IdentifierToken *>(this->getChild(0));
  
  Variant val;
  
  if(this->getNumChildren() == 2) {
    Token *tokRHS = this->getChild(1);
    assert(tokRHS->getReturnType() == Return_String);
    
    val = tokRHS->execute(envLocal, sys, oss);
  
  } else { 
    val = "";
    
  }

  // add to local environment
  envLocal.declare(tokIdent->getVal(), val);
  
  return Variant();
  
}

// ------------------------------------------------------
Vec3Token::Vec3Token(void) {
  _typ = Token_Vec3;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
Vec3Token::~Vec3Token(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string Vec3Token::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t VEC3";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant Vec3Token::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();

  assert(numChildren == 1 || numChildren == 2);
  assert(this->getChild(0)->getType() == Token_Identifier);
  
  IdentifierToken *tokIdent = dynamic_cast<IdentifierToken *>(this->getChild(0));
  
  Variant val;
  
  if(this->getNumChildren() == 2) {
    Token *tokRHS = this->getChild(1);
    assert(tokRHS->getReturnType() == Return_Vec3);
    
    val = tokRHS->execute(envLocal, sys, oss);
  
  } else { 
    val = "";
    
  }

  // add to local environment
  envLocal.declare(tokIdent->getVal(), val);
  
  return Variant();
  
}

// ------------------------------------------------------
PrognToken::PrognToken(void) {
  _typ = Token_Progn;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
PrognToken::~PrognToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
std::string PrognToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t PROGN";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PrognToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  for(unsigned int i=0;i<numChildren;i++) {
    Token *tokChild = this->getChild(i);
    tokChild->execute(envLocal, sys, oss);
  
  }

  // TODO: return last statement?
  return Variant();
  
}

// ------------------------------------------------------
AssignToken::AssignToken(void) {
  _typ = Token_Assign;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
AssignToken::~AssignToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string AssignToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t ASSIGN";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant AssignToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  int iNumChildren = this->getNumChildren();
  
  assert(iNumChildren == 2);
  
  IdentifierToken *tokIdent = dynamic_cast<IdentifierToken *>(this->getChild(0));

  Token *tokRHS = this->getChild(1);
  Variant val = tokRHS->execute(envLocal, sys, oss);
  
  Variant currVal = envLocal.get(tokIdent->getVal());
  
  assert(currVal.getType() == val.getType() );
  
  // add to local environment
  envLocal.set(tokIdent->getVal(), val);
  
  return Variant();
  
}

// ------------------------------------------------------
PlusToken::PlusToken(void) {
  _typ = Token_Plus;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
PlusToken::~PlusToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string PlusToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t PLUS";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PlusToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Unimplemented.");
  return Variant();

}

// ------------------------------------------------------
PlusPlusToken::PlusPlusToken(void) {
  _typ = Token_PlusPlus;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
PlusPlusToken::~PlusPlusToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string PlusPlusToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t PLUSPLUS";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PlusPlusToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 1);
  
  Token *tok = this->getChild(0);
  assert(tok->getType() == Token_Identifier);

  IdentifierToken *tokIdent= dynamic_cast<IdentifierToken *>(tok);

  Variant varVal = tokIdent->execute(envLocal, sys, oss);
  
  assert(varVal.isInteger());
  
  ++varVal;
  
  envLocal.set(tokIdent->getVal(), varVal);
  
  return Variant();
  
}

// ------------------------------------------------------
MinusMinusToken::MinusMinusToken(void) {
  _typ = Token_MinusMinus;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
MinusMinusToken::~MinusMinusToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string MinusMinusToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t MINUSMINUS";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant MinusMinusToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 1);
  
  Token *tok = this->getChild(0);
  assert(tok->getType() == Token_Identifier);

  IdentifierToken *tokIdent= dynamic_cast<IdentifierToken *>(tok);

  Variant varVal = tokIdent->execute(envLocal, sys, oss);
  
  assert(varVal.isInteger());
  
  --varVal;
  
  envLocal.set(tokIdent->getVal(), varVal);
  
  return Variant();
  
}

// ------------------------------------------------------
IfToken::IfToken(void) {
  _typ = Token_If;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
IfToken::~IfToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string IfToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t IF";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant IfToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2 || numChildren == 3);
  assert(this->getChild(0)->getReturnType() == Return_Boolean );
  
  Variant bCond = this->getChild(0)->execute(envLocal, sys, oss);
  
  if(bCond == true) {
    this->getChild(1)->execute(envLocal, sys, oss);
  
  } else if(numChildren == 3) {
    this->getChild(2)->execute(envLocal, sys, oss);
  
  }
  
  return Variant();
  
}

// ------------------------------------------------------
DoTimesToken::DoTimesToken(void) {
  _typ = Token_DoTimes;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
DoTimesToken::~DoTimesToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string DoTimesToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t DOTIMES";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant DoTimesToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);
  
  Variant numTimes = this->getChild(0)->execute(envLocal, sys, oss);
  assert(numTimes.isInteger());
  
  for(int i=0; i < numTimes.getInteger(); i++) {
    this->getChild(1)->execute(envLocal, sys, oss);
  
  }
  
  return Variant();
  
}

// ------------------------------------------------------
WhileToken::WhileToken(void) {
  _typ = Token_While;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
WhileToken::~WhileToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string WhileToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t WHILE";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant WhileToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);
  
  Variant cond = this->getChild(0)->execute(envLocal, sys, oss);
  assert(cond.isBoolean());
  
  while(cond == true) {
    this->getChild(1)->execute(envLocal, sys, oss);
  
    cond = this->getChild(0)->execute(envLocal, sys, oss);
  
  }
  
  return Variant();
  
}

// ------------------------------------------------------
EqualsToken::EqualsToken(void) {
  _typ = Token_Equals;
  _rt = Return_Boolean;

}
  
// ------------------------------------------------------
EqualsToken::~EqualsToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string EqualsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t EQ";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant EqualsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);

  Variant valLHS = this->getChild(0)->execute(envLocal, sys, oss);
  Variant valRHS = this->getChild(1)->execute(envLocal, sys, oss);

  if( valLHS == valRHS )
    return Variant(true);
  else
    return Variant(false);
  
}

// ------------------------------------------------------
NotEqualsToken::NotEqualsToken(void) {
  _typ = Token_NotEquals;
  _rt = Return_Boolean;

}
  
// ------------------------------------------------------
NotEqualsToken::~NotEqualsToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string NotEqualsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t NEQ";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant NotEqualsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);

  Variant valLHS = this->getChild(0)->execute(envLocal, sys, oss);
  Variant valRHS = this->getChild(1)->execute(envLocal, sys, oss);

  if( valLHS == valRHS )
    return Variant(false);
  else
    return Variant(true);
    
}

// ------------------------------------------------------
LessThanToken::LessThanToken(void) {
  _typ = Token_LessThan;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
LessThanToken::~LessThanToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string LessThanToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t LT";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant LessThanToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Unimplemented.");
  return Variant();
  
}

// ------------------------------------------------------
LessOrEqualToken::LessOrEqualToken(void) {
  _typ = Token_LessOrEqual;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
LessOrEqualToken::~LessOrEqualToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string LessOrEqualToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t LE";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant LessOrEqualToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Unimplemented.");
  return Variant();
  
}

// ------------------------------------------------------
GreaterThanToken::GreaterThanToken(void) {
  _typ = Token_GreaterThan;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
GreaterThanToken::~GreaterThanToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string GreaterThanToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t GT";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant GreaterThanToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Unimplemented.");
  return Variant();
  
}

// ------------------------------------------------------
GreaterOrEqualToken::GreaterOrEqualToken(void) {
  _typ = Token_GreaterOrEqual;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
GreaterOrEqualToken::~GreaterOrEqualToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string GreaterOrEqualToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t GE";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant GreaterOrEqualToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Unimplemented.");
  return Variant();
  
}

// ------------------------------------------------------
PlusEqualsToken::PlusEqualsToken(void) {
  _typ = Token_PlusEquals;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
PlusEqualsToken::~PlusEqualsToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string PlusEqualsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t PLUSEQ";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PlusEqualsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  assert(numChildren == 2);

  Token * tokLHS = this->getChild(0);
  assert(tokLHS->getType() == Token_Identifier);
  
  IdentifierToken * tokIdent = dynamic_cast<IdentifierToken *>(tokLHS);
  Variant currVal = envLocal.get(tokIdent->getVal());
  assert(currVal.isNumeric());
  
  Token *tokRHS = this->getChild(1);
  Variant newVal = tokRHS->execute(envLocal, sys, oss);
  assert(newVal.isNumeric());
  
  currVal += newVal;
  
  envLocal.set(tokIdent->getVal(), currVal);
  
  return Variant();

}

// ------------------------------------------------------
MinusEqualsToken::MinusEqualsToken(void) {
  _typ = Token_MinusEquals;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
MinusEqualsToken::~MinusEqualsToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string MinusEqualsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t MINUSEQ";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant MinusEqualsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  assert(numChildren == 2);

  Token * tokLHS = this->getChild(0);
  assert(tokLHS->getType() == Token_Identifier);
  
  IdentifierToken * tokIdent = dynamic_cast<IdentifierToken *>(tokLHS);
  Variant currVal = envLocal.get(tokIdent->getVal());
  assert(currVal.isNumeric());
  
  Token *tokRHS = this->getChild(1);
  Variant newVal = tokRHS->execute(envLocal, sys, oss);
  assert(newVal.isNumeric());
  
  currVal -= newVal;
  
  envLocal.set(tokIdent->getVal(), currVal);
  
  return Variant();

}

// ------------------------------------------------------
TimesEqualsToken::TimesEqualsToken(void) {
  _typ = Token_TimesEquals;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
TimesEqualsToken::~TimesEqualsToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string TimesEqualsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t TIMESEQ";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant TimesEqualsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  assert(numChildren == 2);

  Token * tokLHS = this->getChild(0);
  assert(tokLHS->getType() == Token_Identifier);
  
  IdentifierToken * tokIdent = dynamic_cast<IdentifierToken *>(tokLHS);
  Variant currVal = envLocal.get(tokIdent->getVal());
  assert(currVal.isNumeric());
  
  Token *tokRHS = this->getChild(1);
  Variant newVal = tokRHS->execute(envLocal, sys, oss);
  assert(newVal.isNumeric());
  
  currVal *= newVal;
  
  envLocal.set(tokIdent->getVal(), currVal);
  
  return Variant();

}

// ------------------------------------------------------
DivideEqualsToken::DivideEqualsToken(void) {
  _typ = Token_DivideEquals;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
DivideEqualsToken::~DivideEqualsToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string DivideEqualsToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\top\t DIVIDEEQ";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant DivideEqualsToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  assert(numChildren == 2);

  Token * tokLHS = this->getChild(0);
  assert(tokLHS->getType() == Token_Identifier);
  
  IdentifierToken * tokIdent = dynamic_cast<IdentifierToken *>(tokLHS);
  Variant currVal = envLocal.get(tokIdent->getVal());
  assert(currVal.isNumeric());
  
  Token *tokRHS = this->getChild(1);
  Variant newVal = tokRHS->execute(envLocal, sys, oss);
  assert(newVal.isNumeric());
  
  currVal /= newVal;
  
  envLocal.set(tokIdent->getVal(), currVal);
  
  return Variant();

}


// ------------------------------------------------------
PrintToken::PrintToken(void) {
  _typ = Token_Print;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
PrintToken::~PrintToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string PrintToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t PRINT";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PrintToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  // print each child.
  unsigned int numChildren = this->getNumChildren();
  
  for(unsigned int i=0; i < numChildren; i++) {
    Token * tokChild = this->getChild(i);
    
    Variant val = tokChild->execute(envLocal, sys, oss);

    // *** print it ***
    if(val == true) {
      oss << "true.";
    
    } else if(val == false) {
      oss << "false.";
    
    } else if(val.isInteger()) {
      oss << val.getInteger();
    
    } else if(val.isFloat()) {
      oss << val.getFloat();
    
    } else if(val.isString()) {
      oss << val.getString();
    
    }
    
  }
  
  return Variant();
  
}

// ------------------------------------------------------
PrintlnToken::PrintlnToken(void) {
  _typ = Token_Println;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
PrintlnToken::~PrintlnToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string PrintlnToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t PRINTLN";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PrintlnToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  // print each child.
  unsigned int numChildren = this->getNumChildren();
  
  for(unsigned int i=0; i < numChildren; i++) {
    Token * tokChild = this->getChild(i);
    
    Variant val = tokChild->execute(envLocal, sys, oss);
    
    // *** print it ***
    if(val == true) {
      oss << "true.";
    
    } else if(val == false) {
      oss << "false.";
    
    } else if(val.isInteger()) {
      oss << val.getInteger();
    
    } else if(val.isFloat()) {
      oss << val.getFloat();
    
    } else if(val.isString()) {
      oss << val.getString();
    
    }
    
  }

  oss << std::endl;
  
  return Variant();
  
}

// ------------------------------------------------------
AndToken::AndToken(void) {
  _typ = Token_And;
  _rt = Return_Boolean;

}
  
// ------------------------------------------------------
AndToken::~AndToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string AndToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t AND";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant AndToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren >= 2);
  
  for(unsigned int i=0; i < numChildren; i++) {
    Variant val = this->getChild(i)->execute(envLocal, sys, oss);
  
    assert( val.isBoolean() );
    // any false means all false
    if(val == false)
      return Variant(false);
  
  
  }
  
  return Variant(true);
  
}

// ------------------------------------------------------
OrToken::OrToken(void) {
  _typ = Token_Or;
  _rt = Return_Boolean;

}
  
// ------------------------------------------------------
OrToken::~OrToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string OrToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t OR";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant OrToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren >= 2);
  
  for(unsigned int i=0; i < numChildren; i++) {
    Variant val = this->getChild(i)->execute(envLocal, sys, oss);
  
    assert( val.isBoolean() );
    // any true means all true
    if(val == true)
      return Variant(true);
  
  
  }
  
  return Variant(false);
  
}

// ------------------------------------------------------
NotToken::NotToken(void) {
  _typ = Token_Not;
  _rt = Return_Boolean;

}
  
// ------------------------------------------------------
NotToken::~NotToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string NotToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t NOT";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant NotToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 1);

  Variant val = this->getChild(0)->execute(envLocal, sys, oss);
  assert( val.isBoolean() );
  
  if(val == false)
    return Variant(true);
  else
    return Variant(false);
  
}

// ------------------------------------------------------
PlaySoundToken::PlaySoundToken(void) {
  _typ = Token_PlaySound;
  _rt = Return_Void;

}
  
// ------------------------------------------------------
PlaySoundToken::~PlaySoundToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string PlaySoundToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t PLAYSOUND";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant PlaySoundToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 1);
  
  Token *tokChild = this->getChild(0);
  
  Variant varSound = tokChild->execute(envLocal, sys, oss);
  assert( varSound.isString() );
  
  sys.playSound( varSound.getString() );
    
  return Variant();
  
}

// ------------------------------------------------------
DrawToken::DrawToken(void) {
  _typ = Token_Draw;
  //setReturnType(Return_Void);

}
  
// ------------------------------------------------------
DrawToken::~DrawToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string DrawToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t DRAW";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant DrawToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 3);
  
  Token *tokImage = this->getChild(0);
  Variant varImage = tokImage->execute(envLocal, sys, oss);
  assert( varImage.isString() );
  
  Token *tokX = this->getChild(1);
  Variant varX = tokX->execute(envLocal, sys, oss);
  assert( varX.isFloat() );

  Token *tokY = this->getChild(2);
  Variant varY = tokY->execute(envLocal, sys, oss);
  assert( varY.isFloat() );  
  
  sys.draw(varImage.getString(), varX.getFloat(), varY.getFloat() );
    
  return Variant();
  
}

// ------------------------------------------------------
RandomIntToken::RandomIntToken(void) {
  _typ = Token_RandomInt;
  _rt = Return_Integer;
  
}
  
// ------------------------------------------------------
RandomIntToken::~RandomIntToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string RandomIntToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t RANDI";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant RandomIntToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);

  Token * tokLHS = this->getChild(0);
  Token * tokRHS = this->getChild(1);
  
  Variant valMin = tokLHS->execute(envLocal, sys, oss);
  Variant valMax = tokRHS->execute(envLocal, sys, oss);
  
  assert(valMin.isInteger());
  assert(valMax.isInteger());
  
  int iMin = valMin.getInteger();
  int iMax = valMax.getInteger();
  
  int r = random_int(iMin, iMax);
    
  return Variant(r);

}  

// ------------------------------------------------------
RandomFloatToken::RandomFloatToken(void) {
  _typ = Token_RandomFloat;
  _rt = Return_Float;
  
}
  
// ------------------------------------------------------
RandomFloatToken::~RandomFloatToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string RandomFloatToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t RANDF";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant RandomFloatToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);

  Token * tokLHS = this->getChild(0);
  Token * tokRHS = this->getChild(1);
  
  Variant valMin = tokLHS->execute(envLocal, sys, oss);
  Variant valMax = tokRHS->execute(envLocal, sys, oss);
  
  assert(valMin.isFloat());
  assert(valMax.isFloat());
  
  float fMin = valMin.getFloat();
  float fMax = valMax.getFloat();
  
  float r = random_float(fMin, fMax);
    
  return Variant(r);

}  

// ------------------------------------------------------
EnvAccessToken::EnvAccessToken(void) {
  _typ = Token_EnvAccess;
  _rt = Return_Undeclared;
  
}
  
// ------------------------------------------------------
EnvAccessToken::~EnvAccessToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string EnvAccessToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tsymbol\t ENVACCESS";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant EnvAccessToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 3);
  assert(this->getChild(0)->getType() == Token_Identifier);
  assert(this->getChild(1)->getType() == Token_Colon);
  assert(this->getChild(2)->getType() == Token_Identifier);

  IdentifierToken *tokEnv = dynamic_cast<IdentifierToken *> (this->getChild(0));
  IdentifierToken *tokField = dynamic_cast<IdentifierToken *> (this->getChild(2));

  // lookup field in proper environment
  if(tokEnv->getVal() == "sys") {
    return sys.env().get(tokField->getVal());
  
  } else {
    assert("Unknown environment");
  
  }
  
  return Variant();
  
}

// ------------------------------------------------------
ColonToken::ColonToken(void) {
  _typ = Token_Colon;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
ColonToken::~ColonToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string ColonToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\tsymbol\t COLON";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant ColonToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  assert(!"Should never execute.");
  return Variant();
  
}

// ------------------------------------------------------
DefunToken::DefunToken(void) {
  _typ = Token_Defun;
  _rt = Return_Void;
  
}
  
// ------------------------------------------------------
DefunToken::~DefunToken(void) {
  // no cleanup code yet

}


// ------------------------------------------------------
std::string DefunToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t DEFUN";
  
  return ss.str();
  
}

// ------------------------------------------------------
Variant DefunToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  assert(numChildren == 2);
  
  Token *tokName = this->getChild(0);
  assert(tokName->getType() == Token_StringLiteral);
  
  Token *tokCode = this->getChild(1);
  
  assert(tokCode != NULL);
  tokCode->execute(envLocal, sys, oss);
  
  return Variant();
  
}

// ------------------------------------------------------
ScriptToken::ScriptToken(void) {
  _typ = Token_Script;
  _rt = Return_Void;

}

// ------------------------------------------------------
ScriptToken::~ScriptToken(void) {
  // no cleanup code yet

}

// ------------------------------------------------------
Variant ScriptToken::execute(Environment &envLocal, System &sys, std::ostream &oss) {
  this->call("main", envLocal, sys, oss);
  return Variant();

}

// ------------------------------------------------------
Variant ScriptToken::call(const std::string &sName, Environment &envLocal, System &sys, std::ostream &oss) {
  unsigned int numChildren = this->getNumChildren();
  
  for(unsigned int i=1; i < numChildren; i++) {
    if(this->getChild(i)->getType() == Token_Defun) {
      Token *tokFunc = this->getChild(i);
  
      assert(tokFunc->getNumChildren() == 2);
      
      StringLiteralToken *tokName = dynamic_cast<StringLiteralToken *>( tokFunc->getChild(0));
      
      // found it, run it
      if(tokName->getVal() == sName) {
        tokFunc->getChild(1)->execute(envLocal, sys, oss);
        return Variant();
      
      }
    
    }
  
  }
  
  assert(!"Function not found.");
  return Variant();
  
}

// ------------------------------------------------------
bool ScriptToken::hasFunction(const std::string &sName) {
  unsigned int numChildren = this->getNumChildren();
  
  for(unsigned int i=1; i < numChildren; i++) {
    if(this->getChild(i)->getType() == Token_Defun) {
      Token *tokFunc = this->getChild(i);
  
      assert(tokFunc->getNumChildren() == 2);
      
      StringLiteralToken *tokName = dynamic_cast<StringLiteralToken *>( tokFunc->getChild(0));
      
      // found it, run it
      if(tokName->getVal() == sName) {
        return true;
             
      }
    
    }
  
  }
  
  return false;
  
}

// ------------------------------------------------------
std::string ScriptToken::toString(void) const {
  std::ostringstream ss;
  ss << _line << ":" << _col << "\treserv\t SCRIPT";
  
  return ss.str();
  
}