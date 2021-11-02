#ifndef SHADERPROGRAMIMPL_H
#define SHADERPROGRAMIMPL_H

#include <SDL_opengles2.h>
#include <vector>
#include "./shapes/Shape.h"
#include "./rendering/Proj.h"
#include "./Camera.h"
#include "./program/ShaderProgram.h"

class ShaderProgramImpl : ShaderProgram {

public:
    ShaderProgramImpl(const GLchar* vertexSource, const GLchar* fragmentSource, int bufferCount);
    ~ShaderProgramImpl();

    void init();
    void addShape(Shape* shape);
    void initBuffers();
    // void render(Cube* shape);
    void render();
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