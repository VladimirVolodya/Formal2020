#ifndef UNTITLED_NFA_H
#define UNTITLED_NFA_H
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

class NFA {
    const size_t alphabetPower;
    std::vector<std::unordered_map<size_t, std::set<size_t>>> automata;
    std::unordered_set<size_t> acceptingStates;
    void initialize(const NFA& that);
  public:
    NFA(size_t alphabetPower);
    NFA(size_t alphabetPower, std::vector<std::unordered_map<size_t, std::set<size_t>>> automata,
    std::unordered_set<size_t> acceptingStates);
    NFA(const NFA& nfa);
    void determine();
    void print() const;
    friend void readNFA(NFA& nfa);
    bool operator==(const NFA& that) const;
    NFA& operator=(const NFA& that);
};


#endif //UNTITLED_NFA_H
