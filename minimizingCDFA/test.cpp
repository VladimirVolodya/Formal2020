#include "gtest/gtest.h"
#include "CDFA.h"

namespace {
    class CDFA_Testing : public testing::Test {
      public:
        CDFA_Testing() {}
    };
}

TEST(BaseTests, ConstructorTest) {
    CDFA cdfa(2);
}

TEST(BaseTests, GettingTransitionTest) {
    CDFA cdfa(2, {{1, 1}, {1, 1}}, {1});
    std::vector<size_t> expectedTransitions = {1, 1};
    EXPECT_EQ(expectedTransitions, cdfa.getTransitions(0));
    EXPECT_EQ(expectedTransitions, cdfa.getTransitions(1));
}

TEST(BaseTests, ZeroEqClassTest) {
    CDFA first_cdfa(2, {{}, {}, {}, {}}, {1, 2});
    CDFA second_CDFA(2, {{}, {}, {}, {}}, {1});
    std::vector<size_t> firstExpectedClass = {0, 1, 1, 0};
    std::vector<size_t> secondExpectedClass = {0, 1, 0, 0};
    EXPECT_EQ(firstExpectedClass, first_cdfa.getNewEqClasses());
    EXPECT_EQ(secondExpectedClass, second_CDFA.getNewEqClasses());
}

TEST(AdvancedTests, EqClassesTest) {
    CDFA cdfa(2, {{1, 2}, {3, 3}, {3, 3}, {3, 3}}, {3});
    std::vector<size_t> expectedDistribution = {0, 1, 1, 2};
    EXPECT_EQ(cdfa.getNewEqClasses(cdfa.getNewEqClasses()), expectedDistribution);
}

TEST(AdvancedTests, MinimizingTest) {
    CDFA cdfa(2, {{1, 3}, {2, 4}, {0, 5}, {4, 6}, {5, 7}, {3, 8}, {7, 0}, {8, 1}, {6, 2}},
              {0, 4, 8});
    cdfa.minimize();
    CDFA expectedMinCDFA(2, {{1, 2}, {2, 0}, {0, 1}}, {0});
    EXPECT_EQ(cdfa, expectedMinCDFA);
}
