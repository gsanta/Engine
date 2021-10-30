
#ifndef CUBE_H
#define CUBE_H

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

    virtual glm::mat4& getTransform() {
        return transform;
    }

    virtual void translate(float x, float y, float z);

private:
    float* vertices;
    std::size_t size = sizeof(float) * 108;
    glm::mat4 transform = glm::mat4(1.0f);
};

#endif