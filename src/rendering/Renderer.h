#ifndef RENDERER_H
#define RENDERER_H

#include "../shapes/Shape.h"
#include "../ShaderProgram.h"

class ShaderProgram;

class Renderer {

public:
    void render(ShaderProgram& program, Shape* shape);
};

#endif
