//
//  Expression.h
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/27.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Expression_h
#define Expression_h

#include <stdio.h>
#include <string>
#include "Parser.h"

class Exspression {
    Parser parser;
    
public:
    void init(std::string str);
    double evaluate(Vars *vars);
};


#endif /* Expression_h */
