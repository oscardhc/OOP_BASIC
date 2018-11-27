//
//  Expression.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/24.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "Parser.cpp"

class Exspression {
    Parser parser;
    
public:
    void init(std::string str) {
        parser.buildTree(str);
    }
    double evaluate(Vars *vars) {
        try {
            return parser.parse(vars);
        } catch (double) {
            throw 0.0;
        }
    }
};

