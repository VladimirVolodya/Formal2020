#include "NFA.h"
#include <iostream>
#include <queue>
#include <map>

NFA::NFA(size_t alphabetPower) : alphabetPower(alphabetPower) {}

void NFA::determine() {
    auto oldAutomata = std::move(automata);
    auto oldAcceptingStates = std::move(acceptingStates);
    std::queue<std::set<size_t>> queue;
    std::unordered_set<size_t> used_states;
    std::map<std::set<size_t>, size_t> indexes;
    std::unordered_map<size_t, std::set<size_t>> currTransitions;
    std::unordered_set<size_t> acceptingTransitions;
    indexes.insert({{0}, 0});
    queue.push({0});
    if (oldAutomata.size() == 1) {
        acceptingStates.insert(0);
    }
    while (!queue.empty()) {
        if (!used_states.contains(indexes[queue.front()])) {
            currTransitions.clear();
            acceptingTransitions.clear();
            for (const auto& state : queue.front()) {
                for (const auto& transition : oldAutomata[state]) {
                    for (const auto& destinationState : transition.second) {
                        if (!currTransitions.contains(transition.first)) {
                            currTransitions.insert({transition.first, {}});
                        }
                        if (oldAcceptingStates.contains(destinationState)) {
                            acceptingTransitions.insert(transition.first);
                        }
                        currTransitions[transition.first].emplace(destinationState);
                    }
                }
            }
            automata.emplace_back();
            for (const auto& transition : currTransitions) {
                if (!indexes.contains(transition.second)) {
                    indexes.emplace(transition.second, indexes.size());
                    queue.emplace(transition.second);
                }
                size_t index = indexes[transition.second];
                if (acceptingTransitions.contains(transition.first)) {
                    acceptingStates.insert(index);
                }
                automata.back().insert({transition.first, {index}});
            }
        }
        used_states.insert(indexes[queue.front()]);
        queue.pop();
    }
}

void NFA::print() const {
    for (size_t i = 0; i < automata.size(); ++i) {
        std::cout << "State № " << i << ":\n";
        if (automata[i].empty()) {
            std::cout << "   No transitions from this state.\n";
        }
        for (const auto& transition : automata[i]) {
            std::cout << "   Transitions by letter with code " << transition.first << ": ";
            for (const auto& destination : transition.second) {
                std::cout << destination << ' ';
            }
            std::cout << "\n";
        }
    }
    std::cout << "Accepting states: ";
    for (const auto& state : acceptingStates) {
        std::cout << state << ' ';
    }
    std::cout << '\n';
}

NFA::NFA(size_t alphabetPower, std::vector<std::unordered_map<size_t, std::set<size_t>>> automata,
         std::unordered_set<size_t> acceptingStates) : alphabetPower(alphabetPower), automata(std::move(automata)),
                                                       acceptingStates(std::move(acceptingStates)) {}

void readNFA(NFA &nfa) {
    std::vector<std::unordered_map<size_t, std::set<size_t>>> automata;
    std::unordered_set<size_t> acceptingStates;
    size_t numberOfStates, numberOfLetters, letterCode;
    std::string buffer_str;
    std::cout << "Enter the number of states: ";
    std::cin >> numberOfStates;
    automata.reserve(numberOfStates);
    for (size_t i = 0; i < numberOfStates; ++i) {
        automata.emplace_back();
        std::cout << "You are working with the state № " << i << '\n';
        std::cout << "Enter the number of different letters by which transitions are possible: ";
        std::cin >> numberOfLetters;
        for (size_t j = 0; j < numberOfLetters; ++j) {
            std::cout << "Enter the letter code (from 0 to " << nfa.alphabetPower - 1 << "): ";
            std::cin >> letterCode;
            automata.back().insert({letterCode, {}});
            std::cout << "Enter all the states where transition by the letter " << j << " is possible. Finish the entering with the symbol \"#\": ";
            while (true) {
                std::cin >> buffer_str;
                if (buffer_str == "#") {
                    break;
                }
                automata.back()[letterCode].insert(strtoul(buffer_str.data(), nullptr, 10));
            }
        }
    }
    std::cout << "Enter all the accepting states, finish entering with the symbol \"#\": ";
    while (true) {
        std::cin >> buffer_str;
        if (buffer_str == "#") {
            break;
        }
        acceptingStates.insert(strtoul(buffer_str.data(), nullptr, 10));
    }
    nfa.automata = std::move(automata);
    nfa.acceptingStates = std::move(acceptingStates);
}

bool NFA::operator==(const NFA &that) const {
    return automata == that.automata && acceptingStates == that.acceptingStates;
}

NFA &NFA::operator=(const NFA &that) {
    if (alphabetPower == that.alphabetPower) {
        initialize(that);
    }
    return *this;
}

NFA::NFA(const NFA &nfa) : alphabetPower(nfa.alphabetPower) {
    initialize(nfa);
}

void NFA::initialize(const NFA &that) {
    automata = that.automata;
    acceptingStates = that.acceptingStates;
}
