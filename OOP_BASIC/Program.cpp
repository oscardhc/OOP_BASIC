//
//  Program.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 5018/11/23.
//  Copyright © 5018 Haichen Dong. All rights reserved.
//

#include "Program.h"

Vars Sentence::variable;
std::string keyWords[] = {"REM", "LET", "PRINT", "INPUT", "END", "GOTO", "IF", "THEN", "RUN", "LIST", "CLEAR", "QUIT", "HELP"};

int AssignmentStce::run() {
    int tmp = 0.0;
    try {
        tmp = exp.evaluate(&variable);
    } catch (int) {
        return -1;
    }
    variable.setVal(var, tmp);
    return 0;
}
void AssignmentStce::read() {
    char buf[501];
    std::cin.getline(buf, 500);
    str = "";
    int len = (int)strlen(buf), cur = 0;
    for (cur = 0; cur < len; cur++) {
        if (buf[cur] != ' ') {
            if (buf[cur] == '=') {
                break;
            } else {
                var.push_back(buf[cur]);
            }
        }
    }
    for (int i = 0; i < 13; i++) {
        if (var == keyWords[i]) {
            std::cout << "SYNTAX ERROR" << std::endl;
            throw 1;
        }
    }
    for (cur++; cur < len; cur++) {
        if (buf[cur] != ' ') {
            str.push_back(buf[cur]);
        }
    }
    exp.init(str);
    str="LET" + std::string(buf);
}


int OutputStce::run() {
    int tmp = 0;
    try {
        tmp = exp.evaluate(&variable);
    } catch (int) {
        return 1;
    }
    std::cout << tmp << std::endl;
    return 0;
}
void OutputStce::read() {
    char buf[501];
    std::cin.getline(buf, 500);
    str = "";
    int len = (int)strlen(buf), cur = 0;
    for (cur = 0; cur < len; cur++) {
        if (buf[cur] != ' ') {
            str.push_back(buf[cur]);
        }
    }
    exp.init(str);
    str = "PRINT" + std::string(buf);
}


int InputStce::run() {
    int tmp = 0;
//    std::cin.ignore(100,'\n');
    while (1) {
        std::cout << " ? ";
        std::string tmpstr;
        char buf[501];
        do {
            std::cin.getline(buf, 500);
            tmpstr = std::string(buf);
        } while (strlen(buf) == 0) ;
        std::stringstream sin(tmpstr);
//        std::cout << '\"' << tmpstr << '\"' << std::endl;
        if (!(sin >> tmp)) {
            std::cout << "INVALID NUMBER" << std::endl;
        } else {
            char chr;
            if (sin >> chr) {
                std::cout << "INVALID NUMBER" << std::endl;
            } else {
                break;
            }
        }
    }
    variable.setVal(var, tmp);
    return 0;
}
void InputStce::read() {
    char buf[501];
    std::cin.getline(buf, 500);
    std::string tmpstr = std::string(buf);
    std::stringstream sin(tmpstr);
    sin >> var;
    str = "INPUT" + var;
}


int CommentsStce::run() {
    return 0;
}
void CommentsStce::read() {
    char buf[501];
    std::cin.getline(buf, 500);
    str = "REM" + std::string(buf);
}


int EndStce::run() {
    return 1;
}
void EndStce::read() {
}

int GotoStce::run() {
    throw num;
    return 0;
}
void GotoStce::read() {
    char buf[501];
    std::cin.getline(buf, 500);
    std::string tmpstr = std::string(buf);
    std::stringstream sin(tmpstr);
    sin >> num;
    // str = "GOTO" + std::string(num2str(num));
}


int ConditionStce::run() {
    int tmp1 = 0, tmp2 = 0;
    try {
        tmp1 = exp1.evaluate(&variable);
    } catch (int) {
        return -1;
    }
    try {
        tmp2 = exp2.evaluate(&variable);
    } catch (int) {
        return -1;
    }
    // std::cout << tmp1 << " " << tmp2 << " " << opr << std::endl;
    if (opr == "=") {
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
    }
    return 0;
}
void ConditionStce::read() {
    char buf[501];
    std::cin.getline(buf, 500);
    str = "";
    int len = (int)strlen(buf), cur = 0;
    std::string str2 = "";
    for (cur = 0; cur < len; cur++) {
        if (buf[cur] != ' ') {
            if (buf[cur] == '=' || buf[cur] == '<' || buf[cur] == '>') {
                opr.push_back(buf[cur]);
                break;
            } else {
                str.push_back(buf[cur]);
            }
        }
    }
    for (cur++; cur < len; cur++) {
        if (buf[cur] == '=' || buf[cur] == '<' || buf[cur] == '>') {
            opr.push_back(buf[cur]);
        } else {
            break;
        }
    }
    for (; cur < len; cur++) {
        if (buf[cur] != ' ') {
            str2.push_back(buf[cur]);
        }
        if (str2.length() > 4 && str2.substr(str2.length()-4, 4) == "THEN") {
            str2 = str2.substr(0, str2.length()-4);
            break;
        }
    }
    exp1.init(str);
    exp2.init(str2);
    num = 0;
    for (cur++; cur < len; cur++) {
        if (buf[cur] != ' ') {
            num = num * 10 + buf[cur] - '0';
        }
    }
    str = "IF" + std::string(buf);
}


Program::~Program() {
    for (auto i = stce.begin(); i != stce.end(); i++) {
        delete i->second;
    }
}
void Program::addStce(int lineNum, Sentence* nstce) {
    stce[lineNum] = nstce;
}
void Program::delStce(int lineNum) {
    auto it = stce.find(lineNum);
    if (it != stce.end()) {
        stce.erase(it);
    } else {
//        std::cout << "LINE NUMBER ERROR" << std::endl;
    }
}
void Program::execute() {
    for (auto i = stce.begin(); i != stce.end(); ) {
//         std::cout << "RUNNING LINE " << i->first << std::endl;
        int re = 0;
        try {
            re = i->second->run();
            if (re) {
                break;
            }
            i++;
        } catch (int a) {
            // std::cout << "throwed " << a << std::endl;
            auto j = stce.find(a);
            if (j == stce.end()) {
                std::cout << "LINE NUMBER ERROR" << std::endl;
                throw 1;
            } else {
                i = j;
            }
        }
        
    }
}
void Program::clear() {
    stce.clear();
    Sentence::variable.clear();
}
void Program::list() {
    for (auto i = stce.begin(); i != stce.end(); i++) {
        std::cout << i->first << " " << i->second->str << std::endl;
    }
}

void CMD::work() {
    std::string str;
    std::cin >> str;
    int tmp = 0;
    std::stringstream sin(str);
    if (sin >> tmp) {
        char ch = getchar();
        while (ch == ' ') {
            ch = getchar();
        }
        if (ch == '\n') {
            prog.delStce(tmp);
            return;
        }
        Sentence *stce;
        std::cin >> str;
        // std::cout << str << std::endl;
        if (str == "EM") {
            stce = new CommentsStce();
        } else if (str == "ET") {
            stce = new AssignmentStce();
        } else if (str == "RINT") {
            stce = new OutputStce();
        } else if (str == "NPUT") {
            stce = new InputStce();
        } else if (str == "ND") {
            stce = new EndStce();
        } else if (str == "F") {
            stce = new ConditionStce();
        } else if (str == "OTO") {
            stce = new GotoStce();
        }
        stce->read();
        prog.addStce(tmp, stce);
        
    } else if (str == "LIST") {
        prog.list();
    } else if (str == "CLEAR") {
        prog.clear();
    } else if (str == "QUIT") {
        throw 1;
    } else if (str == "HELP") {
        
    } else if (str == "RUN") {
        try{
            prog.execute();
        } catch (int) {
            return;
        }
    } else if (str == "LET" || str == "PRINT" || str == "INPUT") {
        Sentence *stce;
        if (str == "LET") {
            stce = new AssignmentStce();
        } else if (str == "PRINT") {
            stce = new OutputStce();
        } else {
            stce = new InputStce();
        }
        stce->read();
        int ret = 0;
        try {
            ret = stce->run();
        } catch (int) {
            
        }
    } else {
        std::cout << "SYNTAX ERROR" << std::endl;
//        throw 1;
    }
}
