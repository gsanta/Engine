#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <SDL_opengles2.h>
#include <vector>
#include "./shapes/Shape.h"
#include "./shapes/Cube.h"
#include "./rendering/Proj.h"
#include "./Camera.h"

class ShaderProgram {

public:
    ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount);
    ~ShaderProgram();

    void init();
    void addShape(Shape* shape);
    void initBuffers();
    // void render(Cube* shape);
    void render(Cube* cube, Proj* perspective);
    void setProjection(Proj* proj);
    void setCamera(Camera* camera);
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
    Proj* projection;
    Camera* camera;
    GLuint mvLoc;
    GLuint projLoc;
    glm::mat4 mMat;
    glm::mat4 pMat;
    glm::mat4 mvMat;
};

#endif