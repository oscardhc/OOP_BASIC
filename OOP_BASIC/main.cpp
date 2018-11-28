//
//  main.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/20.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <iostream>
#include "Program.h"

int main(int argc, const char * argv[]) {
//    freopen("in.txt","r",stdin);
    std::cout << "HELLO WORLD" << std::endl;
    CMD cmd;
    while(1){
        try {
            cmd.work();
        } catch(int) {
            break;
        }
    }
    
    return 0;
}
