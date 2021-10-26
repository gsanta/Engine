#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

class Shape {
public:
    virtual float* getVertices() const = 0;
    virtual std::size_t getSize() const = 0;
};

#endif
