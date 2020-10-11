//
//  test_calculator.cpp
//  calculator
//
//  Created by hatlonely on 16/5/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "calculator.h"

#define EXPECT_EQ(v1, v2) \
    do {\
        if (v1 != v2) { \
            std::cout << __FILE__ << ":" << __LINE__ << "] " \
            #v1"[" << v1 << "] != "#v2"[" << v2 << "]" << std::endl; \
        } \
    } while(0)

#define EXPECT_NEAR(v1, v2) \
    do {\
        if (!IsNear(v1, v2)) { \
            std::cout << __FILE__ << ":" << __LINE__ << "] " \
            #v1"[" << v1 << "] != "#v2"[" << v2 << "]" << std::endl; \
        } \
    } while(0)

namespace hatlonely {

bool IsNear(double d1, double d2, double precision=0.00000001) {
    if (d1 == 0 || d2 == 0) {
        return std::fabs(d1 - d2) < precision;
    }
    return std::fabs((d1 - d2) / d1) < precision;
}

int TestCalculator(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "can not open file " << filename << std::endl;
        return -1;
    }
    
    Calculator calculator;
    char buffer[1024];
    int linenum = 0;
    while (in.getline(buffer, sizeof(buffer))) {
        linenum++;
        std::string line(buffer);
        if (TrimCopy(line).substr(0, 2) == "//") {
            continue;
        }
        if (TrimCopy(line).empty()) {
            continue;
        }
        auto idx = line.find_last_of('=');
        std::string expression = TrimCopy(line.substr(0, idx));
        double expected = std::stod(TrimCopy(line.substr(idx + 1)));
        double result = 0.0;
        if (!calculator.calculate(expression, result) || !IsNear(expected, result)) {
            std::cerr << "linenum[" << linenum << "] expression[" << expression
                     << "] expected[" << expected << "] result[" << result << "]"<< std::endl;
        }
    }
    
    return 0;
}

void TestTrim() {
    {
        std::string str = "  aabbcc  ";
        EXPECT_EQ(Trim(str), "aabbcc");
        EXPECT_EQ(str, "aabbcc");
    } {
        std::string str = "";
        EXPECT_EQ(Trim(str), "");
        EXPECT_EQ(str, "");
    } {
        std::string str = " \t\n\r ";
        EXPECT_EQ(Trim(str), "");
        EXPECT_EQ(str, "");
    } {
        std::string str = " ";
        EXPECT_EQ(Trim(str), "");
        EXPECT_EQ(str, "");
    } {
        std::string str = " aabbcc ";
        EXPECT_EQ(TrimCopy(str), "aabbcc");
        EXPECT_EQ(str, " aabbcc ");
    }
}

void TestRemoveSpace() {
    {
        std::string str = " 1 + 2 ";
        EXPECT_EQ(RemoveSpace(str), "1+2");
        EXPECT_EQ(str, "1+2");
    } {
        std::string str = "";
        EXPECT_EQ(RemoveSpace(str), "");
        EXPECT_EQ(str, "");
    } {
        std::string str = " ";
        EXPECT_EQ(RemoveSpace(str), "");
        EXPECT_EQ(str, "");
    } {
        std::string str = " \t\n\r";
        EXPECT_EQ(RemoveSpace(str), "");
        EXPECT_EQ(str, "");
    } {
        std::string str = " 1 + 2 ";
        EXPECT_EQ(RemoveSpaceCopy(str), "1+2");
        EXPECT_EQ(str, " 1 + 2 ");
    }
}
    
void TestSplitWithSeparators() {
    {
        std::string str = "1 2 3 4";
        std::vector<std::string> result;
        SplitWithSeparators(str, result);
        assert(result == std::vector<std::string>({"1", " ", "2", " ", "3", " ", "4"}));
    }
}
    
void TestSplit() {
    {
        std::string str = "1 2 3 4";
        std::vector<std::string> result;
        Split(str, result);
        assert(result == std::vector<std::string>({"1", "2", "3", "4"}));
    }
}
    
}


int main(int argc, const char * argv[]) {
    hatlonely::TestTrim();
    hatlonely::TestRemoveSpace();
    hatlonely::TestSplitWithSeparators();
    hatlonely::TestSplit();
    hatlonely::TestCalculator("case.txt");
    return 0;
}

