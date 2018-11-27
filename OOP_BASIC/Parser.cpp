//
//  Parser.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/20.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "Parser.h"

void Vars::setVal(std::string valName, double val) {
    mp[valName] = val;
}
double Vars::getVal(std::string valName) {
    auto it = mp.find(valName);
    if (it == mp.end()) {
        throw 0.0;
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
    while (str[0] == '(' && str[str.length() - 1] == ')') {
        str = str.substr(1, str.length() - 2);
    }
    int bracketed = 0, maxpos = -1, maxval = -10000;
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
double PTree::cal(Node* cur, Vars *vars, std::vector<std::string> *undifined) {
    if (cur->leaf) {
        std::stringstream sin(cur->str);
        double ret = 0;
        if (sin >> ret) {
            return ret;
        } else {
            try {
                ret = vars->getVal(cur->str);
            } catch (double) {
                undifined->push_back(cur->str);
            }
            return ret;
        }
    }
    double lval = cal(cur->lhs, vars, undifined);
    double rval = cal(cur->rhs, vars, undifined);
    if (cur->str == "+") {
        return lval + rval;
    } else if (cur->str == "-") {
        return lval - rval;
    } else if (cur->str == "*") {
        return lval * rval;
    } else if (cur->str == "/") {
        return lval / rval;
    } else {
        return 0;
    }
}

double PTree::calculate(Vars *vars){
    std::vector<std::string> undifined;
    double ret = cal(root, vars, &undifined);
    if (undifined.size() > 0) {
        throw undifined;
    } else {
        return ret;
    }
}

void Parser::buildTree(std::string str){
    tree.build(tree.root, str);
}

double Parser::parse(Vars *vars){
    double ret = 0;
    try {
        ret = tree.calculate(vars);
    } catch (std::vector<std::string> undifined) {
//        std::cout << "Undefined variables: ";
//        for (int i = 0, sz = (int)undifined.size(); i < sz; i++) {
//            std::cout << undifined[i] << (i == sz - 1 ? "" : ", ");
//        }
        std::cout << std::endl;
        throw 0.0;
    }
    return ret;
}
