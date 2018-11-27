//
//  Parser.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/20.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "Parser.h"

void Vars::setVal(std::string valName, int val) {
    mp[valName] = val;
}
int Vars::getVal(std::string valName) {
    auto it = mp.find(valName);
    if (it == mp.end()) {
        throw 0;
    } else {
        return it->second;
    }
}
void Vars::clear() {
    mp.clear();
}

PTree::Node::Node():str(""),leaf(0),lhs(nullptr),rhs(nullptr) {}
PTree::Node::~Node(){}


void PTree::destruct(Node* cur) {
    if (cur->lhs != nullptr) {
        destruct(cur->lhs);
    }
    if (cur->rhs != nullptr) {
        destruct(cur->rhs);
    }
    delete cur;
}

PTree::PTree():root(new Node()) {}
PTree::~PTree() {
    destruct(root);
}
void PTree::build (Node* cur, std::string str){
//    std::cout << "building   " << str << std::endl;
    int bracketed = 0, maxpos = -1, maxval = -10000;
    int flag = 1;
    for (int i = 0, sz = (int)str.length(); i < sz - 1; i++) {
        if (str[i] == '(') {
            bracketed++;
        } else if (str[i] == ')') {
            bracketed--;
        }
        if (bracketed == 0) {
            flag = 0;
            break;
        }
    }
    if (flag) {
        while (str[0] == '(' && str[str.length() - 1] == ')') {
            str = str.substr(1, str.length() - 2);
        }
    }
    bracketed = 0;
    for (int i = 0, sz = (int)str.length(); i < sz; i++) {
        //            std::cout << i << "   " << str[i] << std::endl;
        if (str[i] == '(') {
            bracketed++;
        } else if (str[i] == ')') {
            bracketed--;
        } else if (str[i] == '*' || str[i] == '/') {
            if (maxval <= 1 - 10 * bracketed) {
                maxval = 1 - 10 * bracketed;
                maxpos = i;
                cur->str = std::string(1, str[i]);
            }
        } else if (str[i] == '+' || str[i] == '-') {
            if (maxval <= 2 - 10 * bracketed) {
                maxval = 2 - 10 * bracketed;
                maxpos = i;
                cur->str = std::string(1, str[i]);
            }
        }
    }
    if (maxpos == -1) {
        cur->leaf = 1;
        cur->str = str;
    } else {
        cur->lhs = new Node();
        build(cur->lhs, maxpos != 0 ? str.substr(0, maxpos) : "0");
        cur->rhs = new Node();
        build(cur->rhs, str.substr(maxpos + 1, str.length() - maxpos - 1));
    }
}
int PTree::cal(Node* cur, Vars *vars) {
    if (cur->leaf) {
        std::stringstream sin(cur->str);
        int ret = 0;
        if (sin >> ret) {
            return ret;
        } else {
            try {
                ret = vars->getVal(cur->str);
            } catch (int) {
                throw 1;
            }
            return ret;
        }
    }
    int lval = 0, rval = 0;
    try {
        lval = cal(cur->lhs, vars);
    } catch (int a) {
        throw a;
    }
    try {
        rval = cal(cur->rhs, vars);
    } catch (int a) {
        throw a;
    }
    if (cur->str == "+") {
        return lval + rval;
    } else if (cur->str == "-") {
        return lval - rval;
    } else if (cur->str == "*") {
        return lval * rval;
    } else if (cur->str == "/") {
        if (rval == 0) {
            throw 2;
        } else {
            return lval / rval;
        }
    } else {
        return 0;
    }
}

int PTree::calculate(Vars *vars){
    std::vector<std::string> undifined;
    int ret = 0;
    try {
        ret = cal(root, vars);
    } catch (int a) {
        throw a;
    }
    return ret;
}

void Parser::buildTree(std::string str){
    tree.build(tree.root, str);
}

int Parser::parse(Vars *vars){
    int ret = 0;
    try {
        ret = tree.calculate(vars);
    } catch (int a) {
        if (a == 1) {
            std::cout << "VARIABLE NOT DEFINED" << std::endl;
        } else {
            std::cout << "DIVIDE BY ZERO" << std::endl;
        }
        throw 0;
    }
    return ret;
}
