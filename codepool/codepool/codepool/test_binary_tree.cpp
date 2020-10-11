//
//  test_binary_tree.cpp
//  codepool
//
//  Created by hatlonely on 16/1/26.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <vector>
#include "binary_tree.hpp"

namespace test_binary_tree {

void test_binary_tree() {
    {
        BinaryTree bt;
        assert(bt.get_root() == nullptr);
    } {
        BinaryTree bt({1, 2, 3, 4});
        assert(bt.get_root()->value == 1);
        assert(bt.get_root()->lchild->value == 2);
        assert(bt.get_root()->rchild->value == 3);
        assert(bt.get_root()->lchild->lchild->value == 4);
    } {
        BinaryTree bt({1, $, 2, 3});
        assert(bt.get_root()->value == 1);
        assert(bt.get_root()->lchild == nullptr);
        assert(bt.get_root()->rchild->value == 2);
        assert(bt.get_root()->rchild->lchild->value == 3);
    }
}

void test_to_string() {
    {
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        assert(bt.to_string() == "1, 2, 3, 4, 5, 6, $, $, $, $, $, $, $, ");
    } {
        BinaryTree bt({$});
        assert(bt.to_string() == "$");
    } {
        BinaryTree bt({1, $, 2, 3});
        assert(bt.to_string() == "1, $, 2, 3, $, $, $, ");
    }
}

void test_preorder() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.preorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.preorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({1, 2, 4, 5, 3, 6}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.preorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({1, 2, 3, 4}));
    }
}

void test_inorder() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.inorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.inorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({4, 2, 5, 1, 6, 3}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.inorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({3, 2, 4, 1}));
    }
}

void test_postorder() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.postorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.postorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({4, 5, 2, 6, 3, 1}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.postorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({3, 4, 2, 1}));
    }
}

void test_preorder2() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.preorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.preorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({1, 2, 4, 5, 3, 6}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.preorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({1, 2, 3, 4}));
    }
}

void test_inorder2() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.inorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.inorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({4, 2, 5, 1, 6, 3}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.inorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({3, 2, 4, 1}));
    }
}

void test_inorder3() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.inorder3(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.inorder3(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({4, 2, 5, 1, 6, 3}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.inorder3(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({3, 2, 4, 1}));
    }
}

void test_postorder2() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.postorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.postorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({4, 5, 2, 6, 3, 1}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.postorder2(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({3, 4, 2, 1}));
    }
}

void test_breadthorder() {
    std::function<void (int &, std::vector<int> &)> func = [](int &i, std::vector<int> &vi) {
        vi.push_back(i);
    };
    {
        std::vector<int> vi;
        BinaryTree bt({});
        bt.breadthorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi.empty());
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, 3, 4, 5, 6});
        bt.breadthorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({1, 2, 3, 4, 5, 6}));
    } {
        std::vector<int> vi;
        BinaryTree bt({1, 2, $, 3, 4});
        bt.breadthorder(std::bind(func, std::placeholders::_1, std::ref(vi)));
        assert(vi == std::vector<int>({1, 2, 3, 4}));
    }
}

int main(int argc, const char *argv[]) {
    test_binary_tree();
    test_to_string();
    test_preorder();
    test_inorder();
    test_postorder();
    test_preorder2();
    test_inorder2();
    test_inorder3();
    test_postorder2();
    test_breadthorder();
    
    return 0;
}

}
