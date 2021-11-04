#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <iostream>

class Shape {
public:
    virtual float* getVertices() const = 0;
    virtual std::size_t getSize() const = 0;
    virtual void setTranslate(float x, float y, float z);
    virtual void setScale(float x, float y, float z);
    virtual void setRotate(float axis, float x, float y, float z);
    void setParent(Shape* shape);
    Shape* getParent();
    virtual glm::mat4& getTransform();
    glm::mat4& getAbsoluteTransform();
    void computeMatrices();

private:
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 absoluteTransform = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    Shape* parent = nullptr;
    bool dirty = false;
};

#endif
