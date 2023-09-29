#include <iostream>
#include "CDFA.h"

int main() {
    int alphabetPower;
    std::cout << "Enter alphabet power: ";
    std::cin >> alphabetPower;
    CDFA cdfa(alphabetPower);
    readCDFA(cdfa);
    cdfa.minimize();
    cdfa.print();
}