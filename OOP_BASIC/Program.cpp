//
//  Program.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/23.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <stdio.h>
#include <map>
#include "Expression.cpp"

class Sentence {
public:
    static Vars variable;
    
public:
    virtual int run(){
        return 0;
    }
};

class AssignmentStce : Sentence {
    std::string var;
    Exspression exp;
    
public:
    int run() {
        double tmp = 0.0;
        try {
            tmp = exp.evaluate(&variable);
        } catch (double) {
            std::cout << "VARIABLE NOT DEFINED" << std::endl;
            return -1;
        }
        variable.setVal(var, tmp);
        return 0;
    }
};

class OutputStce : Sentence {
    Exspression exp;
    
public:
    int run() {
        double tmp = 0.0;
        try {
            tmp = exp.evaluate(&variable);
        } catch (double) {
            std::cout << "VARIABLE NOT DEFINED" << std::endl;
            return -1;
        }
        std::cout << tmp << std::endl;
        return 0;
    }
};

class InputStce : Sentence {
    std::string var;
    
public:
    int run() {
        std::cout << " ? ";
        double tmp = 0.0;
        if (!(std::cin >> tmp)) {
            std::cout << "INVALID NUMBER" << std::endl;
            return -1;
        }
        variable.setVal(var, tmp);
        return 0;
    }
};

class CommentsStce : Sentence {
    
public:
    int run() {
        return 0;
    }
};

class EndStce : Sentence {
    
public:
    int run() {
        return 1;
    }
};

class GotoStce : Sentence {
    int num;
    
public:
    int run() {
        throw num;
        return 0;
    }
};

class ConditionStce : Sentence {
    int num;
    Exspression exp1, exp2;
    std::string opr;
    
public:
    int run() {
        double tmp1 = 0, tmp2 = 0;
        try {
            tmp1 = exp1.evaluate(&variable);
        } catch (double) {
            std::cout << "VARIABLE NOT DEFINED" << std::endl;
            return -1;
        }
        try {
            tmp2 = exp2.evaluate(&variable);
        } catch (double) {
            std::cout << "VARIABLE NOT DEFINED" << std::endl;
            return -1;
        }
        if (opr == "==") {
            if (tmp1 == tmp2) {
                throw num;
            }
        } else if (opr == "<") {
            if (tmp1 < tmp2) {
                throw num;
            }
        } else if (opr == ">") {
            if (tmp1 > tmp2) {
                throw num;
            }
        } else if (opr == "<=") {
            if (tmp1 <= tmp2) {
                throw num;
            }
        } else if (opr == ">=") {
            if (tmp1 >= tmp2) {
                throw num;
            }
        }
        return 0;
    }
};

class Program {
    int curLine;
    std::map< int, Sentence > stce;
    
public:
    void execute() {
        for (auto i = stce.begin(); i != stce.end(); ) {
            int re = 0;
            try {
                re = i->second.run();
                if (re) {
                    break;
                }
                i++;
            } catch (int a) {
                auto j = stce.find(a);
                if (j == stce.end()) {
                    std::cout << "LINE NUMBER ERROR" << std::endl;
                } else {
                    i = j;
                }
            }
            
        }
    }
};
