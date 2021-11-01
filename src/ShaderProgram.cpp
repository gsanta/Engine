#include <SDL_opengles2.h>
#include "ShaderProgram.h"
#include <vector>
#include "./shapes/Shape.h"
#include "./shapes/Cube.h"
#include "./rendering/Proj.h"
#include "./Camera.h"
#include <algorithm>
#include <iterator>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

ShaderProgram::ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount)
    : vertexSource(vertexSource), fragmentSource(fragmentSource)
{
}

void ShaderProgram::initBuffers() {
    int counter = 0;
    for(std::vector<Shape*>::iterator it = std::begin(shapes); it != std::end(shapes); ++it) {
        // std::cout << "rendering a shape: " << (*it + counter)->getSize() << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, *(getVbo() + counter));
        float* vertices = (*it)->getVertices();
        glBufferData(GL_ARRAY_BUFFER, (*it)->getSize(), vertices, GL_STATIC_DRAW);
        counter++;
    }
}

// void ShaderProgram::render(Cube* shape) {
//         glClear(GL_DEPTH_BUFFER_BIT);
//         glUseProgram(shaderProgram);

//         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//     // for(std::vector<Shape*>::iterator it = std::begin(shapes); it != std::end(shapes); ++it) {
//         // Shape* shape = *it;
//     mvLoc = glGetUniformLocation(shaderProgram, "mv_matrix");
//     projLoc = glGetUniformLocation(shaderProgram, "proj_matrix");
//     std::cout << "projloc " << mvLoc << " mvloc: " << mvLoc << std::endl;
//     mMat = shape->getTransform();
//     // pMat = glm::perspective(1.0472f, 1.0f, 0.1f, 1000.0f);
//     pMat = projection->getProjectionMatrix();
//     mvMat = camera->getViewMatrix() * mMat;

//     glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
//     glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LEQUAL);
//     glDrawArrays(GL_TRIANGLES, 0, 36);
//     // }
// }

void ShaderProgram::render(Cube* cube, Proj* perspective) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mvLoc = glGetUniformLocation(shaderProgram, "mv_matrix");
    projLoc = glGetUniformLocation(shaderProgram, "proj_matrix");
    std::cout << "camera " << camera->getX() << std::endl;
    mMat = cube->getTransform();
    // pMat = glm::perspective(1.0472f, 1.0f, 0.1f, 1000.0f);
    pMat = perspective->getProjectionMatrix();
    mvMat = camera->getViewMatrix() * mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
} 

void ShaderProgram::addShape(Shape* shape)
{
    shapes.push_back(shape);
}

void ShaderProgram::setProjection(Proj* projection) {
    this->projection = projection;        
}

void ShaderProgram::setCamera(Camera* camera) {
    this->camera = camera;        
}


ShaderProgram::~ShaderProgram() {}

void ShaderProgram::init() {
    if (this->vbo != nullptr) {
        delete[] this->vbo;
    }
    this->vbo = new GLuint[this->shapes.size()];
    glGenBuffers(this->shapes.size(), this->vbo);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
}