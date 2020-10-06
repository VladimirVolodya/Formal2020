#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>

class CDFA {
    std::vector<std::vector<size_t>> automata;
    std::unordered_set<size_t> acceptingStates;
    const int alphabetPower;
  public:
    void minimize();
    const std::vector<size_t>& getTransitions(int stateNumber) const;
    explicit CDFA(int alphabetPower, int statesNumber);
    std::vector<size_t> getNewEqClasses(const std::vector<size_t>& oldEq= {}) const;
    size_t getNumberOfStates() const;
    bool isAccepting(int state) const;
    void print() const;
};

int main() {
    int alphabetPower, statesNumber;
    std::cout << "Enter alphabet power and number of states in CDFA:\n";
    std::cin >> alphabetPower >> statesNumber;
    CDFA cdfa(alphabetPower, statesNumber);
    cdfa.minimize();
    cdfa.print();
}

CDFA::CDFA(int alphabetPower, int statesNumber) : alphabetPower(alphabetPower) {
    automata.reserve(statesNumber);
    int buffer, acceptingNumber;
    for (int i = 0; i < statesNumber; ++i) {
        automata.emplace_back();
        automata.back().reserve(alphabetPower);
        std::cout << "Enter transitions from the state №" << i << '\n';
        for (int j = 0; j < alphabetPower; ++j) {
            std::cin >> buffer;
            automata.back().push_back(buffer);
        }
    }
    std::cout << "Enter the number of accepting states:\n";
    std::cin >> acceptingNumber;
    std::cout << "Enter all accepting states:\n";
    for (int i = 0; i < acceptingNumber; ++i) {
        std::cin >> buffer;
        acceptingStates.emplace(buffer);
    }
}

const std::vector<size_t> &CDFA::getTransitions(int stateNumber) const {
    return automata[stateNumber];
}

std::vector<size_t> CDFA::getNewEqClasses(const std::vector<size_t> &oldEq) const {
    std::vector<size_t> result;
    result.reserve(automata.size());
    if (oldEq.empty()) {
        for (size_t i = 0; i < automata.size(); ++i) {
            result.push_back((acceptingStates.contains(i) ? 0 : 1));
        }
        return result;
    }
    std::vector<std::vector<int>> eqTransitions;
    eqTransitions.reserve(automata.size());
    for (size_t i = 0; i < automata.size(); ++i) {
        eqTransitions.emplace_back();
        eqTransitions.back().reserve(alphabetPower);
        for (const auto& transition : getTransitions(i)) {
            eqTransitions.back().push_back(oldEq[transition]);
        }
        eqTransitions.back().push_back(oldEq[i]);
    }
    std::map<std::vector<int>, int> newTransitions;
    for (const auto& key : eqTransitions) {
        if (!newTransitions.contains(key)) {
            newTransitions.emplace(key, newTransitions.size());
        }
        result.push_back(newTransitions[key]);
    }
    return result;
}

size_t CDFA::getNumberOfStates() const {
    return automata.size();
}

bool CDFA::isAccepting(int state) const {
    return acceptingStates.contains(state);
}

void CDFA::minimize() {
    std::vector<size_t> oldClasses = getNewEqClasses();
    std::vector<size_t> newClasses = getNewEqClasses(oldClasses);
    while (oldClasses != newClasses) {
        oldClasses = std::move(newClasses);
        newClasses = getNewEqClasses(oldClasses);
    }
    std::vector<std::vector<size_t>> oldAutomata = std::move(automata);
    std::unordered_set<size_t> oldAcceptingStates = std::move(acceptingStates);
    for (const auto& state : oldAcceptingStates) {
        acceptingStates.insert(newClasses[state]);
    }
    for (size_t i = 0; i < newClasses.size(); ++i) {
        if (newClasses[i] >= automata.size()) {
            automata.emplace_back();
            automata.back().reserve(alphabetPower);
            for (const size_t & transition : oldAutomata[i]) {
                automata.back().push_back(newClasses[transition]);
            }
        }
    }
}

void CDFA::print() const {
    for (size_t i = 0; i < automata.size(); ++i) {
        std::cout << i << ' ';
        for (const size_t & transition : automata[i]) {
            std::cout << transition << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Accepting states:\n";
    for (const auto& state : acceptingStates) {
        std::cout << state << ' ';
    }
}
