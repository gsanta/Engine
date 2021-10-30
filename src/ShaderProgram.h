#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <SDL_opengles2.h>
#include <vector>
#include "./shapes/Shape.h"

class ShaderProgram {

public:
    ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount);
    ~ShaderProgram();

    void init();
    void addShape(Shape* shape);
    void initBuffers();
    void render();
    GLuint getShaderProgram() {
        return shaderProgram;
    }
    GLuint* getVbo() const {
        return vbo;
    }

private:
    GLuint shaderProgram;
    GLuint* vbo = nullptr;
    const GLchar* vertexSource;
    const GLchar* fragmentSource;
    std::vector<Shape*> shapes;
};

#endif