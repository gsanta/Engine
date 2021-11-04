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

glm::mat4& Shape::getTransform() {
    if (this->dirty) {
        this->transform = this->translate * this->rotate * this->scale;
    }

    return this->transform;
}