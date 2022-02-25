#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "square.h"
#include "triangle.h"
#include "circular.h"
#include "shape.h"
#include <string>

class factory {
public:
    static shape* createShape(std::string str) {
        if (str == "triangle") {
            return new triangle(1, 2, 3);
        } else if (str == "square") {
            return new square(1);
        } else if (str == "circular") {
            return new circular(1);
        } else {
            return nullptr;
        }
    }
};


#endif // !SHAPEFACTORY_H