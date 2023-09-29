#ifndef FORMAL_LANGUAGES_CDFA_H
#define FORMAL_LANGUAGES_CDFA_H
#include <vector>
#include <unordered_set>

class CDFA {
    const int alphabetPower;
    std::vector<std::vector<size_t>> automata;
    std::unordered_set<size_t> acceptingStates;
  public:
    void minimize();
    const std::vector<size_t>& getTransitions(int stateNumber) const;
    explicit CDFA(size_t alphabetPower);
    CDFA(int alphabetPower, std::vector<std::vector<size_t>> automata, std::unordered_set<size_t> acceptingStates);
    std::vector<size_t> getNewEqClasses(const std::vector<size_t>& oldEq= {}) const;
    bool isAccepting(int state) const;
    void print() const;
    friend void readCDFA(CDFA& cdfa);
    bool operator==(const CDFA& that) const;
};


#endif //FORMAL_LANGUAGES_CDFA_H
