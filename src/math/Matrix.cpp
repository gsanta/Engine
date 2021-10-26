#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Matrix.h"


Matrix::Matrix(glm::mat4 matrix) : matrix(matrix) {}

Matrix* Matrix::CreateTransform(float x, float y, float z) {
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, x));
    return new Matrix(matrix);
}