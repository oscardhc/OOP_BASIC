//
//  Parser.h
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/27.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

class Vars {
    std::map<std::string, int> mp;
    
public:
    void setVal(std::string valName, int val);
    int getVal(std::string valName);
    void clear();
};

class PTree {
    class Node {
        
    public:
        std::string str;
        bool leaf;
        Node* lhs;
        Node* rhs;
        
    public:
        Node();
        ~Node();
    };
    
public:
    Node* root;
    
private:
    void destruct(Node* cur);
    
public:
    PTree();
    ~PTree();
    void build (Node* cur, std::string str);
    int cal(Node* cur, Vars *vars);
    
public:
    int calculate(Vars *vars);
};

class Parser {
    PTree tree;
    
public:
    void buildTree(std::string str);
    int parse(Vars *vars);
};


#endif /* Parser_h */
