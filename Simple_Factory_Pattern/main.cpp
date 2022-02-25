#include <iostream>
#include "shapeFactory.h"

using namespace std;

int main(int argc, char* argv[]) {
    factory* fac = new factory();
    shape*   s   = fac->createShape("triangle");
    s->draw();
    s->erase();

    shape* s2 = fac->createShape("square");
    s2->draw();
    s2->erase();

    shape* s3 = fac->createShape("circular");
    s3->draw();
    s3->erase();

    return 0;
}