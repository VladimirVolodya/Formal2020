#include "CDFA.h"
#include <iostream>
#include <map>

void readCDFA(CDFA& cdfa) {
    std::vector<std::vector<size_t>> automata;
    std::unordered_set<size_t> acceptingStates;
    std::cout << "Enter the number of states: ";
    size_t statesNumber;
    std::cin >> statesNumber;
    automata.reserve(statesNumber);
    int buffer, acceptingNumber;
    for (size_t i = 0; i < statesNumber; ++i) {
        automata.emplace_back();
        automata.back().reserve(cdfa.alphabetPower);
        std::cout << "Enter transitions from the state №" << i << ' ';
        for (int j = 0; j < cdfa.alphabetPower; ++j) {
            std::cin >> buffer;
            automata.back().push_back(buffer);
        }
    }
    std::cout << "Enter the number of accepting states: ";
    std::cin >> acceptingNumber;
    std::cout << "Enter all accepting states: ";
    for (int i = 0; i < acceptingNumber; ++i) {
        std::cin >> buffer;
        acceptingStates.emplace(buffer);
    }
    cdfa.automata = std::move(automata);
    cdfa.acceptingStates = std::move(acceptingStates);
}

const std::vector<size_t> &CDFA::getTransitions(int stateNumber) const {
    return automata[stateNumber];
}

std::vector<size_t> CDFA::getNewEqClasses(const std::vector<size_t> &oldEq) const {
    std::vector<size_t> result;
    result.reserve(automata.size());
    if (oldEq.empty()) {
        const size_t acceptingClassIndex = 1 - acceptingStates.contains(0);
        for (size_t i = 0; i < automata.size(); ++i) {
            result.push_back((acceptingStates.contains(i) ? acceptingClassIndex : 1 - acceptingClassIndex));
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


bool CDFA::operator==(const CDFA &that) const {
    return automata == that.automata && acceptingStates == that.acceptingStates;
}

CDFA::CDFA(int alphabetPower, std::vector<std::vector<size_t>> automata, std::unordered_set<size_t> acceptingStates) :
alphabetPower(alphabetPower), automata(std::move(automata)), acceptingStates(std::move(acceptingStates)) {}

CDFA::CDFA(size_t alphabetPower) : alphabetPower(alphabetPower) {}
