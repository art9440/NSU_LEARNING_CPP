#include <iostream>
#include "BitArray_lab1.h"


int main() {
    BitArray bitArr_1(3, 5), bitArr_2(3, 2);
    bitArr_1 &= bitArr_2;
    std::cout << bitArr_1.to_string() << std::endl;
    

    return 0;
}