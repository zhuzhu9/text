#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "shape.h"

class circular : public shape {
public:
    circular(int r);
    ~circular(){};
    void draw();
    void erase();

private:
    int r;
};

#endif // !CIRCULAR_H