//
//  Program.h
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/27.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Program_h
#define Program_h

#include <stdio.h>
#include <map>
#include <cstring>
#include "Expression.h"
#include "Parser.h"

class Sentence {
public:
    static Vars variable;
    std::string str;
    
public:
    virtual int run(){
        return 0;
    }
    virtual void read(){
        
    }
};

class AssignmentStce : public Sentence {
    std::string var;
    Exspression exp;
    
public:
    int run();
    void read();
};

class OutputStce : public Sentence {
    Exspression exp;
    
public:
    int run();
    void read();
};

class InputStce : public Sentence {
    std::string var;
    
public:
    int run();
    void read();
};

class CommentsStce : public Sentence {
    
public:
    int run();
    void read();
};

class EndStce : public Sentence {
    
public:
    int run();
    void read();
};

class GotoStce : public Sentence {
    int num;
    
public:
    int run();
    void read();
};

class ConditionStce : public Sentence {
    int num;
    Exspression exp1, exp2;
    std::string opr;
    
public:
    int run();
    void read();
};

class Program {
    int curLine;
    std::map< int, Sentence* > stce;
    
public:
    ~Program();
    void addStce(int lineNum, Sentence* nstce);
    void delStce(int lineNum);
    void execute();
    void clear();
    void list();
};

class CMD{
    Program prog;
    
public:
    void work();
};


#endif /* Program_h */
