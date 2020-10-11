//
//  calculator.h
//  calculator
//
//  Created by hatlonely on 16/5/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace hatlonely {
    
std::string& Trim(std::string& str);
std::string TrimCopy(const std::string& str);
std::string& RemoveSpace(std::string& str);
std::string RemoveSpaceCopy(const std::string& str);
void SplitWithSeparators(const std::string& str,
                         std::vector<std::string>& result,
                         std::function<bool (char)> sepPred=isspace);
void Split(const std::string& str, std::vector<std::string>& result,
           std::function<bool (char)> sepPred=isspace);


enum class TokenType {
    kNumber    = 0,
    kOperation = 1,
    kVariable  = 2,
    kBracket   = 3,
    kUndefine
};

struct op_info_t {
    int opnum;                                              // 操作数个数
    std::function<double (std::vector<double>&)> func;      // 计算方法
};

struct token_t {
    TokenType type = TokenType::kUndefine;      // 标识符类型
    std::string identify;                       // 字符串
    double number = 0.0;                        // type = kNumber 有效
    
    std::string toString() const {
        std::stringstream os;
        os << "(" << int(type) << ", " << identify << ", " << number << ")";
        return os.str();
    }
};
    
class Calculator {
public:
    /**
     *  @author hatlonely(hatlonely@mobvista.com), 16-05-26 21:05:36
     *
     *  @brief 计算一个表达式的值
     *  @param expression 表达式，例如：1 + sin(PI / 2) * 3 - 4 / 5
     *  @param result     表达式的值
     *  @return 成功返回true，否则返回false
     *  @since 1.0.0.0
     */
    bool calculate(const std::string& expression, double& result);
    
    /**
     *  @author hatlonely(hatlonely@mobvista.com), 16-05-26 21:05:36
     *
     *  @brief 计算一个表达式的值
     *  @param values     环境变量
     *  @param expression 表达式，例如：1 + sin(PI / 2) * 3 - 4 / 5
     *  @param result     表达式的值
     *  @return 成功返回true，否则返回false
     *  @since 1.0.0.0
     */
    bool calculate(std::unordered_map<std::string, double> values, const std::string& expression, double& result);
    
    /**
     *  @author hatlonely(hatlonely@mobvista.com), 16-05-26 21:05:56
     *
     *  @brief 计算一个表达式的值，表达式中包含一些变量
     *  @param environment 环境变量的值，例如：[a = 1, b = 2, x = a + b]
     *  @param expression  表达式，例如：a * b + x
     *  @param result      表达式的值
     *  @return 成功返回true，否则返回false
     *  @since 1.0.0.0
     */
    bool calculate(const std::vector<std::string>& environment, const std::string& expression, double& result);
    
    /**
     *  @author hatlonely(hatlonely@mobvista.com), 16-05-26 21:05:23
     *
     *  @brief 语法分析，分析表达式，化成前缀表达式
     *  @param values     环境变量
     *  @param expression 表达式
     *  @param infix      前缀表达式
     *  @return 成功返回true，否则返回false
     *  @since 1.0.0.0
     */
    bool syntaxAnalysis(std::unordered_map<std::string, double> values,
                        const std::string& expression, std::vector<token_t>& infix);
    
    /**
     *  @author hatlonely(hatlonely@mobvista.com), 16-05-26 21:05:38
     *
     *  @brief 前缀表达式化成后缀表达式，去掉括号
     *  @param infix   前缀表达式
     *  @param postfix 后缀表达式
     *  @return 成功返回true，否则返回false
     *  @since 1.0.0.0
     */
    bool infixToPostfix(const std::vector<token_t>& infix, std::vector<token_t>& postfix);
    
    /**
     *  @author hatlonely(hatlonely@mobvista.com), 16-05-26 22:05:25
     *
     *  @brief 计算一个后缀表达式的值
     *  @param values  环境变量
     *  @param postfix 后缀表达式
     *  @param result  表达式的值
     *  @return 成功返回true，否则返回false
     *  @since 1.0.0.0
     */
    bool evaluate(std::unordered_map<std::string, double> values,
                  std::vector<token_t>& postfix, double& result);
    
private:
    static std::unordered_map<std::string, op_info_t> _opmap;   // 计算方法
    static std::unordered_map<std::string, int> _priority;      // 运算符优先级
    static std::unordered_map<std::string, double> _constant;   // 常量
    static std::unordered_set<char> _separators;                // 表达式分隔符
};
    
}
