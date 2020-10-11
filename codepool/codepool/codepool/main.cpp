//
//  main.cpp
//  codepool
//
//  Created by hatlonely on 16/1/26.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>

#define MAIN_NAMESPACE(name) namespace name { extern int main(int argc, const char *argv[]); }

MAIN_NAMESPACE(test_binary_tree)

int main(int argc, const char * argv[]) {
    test_binary_tree::main(argc, argv);
    return 0;
}
