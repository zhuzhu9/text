#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"

class square : public shape {
public:
    square(int n);
    ~square(){};
    virtual void draw();
    virtual void erase();

private:
    int n;
};
#endif
