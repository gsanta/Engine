#include <SDL_opengles2.h>
#include "Renderer.h"
#include "../ShaderProgram.h"

void Renderer::render(ShaderProgram& program, Shape* shape) {
    glBindBuffer(GL_ARRAY_BUFFER, *(program.getVbo()));
    float* vertices = shape->getVertices();
    glBufferData(GL_ARRAY_BUFFER, shape->getSize(), shape->getVertices(), GL_STATIC_DRAW);
}
