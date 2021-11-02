#ifndef RENDERER_H
#define RENDERER_H

#include "../shapes/Shape.h"
#include "../ShaderProgramImpl.h"

class ShaderProgramImpl;

class Renderer {

public:
    void render(ShaderProgramImpl& program, Shape* shape);
};

#endif
