#ifndef RENDERER_H
#define RENDERER_H

#include "../shapes/Shape.h"
#include "../ShaderProgram.h"

class Renderer {

public:
    Renderer(ShaderProgram* program);
    void render(Shape* shape);

private:
    ShaderProgram* program;
};

#endif
