// @file test_thread_pool.cpp
// @desc 线程池测试
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-06-02

#include <gtest/gtest.h>
#include "thread_pool.hpp"

class TestCallback
{
public:
   void operator()(int i) {
        std::cout << "handle task " << i << std::endl;
   }
};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace hl {

TEST(test_thread_pool, case_thread_pool) {
    hl::ThreadPool<int, TestCallback> pool;
    pool.init(20);

    for (int i = 0; i < 10; i += 2) {
        sleep(1);
        pool.add_task(i);
        pool.add_task(i + 1);
    }

    pool.stop();
    pool.join();
}

}  // namespace hl
