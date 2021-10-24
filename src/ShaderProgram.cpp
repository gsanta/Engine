#include <SDL_opengles2.h>
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount)
    : vertexSource(vertexSource), fragmentSource(fragmentSource)  {
        this->vbo = new GLuint[bufferCount];
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