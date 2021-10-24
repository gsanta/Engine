
#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape {

public:
    Cube();
    ~Cube();

    virtual float* getVertices() const {
        return vertices;
    }

private:
    float* vertices;
};

#endif