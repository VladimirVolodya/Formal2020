#include <iostream>
#include <vector>

#include "NFA.h"

int main() {
    size_t alphabetPower;
    std::cout << "Enter the alphabet power: ";
    std::cin >> alphabetPower;
    NFA nfa(alphabetPower);
    readNFA(nfa);
    nfa.determine();
    nfa.print();
}