#include <functional>

#include <emscripten.h>
#include <SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "src/ShaderProgram.h"
#include "src/Camera.h"
#include "src/shapes/Cube.h"
#include "src/rendering/Renderer.h"

// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position;                     \n"
    "uniform mat4 mv_matrix;                      \n"
    "uniform mat4 proj_matrix;                    \n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_Position = proj_matrix * mv_matrix * vec4(position.xyz, 1.0);     \n"
    "}                                            \n";

const GLchar* fragmentSource =
    "precision mediump float;\n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);                     \n"
    "}                                            \n";

// an example of something we will control from the javascript side
bool background_is_black = true;

// the function called by the javascript code
extern "C" void EMSCRIPTEN_KEEPALIVE toggle_background_color() { background_is_black = !background_is_black; }

std::function<void()> loop;
void main_loop() { loop(); }

GLuint vbo;
glm::mat4 pMat, mMat, mvMat;
GLuint mvLoc, projLoc;
float cubeLocX, cubeLocY, cubeLocZ;

int main()
{
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    ShaderProgram shaderProgram(vertexSource, fragmentSource, 1);
    shaderProgram.init();
    GLuint shaderProgramId = shaderProgram.getShaderProgram();

    Camera camera(0.0f, 0.0f, 8.0f);

    // setupVertices(shaderProgram, vertexPositions, 108 * sizeof(float));
    Cube cube;
    Renderer renderer(shaderProgram);

    renderer.render(&cube);
    // renderer.render(vertexPositions);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgramId, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // shift down Y to reveal perspective
    mMat = glm::mat4(1.0f); //glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

    loop = [&]
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgramId);

        mvLoc = glGetUniformLocation(shaderProgramId, "mv_matrix");
        projLoc = glGetUniformLocation(shaderProgramId, "proj_matrix");
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
        pMat = glm::perspective(1.0472f, 1.0f, 0.1f, 1000.0f);
        mvMat = camera.getViewMatrix() * mMat;
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        if( background_is_black )
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        else
            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        SDL_GL_SwapWindow(window);
    };

    emscripten_set_main_loop(main_loop, 0, true);

    return EXIT_SUCCESS;
}