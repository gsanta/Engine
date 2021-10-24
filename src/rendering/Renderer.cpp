#include <SDL_opengles2.h>
#include "Renderer.h"

Renderer::Renderer(ShaderProgram* program): program(program) {}

void Renderer::render(Shape* shape) {
    glBindBuffer(GL_ARRAY_BUFFER, *(program->getVbo()));
    float* vertices = shape->getVertices();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}