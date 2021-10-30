#include <SDL_opengles2.h>
#include "ShaderProgram.h"
#include <vector>
#include "./shapes/Shape.h"
#include <algorithm>
#include <iterator>


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

void ShaderProgram::render() {
    for(std::vector<Shape*>::iterator it = std::begin(shapes); it != std::end(shapes); ++it) {
        Shape* shape = *it;
        GLuint mvLoc = glGetUniformLocation(shaderProgram, "mv_matrix");
        GLuint projLoc = glGetUniformLocation(shaderProgram, "proj_matrix");
        glm::mat4 mMat = shape->getTransform();
        // pMat = glm::perspective(1.0472f, 1.0f, 0.1f, 1000.0f);
        glm::mat4 pMat = perspective.getProjectionMatrix();
        glm::mat4 mvMat = camera.getViewMatrix() * mMat;
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void ShaderProgram::addShape(Shape* shape)
{
    shapes.push_back(shape);
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