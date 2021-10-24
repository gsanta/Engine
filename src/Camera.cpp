#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float x, float y, float z) : x(x), y(y), z(z) 
{
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-x, -y, -z));
}

Camera::~Camera() {}

