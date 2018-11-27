//
//  Expression.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/24.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "Expression.h"

void Exspression::init(std::string str) {
    parser.buildTree(str);
}
int Exspression::evaluate(Vars *vars) {
    try {
        return parser.parse(vars);
    } catch (int) {
        throw 0;
    }
}
