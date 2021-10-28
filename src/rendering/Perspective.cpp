#include "Perspective.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Perspective::Perspective(PerspectiveOptions options) {
    projectionMat = glm::perspective(1.0472f, 1.0f, 0.1f, 1000.0f);
}

Perspective::~Perspective() {}