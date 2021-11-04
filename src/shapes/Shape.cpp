#include "./Shape.h"
#include <glm/gtc/matrix_transform.hpp>

void Shape::setScale(float x, float y, float z) {
    this->scale = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
    this->dirty = true;
}

void Shape::setTranslate(float x, float y, float z) {
    this->translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    this->dirty = true;
}

void Shape::setRotate(float axis, float x, float y, float z) {
    this->rotate = glm::rotate(glm::mat4(1.0f), (float)axis, glm::vec3(x, y, z));
    this->dirty = true;
}

void Shape::setParent(Shape* shape) {
    this->parent = shape;
}

glm::mat4& Shape::getTransform() {
    this->computeMatrices();

    return this->transform;
}

glm::mat4& Shape::getAbsoluteTransform() {
    this->computeMatrices();

    return this->absoluteTransform;
}

void Shape::computeMatrices() {
    if (this->dirty) {
        this->transform = this->translate * this->rotate * this->scale;
    }
    if (this->parent) {
        this->absoluteTransform = this->parent->getAbsoluteTransform() * this->transform;
    } else {
        this->absoluteTransform = this->parent == nullptr ? this->transform : this->parent->getAbsoluteTransform() * this->transform;
    }

    this->dirty = false;
}

Shape* Shape::getParent() {
    return this->parent;
}