#ifndef SHAPE_H
#define SHAPE_H

class shape {
public:
    virtual ~shape(){}
public:
    virtual void draw() = 0;
    virtual void erase() = 0;
};

#endif