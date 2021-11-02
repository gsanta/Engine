
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <SDL_opengles2.h>
#include <vector>
#include "../shapes/Shape.h"
#include "../shapes/Cube.h"
#include "../rendering/Proj.h"
#include "../Camera.h"

class ShaderProgram {

public:
    void virtual init() = 0;
    void virtual addShape(Shape* shape) = 0;
    void virtual initBuffers() = 0;
    // void render(Cube* shape);
    void virtual render() = 0;
    void virtual setProjection(Proj* proj) = 0;
    void virtual setCamera(Camera* camera) = 0;
    virtual GLuint getShaderProgram() = 0;
    virtual GLuint* getVbo() const = 0;
};

#endif