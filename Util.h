//
//  Util.h
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Util_h
#define Tech1_Util_h

void string_toLower(std::string &s);

int random_int(int min, int max);
float random_float(float min, float max);

std::string string_fromStream(const std::ifstream &ifs);

#endif
