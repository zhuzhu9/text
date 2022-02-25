#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "shape.h"

class triangle : public shape {
public:
    triangle(int a, int b, int c);
    ~triangle(){};
    virtual void draw();
    virtual void erase();

private:
    int a, b, c;
};

#endif // !TRIANGLE_H