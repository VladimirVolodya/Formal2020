#include "gtest/gtest.h"
#include "NFA.h"

namespace {
    class NFA_testing : public testing::Test {
      public:
        NFA_testing() {}
    };
}


TEST(BaseTests, OneState) {
    NFA nfa(2, {{}}, {0});
    auto nfaCpy = nfa;
    nfa.determine();
    EXPECT_EQ(nfa, nfaCpy);
}

TEST(BaseTests, TwoEqStates) {
    NFA nfa(2, {{{1, {1, 2}}}, {}, {}}, {1, 2});
    NFA expectedDFA(2, {{{1, {1}}}, {}}, {1});
    nfa.determine();
    EXPECT_EQ(nfa, expectedDFA);
}

TEST(AdvancedTests, ThreeStates) {
    NFA nfa(2, {{{0, {0, 2}}, {1, {1}}},
                {{0, {0, 2}}, {1, {1}}},
                {{1, {1, 2}}}}, {1});
    nfa.determine();
    NFA expectedDFA(2, { {{0, {1}}, {1, {2}}},
                         {{0, {1}}, {1, {3}}},
                         {{0, {1}}, {1, {2}}},
                         {{0, {1}}, {1, {3}}} }, {2, 3});
    EXPECT_EQ(expectedDFA, nfa);
}

TEST(AdvanceTests, FiveStates) {
    NFA nfa(3, { {{1, {1}}}, {{0, {4}}, {2, {2, 3}}},
                 {{2, {1}}}, {{2, {4}}}, {{2, {3}}} }, {4});
    NFA expectedNFA(3, { {{1, {1}}}, {{0, {2}}, {2, {3}}}, {{2, {4}}},
                         {{2, {5}}}, {{2, {2}}}, {{0, {2}}, {2, {3}}} }, {2, 5});
    nfa.determine();
    EXPECT_EQ(expectedNFA, nfa);
}