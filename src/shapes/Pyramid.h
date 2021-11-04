
#ifndef PYRAMID_H
#define PYRAMID_H

#include <iostream>
#include <glm/glm.hpp>
#include "Shape.h"

class Pyramid : public Shape {

public:
    Pyramid();
    ~Pyramid();

    virtual float* getVertices() const {
        return vertices;
    }

    virtual std::size_t getSize() const {
        return size;
    }
private:
    float* vertices;
    std::size_t size = 54;
    glm::mat4 transform = glm::mat4(1.0f);
};

#endif