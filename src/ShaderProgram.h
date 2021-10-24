#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <SDL_opengles2.h>

class ShaderProgram {

public:
    ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount);
    ~ShaderProgram();

    void init();
    GLuint getShaderProgram() {
        return shaderProgram;
    }
    GLuint* getVbo() const {
        return vbo;
    }

private:
    GLuint shaderProgram;
    GLuint* vbo;
    const GLchar* vertexSource;
    const GLchar* fragmentSource;
};

#endif