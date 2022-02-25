#include "triangle.h"

triangle::triangle(int a, int b, int c):shape() {
    this->a = a;
    this->b = b;
    this->c = c;
}

void triangle::draw() {
    std::cout << "Drawing a triangle with sides " << a << ", " << b << ", " << c << std::endl;
}

void triangle::erase() {
    std::cout << "Erasing a triangle with sides " << a << ", " << b << ", " << c << std::endl;
}