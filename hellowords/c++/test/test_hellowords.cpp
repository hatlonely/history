#include "hellowords.h"
#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(initSuite, caseInit) {
    HelloWords helloWords;
    EXPECT_EQ(0, helloWords._words.size());
    ASSERT_EQ(0, helloWords.addWords("../../../data/one.txt", "one"));
    EXPECT_NE(0, helloWords._words.size());
}

TEST(helloWordsSuite, caseHelloWords) {
    HelloWords helloWords;
    ASSERT_EQ(0, helloWords.addWords("../../../data/one.txt", "one"));
    for (int i = 0; i < 10; i++) {
        std::cout << helloWords.helloWords() << std::endl;
    }
}
