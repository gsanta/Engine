
#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include "Shape.h"

class Cube : public Shape {

public:
    Cube();
    ~Cube();

    virtual float* getVertices() const {
        return vertices;
    }

    virtual std::size_t getSize() const {
        return size;
    }

private:
    float* vertices;
    std::size_t size = sizeof(float) * 108;
};

#endif