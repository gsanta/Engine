#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <iostream>

class Shape {
public:
    virtual float* getVertices() const = 0;
    virtual std::size_t getSize() const = 0;
    virtual void translate(float x, float y, float z) = 0;
    virtual glm::mat4& getTransform() = 0;
};

#endif
