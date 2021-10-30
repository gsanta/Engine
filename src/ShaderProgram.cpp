#include <SDL_opengles2.h>
#include "ShaderProgram.h"
#include <vector>
#include "./shapes/Shape.h"
#include <algorithm>
#include <iterator>


ShaderProgram::ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount)
    : vertexSource(vertexSource), fragmentSource(fragmentSource)
{
        this->vbo = new GLuint[bufferCount];
}

void ShaderProgram::render() {
    for(std::vector<Shape*>::iterator it = std::begin(shapes); it != std::end(shapes); ++it) {
        glBindBuffer(GL_ARRAY_BUFFER, *(getVbo()));
        float* vertices = (*it)->getVertices();
        glBufferData(GL_ARRAY_BUFFER, (*it)->getSize(), vertices, GL_STATIC_DRAW);
    }
}

void ShaderProgram::addShape(Shape* shape)
{
    shapes.push_back(shape);
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::init() {
    glGenBuffers(1, this->vbo);
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