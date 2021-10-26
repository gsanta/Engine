#ifndef MATRIX_H
#define MATRIX_H

#include <glm/glm.hpp>

class Matrix {

public:
    static Matrix* CreateTransform(float x, float y, float z);
private:
    Matrix(glm::mat4 matrix);
    
    glm::mat4 matrix;
};

#endif