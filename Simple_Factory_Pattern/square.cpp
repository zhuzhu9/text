#include <iostream>
#include "square.h"

square::square(int n):shape() {
    this->n = n;
}

void square::draw() {
    std::cout << "Drawing a square with side " << n << std::endl;
}

void square::erase() {
    std::cout << "Erasing a square with side " << n << std::endl;
}