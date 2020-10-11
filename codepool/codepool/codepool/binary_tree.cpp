//
//  binary_tree.cpp
//  codepool
//
//  Created by hatlonely on 16/1/26.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include "binary_tree.hpp"
#include <queue>
#include <stack>
#include <sstream>

BinaryTree::BinaryTree(std::initializer_list<int> li) {
    enum {
        kLeft = 0,
        kRight = 1
    };
    
    node_t prev(0);
    node_t *node = &prev;
    std::queue<node_t *> nodes;
    int left_or_right = kRight;
    
    for (auto i: li) {
        if (left_or_right == kLeft) {
            if (i != $) {
                node->lchild = new node_t(i);
                nodes.push(node->lchild);
            }
            left_or_right = kRight;
        } else {
            if (i != $) {
                node->rchild = new node_t(i);
                nodes.push(node->rchild);
            }
            left_or_right = kLeft;
            if (nodes.empty()) {
                break;
            }
            node = nodes.front();
            nodes.pop();
        }
    }
    
    _root = prev.rchild;
}

BinaryTree::~BinaryTree() {
    if (_root == nullptr) {
        return;
    }
    std::queue<node_t *> nodes;
    nodes.push(_root);
    while (!nodes.empty()) {
        node_t *node = nodes.front();
        nodes.pop();
        if (node->lchild != nullptr) {
            nodes.push(node->lchild);
        }
        if (node->rchild != nullptr) {
            nodes.push(node->rchild);
        }
        delete node;
    }
}

std::string BinaryTree::to_string() {
    if (_root == nullptr) {
        return "$";
    }
    std::stringstream result;
    std::queue<node_t *> nodes;
    nodes.push(_root);
    result << _root->value << ", ";
    while (!nodes.empty()) {
        node_t *node = nodes.front();
        nodes.pop();
        if (node->lchild != nullptr) {
            nodes.push(node->lchild);
            result << node->lchild->value << ", ";
        } else {
            result << "$, ";
        }
        if (node->rchild != nullptr) {
            nodes.push(node->rchild);
            result << node->rchild->value << ", ";
        } else {
            result << "$, ";
        }
    }
    
    return result.str();
}

void BinaryTree::preorder(std::function<void (int &)> func) {
    _preorder_process(_root, func);
}

void BinaryTree::inorder(std::function<void (int &)> func) {
    _inorder_process(_root, func);
}

void BinaryTree::postorder(std::function<void (int &)> func) {
    _postorder_process(_root, func);
}

void BinaryTree::_preorder_process(node_t *node, std::function<void (int &)> func) {
    if (node != nullptr) {
        func(node->value);
        _preorder_process(node->lchild, func);
        _preorder_process(node->rchild, func);
    }
}

void BinaryTree::_inorder_process(node_t *node, std::function<void (int &)> func) {
    if (node != nullptr) {
        _inorder_process(node->lchild, func);
        func(node->value);
        _inorder_process(node->rchild, func);
    }
}
void BinaryTree::_postorder_process(node_t *node, std::function<void (int &)> func) {
    if (node != nullptr) {
        _postorder_process(node->lchild, func);
        _postorder_process(node->rchild, func);
        func(node->value);
    }
}

void BinaryTree::preorder2(std::function<void (int &)> func) {
    if (_root == nullptr) {
        return;
    }
    
    std::stack<node_t *> nodes;
    nodes.push(_root);
    while (!nodes.empty()) {
        node_t *node = nodes.top();
        nodes.pop();
        func(node->value);
        if (node->rchild != nullptr) {
            nodes.push(node->rchild);
        }
        if (node->lchild != nullptr) {
            nodes.push(node->lchild);
        }
    }
}

void BinaryTree::inorder2(std::function<void (int &)> func) {    
    std::stack<node_t *> nodes;
    node_t *node = _root;
    while (!nodes.empty() || node != nullptr) {
        if (node != nullptr) {
            nodes.push(node);
            node = node->lchild;
        } else {
            node = nodes.top();
            nodes.pop();
            func(node->value);
            node = node->rchild;
        }
    }
}

void BinaryTree::inorder3(std::function<void (int &)> func) {
    std::stack<node_t *> nodes;
    node_t *node = _root;
    while (!nodes.empty() || node != nullptr) {
        while (node != nullptr) {
            nodes.push(node);
            node = node->lchild;
        }
        node = nodes.top();
        nodes.pop();
        func(node->value);
        node = node->rchild;
    }
}

void BinaryTree::postorder2(std::function<void (int &)> func) {
    std::stack<node_t *> nodes;
    node_t *node = _root;
    node_t *prev = nullptr;
    while (!nodes.empty() || node != nullptr) {
        while (node != nullptr) {
            nodes.push(node);
            node = node->lchild;
        }
        node = nodes.top();
        if (node->rchild == nullptr || node->rchild == prev) {
            func(node->value);
            prev = node;
            nodes.pop();
            node = nullptr;
        } else {
            node = node->rchild;
        }
    }
}

void BinaryTree::breadthorder(std::function<void (int &)> func) {
    if (_root == nullptr) {
        return;
    }
    
    std::queue<node_t *> nodes;
    nodes.push(_root);
    while (!nodes.empty()) {
        node_t *node = nodes.front();
        nodes.pop();
        func(node->value);
        if (node->lchild != nullptr) {
            nodes.push(node->lchild);
        }
        if (node->rchild != nullptr) {
            nodes.push(node->rchild);
        }
    }
}

