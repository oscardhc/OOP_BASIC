//
//  main.cpp
//  OOP_BASIC
//
//  Created by Haichen Dong on 2018/11/20.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <iostream>
#include "Program.cpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Exspression ex;
    ex.init("-(-1*a)*3+4");
    Vars vs;
    vs.setVal("a", 233);
    std::cout << ex.evaluate(&vs) << std::endl;
    
    Program a;
    return 0;
}
