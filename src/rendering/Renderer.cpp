#include <SDL_opengles2.h>
#include "Renderer.h"
#include "../ShaderProgramImpl.h"

void Renderer::render(ShaderProgramImpl& program, Shape* shape) {
    glBindBuffer(GL_ARRAY_BUFFER, *(program.getVbo()));
    float* vertices = shape->getVertices();
    glBufferData(GL_ARRAY_BUFFER, shape->getSize(), shape->getVertices(), GL_STATIC_DRAW);
}
