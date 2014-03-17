//
//  Util.c++
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Util.h"

// -----------------------------------------------------------
std::string string_fromStream(std::ifstream &ifs) {  
  std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  
  return s;
  
}

// -----------------------------------------------------------
void string_toLower(std::string &s) {
  for(unsigned int i=0; i < s.length(); i++) {
    char c = s[i];
    if(c >= 'A' && c <= 'Z')
      s[i] += 32;
  
  }

}

// -----------------------------------------------------------
int random_int(int min, int max) {
  return rand() % (max - min) + min;

}

// -----------------------------------------------------------
float random_float(float min, float max) {
  return(min + (float)rand() / ((float)RAND_MAX / ( max - min )));
  
}
