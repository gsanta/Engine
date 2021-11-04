#include <functional>

#include <emscripten.h>
#include <SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "src/ShaderProgramImpl.h"
#include "src/Camera.h"
#include "src/shapes/Cube.h"
#include "src/shapes/Pyramid.h"
#include "src/rendering/Renderer.h"
#include "src/rendering/Perspective.h"
#include "src/rendering/Proj.h"

// Shader sources
const GLchar* vertexSource =
    "attribute vec3 position;                     \n"
    "uniform mat4 mv_matrix;                      \n"
    "uniform mat4 proj_matrix;                    \n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);     \n"
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

int main()
{
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Renderer* renderer = new Renderer();
    ShaderProgramImpl* shaderProgram = new ShaderProgramImpl(vertexSource, fragmentSource, 1);

    PerspectiveOptions perspectiveOptions;
    perspectiveOptions.fieldOfView = 1.0472f; 
    perspectiveOptions.aspect = 1.0f; 
    perspectiveOptions.zNear = 0.1f; 
    perspectiveOptions.zFar = 1000.0f; 

    Perspective* perspective = new Perspective(perspectiveOptions);

    shaderProgram->setProjection(perspective);

    Camera* camera = new Camera(0.0f, 0.0f, 8.0f);
    std::cout << camera->getX() << std::endl;
    shaderProgram->setCamera(camera);

    Cube* cube = new Cube();
    Cube* cube2 = new Cube();
    Pyramid* pyramid = new Pyramid();
    pyramid->setTranslate(-2.0f, 0.0f, 0.0f);
    cube->setTranslate(0.0f, -2.0f, 0.0f);
    cube2->setTranslate(1.0f, 0.0f, 0.0f);
    cube2->setParent(cube);
    // cube2->setScale(0.5f, 0.5f, 0.5f);
    // cube2->setRotate(0.8f, 0.0f, 0.0f, 1.0f);
    shaderProgram->addShape(cube2);
    shaderProgram->addShape(cube);
    shaderProgram->addShape(pyramid);
    shaderProgram->init();
    GLuint shaderProgramId = shaderProgram->getShaderProgram();

    shaderProgram->initBuffers();

    GLint posAttrib = glGetAttribLocation(shaderProgramId, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // mMat = glm::mat4(1.0f); //glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

    loop = [&]
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgramId);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->render();

        SDL_GL_SwapWindow(window);
    };

    emscripten_set_main_loop(main_loop, 0, true);

    return EXIT_SUCCESS;
}

