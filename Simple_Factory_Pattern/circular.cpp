#include <iostream>
#include "circular.h"


circular::circular(int r):shape(){
    this->r = r;
}

void circular::draw() {
    std::cout << "Drawing a circular with radius " << r << std::endl;
}

void circular::erase() {
    std::cout << "Erasing a circular with radius " << r << std::endl;
}