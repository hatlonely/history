// @file test_blocking_queue.cpp
// @desc 测试BlockingQueue
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-05-12

#include "blocking_queue.hpp"
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace hl {

TEST(test_constructor_case, case_constructor)
{
    BlockingQueue<int> bq1;
    EXPECT_EQ(bq1._max_queue_size, 60000U);

    BlockingQueue<int> bq2(66U);
    EXPECT_EQ(bq2._max_queue_size, 66U);
}

TEST(test_offer_case, case_offer)
{
    BlockingQueue<int> bq(6U);
    ASSERT_EQ(bq._max_queue_size, 6U);
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(bq.offer(i, 500000UL));
    }
    EXPECT_FALSE(bq.offer(6, 500000UL));
    EXPECT_EQ(6U, bq.size());
    EXPECT_TRUE(bq.full());
    EXPECT_FALSE(bq.empty());
}

TEST(test_poll_case, case_poll)
{
    BlockingQueue<int> bq(6U);
    ASSERT_EQ(bq._max_queue_size, 6U);
    int element;
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(bq.offer(i, 500000UL));
    }
    EXPECT_TRUE(bq.poll(element, 500000UL));
    EXPECT_EQ(0, element);
    EXPECT_TRUE(bq.poll(element, 500000UL));
    EXPECT_EQ(1, element);
    EXPECT_TRUE(bq.poll(element, 500000UL));
    EXPECT_EQ(2, element);
    EXPECT_TRUE(bq.poll(element, 500000UL));
    EXPECT_EQ(3, element);
    EXPECT_TRUE(bq.poll(element, 500000UL));
    EXPECT_EQ(4, element);
    EXPECT_TRUE(bq.poll(element, 500000UL));
    EXPECT_EQ(5, element);
    EXPECT_FALSE(bq.poll(element, 500000UL));
    EXPECT_EQ(0U, bq.size());
    EXPECT_TRUE(bq.empty());
    EXPECT_FALSE(bq.full());
}

TEST(test_put_case, case_put)
{
    BlockingQueue<int> bq(6U);
    for (int i = 0; i < 6; i++) {
        bq.put(i);
    }
    EXPECT_EQ(6U, bq.size());
    EXPECT_TRUE(bq.full());
    EXPECT_FALSE(bq.empty());
}

TEST(test_take_case, case_take)
{
    BlockingQueue<int> bq(6U);
    for (int i = 0; i < 6; i++) {
        bq.put(i);
    }
    int element;
    bq.take(element);
    EXPECT_EQ(0, element);
    bq.take(element);
    EXPECT_EQ(1, element);
    bq.take(element);
    EXPECT_EQ(2, element);
    bq.take(element);
    EXPECT_EQ(3, element);
    bq.take(element);
    EXPECT_EQ(4, element);
    bq.take(element);
    EXPECT_EQ(5, element);
    EXPECT_EQ(0U, bq.size());
    EXPECT_FALSE(bq.full());
    EXPECT_TRUE(bq.empty());
}

} // namespace hl
