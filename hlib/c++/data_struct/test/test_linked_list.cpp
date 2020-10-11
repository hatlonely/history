//
//  test_linked_list.cpp
//
//  Created by hatlonely(hatlonely@gmail.com) on 15/3/26.
//  Copyright (c) 2015 hatlonely. All rights reserved.
//

// define private/protected to public for test
#define private public
#define protected public

#include <list>
#include <gtest/gtest.h>
#include "linked_list.h"

int main(int argc, char **argv)
{
 	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace hl {

TEST(test_constructor_case, case_default) {
    LinkedList<int> li;
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_constructor_case, case_copy) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);

    LinkedList<int> li_copy(li);
    EXPECT_EQ(li_copy[0], 1);
    EXPECT_EQ(li_copy[1], 2);
    EXPECT_EQ(li_copy[2], 3);
    EXPECT_EQ(li_copy[3], 4);
}

TEST(test_constructor_case, case_initializer_list) {
    LinkedList<int> li({1, 2, 3, 4});
    EXPECT_EQ(li[0], 1);
    EXPECT_EQ(li[1], 2);
    EXPECT_EQ(li[2], 3);
    EXPECT_EQ(li[3], 4);

    li = {5, 6, 7, 8, 9};
    EXPECT_EQ(li[0], 5);
    EXPECT_EQ(li[1], 6);
    EXPECT_EQ(li[2], 7);
    EXPECT_EQ(li[3], 8);
    EXPECT_EQ(li[4], 9);
}

TEST(test_constructor_case, case_operator_equal) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);

    LinkedList<int> li_equal;
    li_equal = li;
    EXPECT_EQ(li_equal[0], 1);
    EXPECT_EQ(li_equal[1], 2);
    EXPECT_EQ(li_equal[2], 3);
    EXPECT_EQ(li_equal[3], 4);
}

TEST(test_clear_case, case_empty_list) {
    LinkedList<int> li;
    li.clear();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_clear_case, case_size_1_list) {
    LinkedList<int> li;
    li.push_back(1);
    li.clear();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_clear_case, case_size_n_list) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.clear();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_push_back_case, case_empty_list) {
    LinkedList<int> li;
    li.push_back(1);
    EXPECT_EQ(li._size, 1);
    EXPECT_EQ(li._head, li._tail);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
}

TEST(test_push_back_case, case_size_n_list) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);
    EXPECT_EQ(li._size, 4);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li._head->value, 1);
    EXPECT_EQ(li._head->next->value, 2);
    EXPECT_EQ(li._head->next->next->value, 3);
    EXPECT_EQ(li._head->next->next->next->value, 4);
    EXPECT_EQ(li._tail->value, 4);
    EXPECT_EQ(li._tail->prev->value, 3);
    EXPECT_EQ(li._tail->prev->prev->value, 2);
    EXPECT_EQ(li._tail->prev->prev->prev->value, 1);
}

TEST(test_push_front_case, case_empty_list) {
    LinkedList<int> li;
    li.push_front(1);
    EXPECT_EQ(li._size, 1);
    EXPECT_EQ(li._head, li._tail);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
}

TEST(test_push_front_case, case_size_n_list) {
    LinkedList<int> li;
    li.push_front(1);
    li.push_front(2);
    li.push_front(3);
    li.push_front(4);
    EXPECT_EQ(li._size, 4);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li._head->value, 4);
    EXPECT_EQ(li._head->next->value, 3);
    EXPECT_EQ(li._head->next->next->value, 2);
    EXPECT_EQ(li._head->next->next->next->value, 1);
    EXPECT_EQ(li._tail->value, 1);
    EXPECT_EQ(li._tail->prev->value, 2);
    EXPECT_EQ(li._tail->prev->prev->value, 3);
    EXPECT_EQ(li._tail->prev->prev->prev->value, 4);
}

TEST(test_pop_back_case, case_empty_list) {
    LinkedList<int> li;
    li.pop_back();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_pop_back_case, case_size_1_list) {
    LinkedList<int> li;
    li.push_back(1);
    li.pop_back();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_pop_back_case, case_size_n_list) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);
    li.pop_back();
    EXPECT_EQ(li._size, 3);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li._head->value, 1);
    EXPECT_EQ(li._head->next->value, 2);
    EXPECT_EQ(li._head->next->next->value, 3);
    EXPECT_EQ(li._tail->value, 3);
    EXPECT_EQ(li._tail->prev->value, 2);
    EXPECT_EQ(li._tail->prev->prev->value, 1);
}

TEST(test_pop_front_case, case_empty_list) {
    LinkedList<int> li;
    li.pop_front();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_pop_front_case, case_size_1_list) {
    LinkedList<int> li;
    li.push_front(1);
    li.pop_front();
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_pop_front_case, case_size_n_list) {
    LinkedList<int> li;
    li.push_front(1);
    li.push_front(2);
    li.push_front(3);
    li.push_front(4);
    li.pop_front();
    EXPECT_EQ(li._size, 3);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li._head->value, 3);
    EXPECT_EQ(li._head->next->value, 2);
    EXPECT_EQ(li._head->next->next->value, 1);
    EXPECT_EQ(li._tail->value, 1);
    EXPECT_EQ(li._tail->prev->value, 2);
    EXPECT_EQ(li._tail->prev->prev->value, 3);
}

TEST(test_empty_case, case) {
    LinkedList<int> li;
    EXPECT_TRUE(li.empty());

    li.push_back(1);
    EXPECT_FALSE(li.empty());

    li.pop_back();
    EXPECT_TRUE(li.empty());
}

TEST(test_at_case, case) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);

    EXPECT_EQ(li.at(0), 1);
    EXPECT_EQ(li.at(1), 2);
    EXPECT_EQ(li.at(2), 3);
    EXPECT_EQ(li.at(3), 4);
}

TEST(test_operator_index_case, case) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);

    EXPECT_EQ(li[0], 1);
    EXPECT_EQ(li[1], 2);
    EXPECT_EQ(li[2], 3);
    EXPECT_EQ(li[3], 4);
}

TEST(test_iterator_case, case) {
    LinkedList<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);

    auto it = li.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it.node, li._head);
    EXPECT_EQ(*(++it), 2);
    EXPECT_EQ(it.node, li._head->next);
    EXPECT_EQ(*(it++), 2);
    EXPECT_EQ(it.node, li._head->next->next);
    EXPECT_EQ(*it, 3);

    it = li.end();
    EXPECT_EQ(it.node, nullptr);

    it = li.rbegin();
    EXPECT_EQ(*it, 4);
    EXPECT_EQ(it.node, li._tail);
    EXPECT_EQ(*(it--), 4);
    EXPECT_EQ(it.node, li._tail->prev);
    EXPECT_EQ(*(--it), 2);
    EXPECT_EQ(it.node, li._tail->prev->prev);
    EXPECT_EQ(*it, 2);

    EXPECT_EQ(*(li.begin() + 2), 3);
    EXPECT_EQ(*(li.rbegin() - 2), 2);

    it = li.begin();
    it += 2;
    EXPECT_EQ(*it, 3);

    it = li.rbegin();
    it -= 2;
    EXPECT_EQ(*it, 2);
}

TEST(test_to_string_case, case) {
    LinkedList<int> li;

    EXPECT_EQ(li.to_string(), "[]");

    li.push_back(1);
    EXPECT_EQ(li.to_string(), "[1]");

    li.push_back(2);
    EXPECT_EQ(li.to_string(), "[1, 2]");

    li.push_back(3);
    li.push_back(4);
    EXPECT_EQ(li.to_string(), "[1, 2, 3, 4]");
}

TEST(test_front_back_case, case) {
    LinkedList<int> li;
    li.push_back(1);

    EXPECT_EQ(li.front(), 1);
    EXPECT_EQ(li.back(), 1);

    li.push_back(2);
    li.push_front(0);
    EXPECT_EQ(li.front(), 0);
    EXPECT_EQ(li.back(), 2);
}

TEST(test_insert_case, case_empty_list) {
    LinkedList<int> li;
    auto it = li.insert(li.end(), 1);
    EXPECT_TRUE(it == li.rbegin());
    EXPECT_EQ(li._size, 1);
    EXPECT_NE(li._head, nullptr);
    EXPECT_EQ(li._head, li._tail);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._head->next, nullptr);
}

TEST(test_insert_case, case_size_1_list) {
    LinkedList<int> li0;
    li0.push_back(1);

    LinkedList<int> li1(li0);
    auto it1 = li1.insert(li1.begin(), 0);
    EXPECT_TRUE(it1 == li1.begin());
    EXPECT_EQ(li1._size, 2);
    EXPECT_EQ(li1._head->prev, nullptr);
    EXPECT_EQ(li1._tail->next, nullptr);
    EXPECT_EQ(li1[0], 0);
    EXPECT_EQ(li1[1], 1);

    LinkedList<int> li2(li0);
    auto it2 = li2.insert(li2.end(), 2);
    EXPECT_TRUE(it2 == li2.rbegin());
    EXPECT_EQ(li2._size, 2);
    EXPECT_EQ(li2._head->prev, nullptr);
    EXPECT_EQ(li2._tail->next, nullptr);
    EXPECT_EQ(li2[0], 1);
    EXPECT_EQ(li2[1], 2);
}

TEST(test_insert_case, case_size_n_list) {
    LinkedList<int> li0 = {1, 2, 3, 4};

    LinkedList<int> li1(li0);
    auto it1 = li1.insert(li1.begin(), 0);
    EXPECT_TRUE(li1.begin() == it1);
    EXPECT_EQ(li1._size, 5);
    EXPECT_EQ(li1._head->prev, nullptr);
    EXPECT_EQ(li1._tail->next, nullptr);
    EXPECT_EQ(li1[0], 0);
    EXPECT_EQ(li1[1], 1);
    EXPECT_EQ(li1[2], 2);
    EXPECT_EQ(li1[3], 3);
    EXPECT_EQ(li1[4], 4);

    LinkedList<int> li2(li0);
    auto it2 = li2.insert(li2.end(), 5);
    EXPECT_TRUE(li2.rbegin() == it2);
    EXPECT_EQ(li2._size, 5);
    EXPECT_EQ(li2._head->prev, nullptr);
    EXPECT_EQ(li2._tail->next, nullptr);
    EXPECT_EQ(li2[0], 1);
    EXPECT_EQ(li2[1], 2);
    EXPECT_EQ(li2[2], 3);
    EXPECT_EQ(li2[3], 4);
    EXPECT_EQ(li2[4], 5);

    LinkedList<int> li3(li0);
    auto it3 = li3.insert(li3.begin() + 2, 8);
    EXPECT_TRUE(li3.begin() + 2 == it3);
    EXPECT_EQ(li3._size, 5);
    EXPECT_EQ(li3._head->prev, nullptr);
    EXPECT_EQ(li3._tail->next, nullptr);
    EXPECT_EQ(li3[0], 1);
    EXPECT_EQ(li3[1], 2);
    EXPECT_EQ(li3[2], 8);
    EXPECT_EQ(li3[3], 3);
    EXPECT_EQ(li3[4], 4);
}

TEST(test_erase_case, case_empty_list) {
    LinkedList<int> li;
    auto it = li.erase(li.begin());
    EXPECT_TRUE(it == li.end());
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_erase_case, case_size_1_list) {
    LinkedList<int> li({1});
    auto it = li.erase(li.begin());
    EXPECT_TRUE(it == li.end());
    EXPECT_EQ(li._size, 0);
    EXPECT_EQ(li._head, nullptr);
    EXPECT_EQ(li._tail, nullptr);
}

TEST(test_erase_case, case_size_n_list) {
    LinkedList<int> li0({1, 2, 3, 4});

    LinkedList<int> li1(li0);
    auto it1 = li1.erase(li1.begin());
    EXPECT_TRUE(it1 == li1.begin());
    EXPECT_EQ(li1._size, 3);
    EXPECT_EQ(li1._head->prev, nullptr);
    EXPECT_EQ(li1._tail->next, nullptr);
    EXPECT_EQ(li1[0], 2);
    EXPECT_EQ(li1[1], 3);
    EXPECT_EQ(li1[2], 4);

    LinkedList<int> li2(li0);
    auto it2 = li2.erase(li2.end());
    EXPECT_TRUE(it2 == li2.end());
    EXPECT_EQ(li2._size, 4);
    EXPECT_EQ(li2._head->prev, nullptr);
    EXPECT_EQ(li2._tail->next, nullptr);
    EXPECT_EQ(li2[0], 1);
    EXPECT_EQ(li2[1], 2);
    EXPECT_EQ(li2[2], 3);
    EXPECT_EQ(li2[3], 4);

    LinkedList<int> li3(li0);
    auto it3 = li3.erase(li3.rbegin());
    EXPECT_TRUE(it3 == li3.end());
    EXPECT_EQ(li3._size, 3);
    EXPECT_EQ(li3._head->prev, nullptr);
    EXPECT_EQ(li3._tail->next, nullptr);
    EXPECT_EQ(li3[0], 1);
    EXPECT_EQ(li3[1], 2);
    EXPECT_EQ(li3[2], 3);

    LinkedList<int> li4(li0);
    auto it4 = li4.erase(li4.begin() + 2);
    EXPECT_TRUE(it4 == li4.begin() + 2);
    EXPECT_EQ(li4._size, 3);
    EXPECT_EQ(li4._head->prev, nullptr);
    EXPECT_EQ(li4._tail->next, nullptr);
    EXPECT_EQ(li4[0], 1);
    EXPECT_EQ(li4[1], 2);
    EXPECT_EQ(li4[2], 4);
}

TEST(test_insert_case, case_initializer_list) {
    LinkedList<int> li({1, 2, 3, 6});
    auto it = li.insert(li.begin() + 3, {4, 5});
    EXPECT_TRUE(it == li.begin() + 3);
    EXPECT_EQ(li._size, 6);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li[0], 1);
    EXPECT_EQ(li[1], 2);
    EXPECT_EQ(li[2], 3);
    EXPECT_EQ(li[3], 4);
    EXPECT_EQ(li[4], 5);
    EXPECT_EQ(li[5], 6);

    LinkedList<int> li1;
    auto it1 = li1.insert(li1.begin(), {1, 2});
    EXPECT_TRUE(it1 == li1.begin());
    EXPECT_EQ(li1._size, 2);
    EXPECT_EQ(li1._head->prev, nullptr);
    EXPECT_EQ(li1._tail->next, nullptr);
    EXPECT_EQ(li1[0], 1);
    EXPECT_EQ(li1[1], 2);
}

TEST(test_insert_case, case_input_iterator) {
    LinkedList<int> li({1, 2, 3, 6});
    std::vector<int> vi({4, 5});

    auto it = li.insert(li.begin() + 3, vi.begin(), vi.end());
    EXPECT_TRUE(it == li.begin() + 3);
    EXPECT_EQ(li._size, 6);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li[0], 1);
    EXPECT_EQ(li[1], 2);
    EXPECT_EQ(li[2], 3);
    EXPECT_EQ(li[3], 4);
    EXPECT_EQ(li[4], 5);
    EXPECT_EQ(li[5], 6);
}

TEST(test_erase_case, case_range) {
    LinkedList<int> li1({1, 2, 3, 4});
    auto it1 = li1.erase(li1.begin(), li1.end());
    EXPECT_TRUE(it1 == li1.end());
    EXPECT_EQ(li1._size, 0);
    EXPECT_EQ(li1._head, nullptr);
    EXPECT_EQ(li1._tail, nullptr);

    LinkedList<int> li2({1, 2, 3, 4});
    auto it2 = li2.erase(li2.begin() + 1, li2.begin() + 3);
    EXPECT_TRUE(it2 == li2.begin() + 1);
    EXPECT_EQ(li2._size, 2);
    EXPECT_EQ(li2._head->prev, nullptr);
    EXPECT_EQ(li2._tail->next, nullptr);
    EXPECT_EQ(li2[0], 1);
    EXPECT_EQ(li2[1], 4);
}

TEST(test_operator_add_case, case) {
    LinkedList<int> li({1, 2, 3});
    li += {4, 5, 6};
    EXPECT_EQ(li._size, 6);
    EXPECT_EQ(li._head->prev, nullptr);
    EXPECT_EQ(li._tail->next, nullptr);
    EXPECT_EQ(li[0], 1);
    EXPECT_EQ(li[1], 2);
    EXPECT_EQ(li[2], 3);
    EXPECT_EQ(li[3], 4);
    EXPECT_EQ(li[4], 5);
    EXPECT_EQ(li[5], 6);
}

TEST(test_merge_case, case) {
    LinkedList<int> li1({1, 2, 3});
    LinkedList<int> li2({4, 5});

    li1.merge(li2);
    EXPECT_EQ(li1._size, 5);
    EXPECT_EQ(li1._head->prev, nullptr);
    EXPECT_EQ(li1._tail->next, nullptr);
    EXPECT_EQ(li1[0], 1);
    EXPECT_EQ(li1[1], 2);
    EXPECT_EQ(li1[2], 3);
    EXPECT_EQ(li1[3], 4);
    EXPECT_EQ(li1[4], 5);
}

/* TEST(test_sort_case, case) { */
    /* LinkedList<int> li({6, 3, 4, 1, 5, 2}); */
    /* li.sort(); */
    /* EXPECT_EQ(li._size(), 6); */
    /* EXPECT_EQ(li._head->prev, nullptr); */
    /* EXPECT_EQ(li._tail->next, nullptr); */
    /* EXPECT_EQ(li[0], 1); */
    /* EXPECT_EQ(li[1], 2); */
    /* EXPECT_EQ(li[2], 3); */
    /* EXPECT_EQ(li[3], 4); */
    /* EXPECT_EQ(li[4], 5); */
    /* EXPECT_EQ(li[5], 6); */
/* } */

}  // namespace hl

