//
//  binary_tree.hpp
//  codepool
//
//  Created by hatlonely on 16/1/26.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#ifndef binary_tree_hpp
#define binary_tree_hpp

#include <iostream>

const int $ = INT_MIN;

class BinaryTree {
    
struct node_t {
    node_t *lchild;
    node_t *rchild;
    int value;
    node_t(int value) : value(value), lchild(nullptr), rchild(nullptr) {}
};
    
public:
    BinaryTree() : _root(nullptr) {}
    BinaryTree(std::initializer_list<int> li);
    ~BinaryTree();
    std::string to_string();
    
    void preorder(std::function<void (int &)> func);
    void inorder(std::function<void (int &)> func);
    void postorder(std::function<void (int &)> func);
    
    void preorder2(std::function<void (int &)> func);
    void inorder2(std::function<void (int &)> func);
    void inorder3(std::function<void (int &)> func);
    void postorder2(std::function<void (int &)> func);
    
    void breadthorder(std::function<void (int&)> func);
    
    node_t *get_root() { return _root; }
private:
    node_t *_root;
    
    void _preorder_process(node_t *node, std::function<void (int &)> func);
    void _inorder_process(node_t *node, std::function<void (int &)> func);
    void _postorder_process(node_t *node, std::function<void (int &)> func);
};

#endif /* binary_tree_hpp */
