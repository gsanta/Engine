#include <SDL_opengles2.h>
#include "ShaderProgramImpl.h"
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

ShaderProgramImpl::ShaderProgramImpl(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount)
    : vertexSource(vertexSource), fragmentSource(fragmentSource)
{
}

void ShaderProgramImpl::initBuffers() {
    int counter = 0;
    for(std::vector<Shape*>::iterator it = std::begin(shapes); it != std::end(shapes); ++it) {
        // std::cout << "rendering a shape: " << (*it + counter)->getSize() << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, *(getVbo() + counter));
        float* vertices = (*it)->getVertices();
        glBufferData(GL_ARRAY_BUFFER, (*it)->getSize() * sizeof(float), vertices, GL_STATIC_DRAW);
        counter++;
    }
}

void ShaderProgramImpl::render() {
    for(std::vector<Shape*>::iterator it = std::begin(shapes); it != std::end(shapes); ++it) {
        Shape* shape = *it;

        mvLoc = glGetUniformLocation(shaderProgram, "mv_matrix");
        projLoc = glGetUniformLocation(shaderProgram, "proj_matrix");
        mMat = shape->getTransform();
        pMat = projection->getProjectionMatrix();
        mvMat = camera->getViewMatrix() * mMat;

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        std::cout << "size: " << shape->getSize() / 3 << std::endl;

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, shape->getSize() / 3);
    }
} 

void ShaderProgramImpl::addShape(Shape* shape)
{
    shapes.push_back(shape);
}

void ShaderProgramImpl::setProjection(Proj* projection) {
    this->projection = projection;        
}

void ShaderProgramImpl::setCamera(Camera* camera) {
    this->camera = camera;        
}


ShaderProgramImpl::~ShaderProgramImpl() {}

void ShaderProgramImpl::init() {
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