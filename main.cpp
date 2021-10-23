#include <functional>

#include <emscripten.h>
#include <SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

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
glm::mat4 pMat, vMat, mMat, mvMat;
GLuint mvLoc, projLoc;
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

void setupVertices(void) { // 36 vertices, 12 triangles, makes 2x2x2 cube placed at origin
    float vertexPositions[108] = {
        -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };

    // glGenVertexArraysOES(1, vao);
    // glBindVertexArrayOES(vao[0]);
    // glGenBuffers(numVBOs, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

int main()
{
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    setupVertices();

    // GLfloat vertices[] = {0.25f, -0.25f, 0.0f, -0.25f, -0.25f, 0.0f, 0.25f, 0.25f, 0.0f};

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // projLoc = glGetUniformLocation(shaderProgram, "proj_matrix");
    // build perspective matrix
     // 1.0472 radians = 60 degrees
    // build view matrix, model matrix, and model-view matrix
cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // shift down Y to reveal perspective
    mMat = glm::mat4(1.0f); //glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
    mvMat = mMat;//vMat * mMat;
    // glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    loop = [&]
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        mvLoc = glGetUniformLocation(shaderProgram, "mv_matrix");
        projLoc = glGetUniformLocation(shaderProgram, "proj_matrix");
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
        pMat = glm::perspective(1.0472f, 1.0f, 0.1f, 1000.0f);
        vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        mvMat = vMat * mMat;
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
        // move a vertex
        // const uint32_t milliseconds_since_start = SDL_GetTicks();
        // const uint32_t milliseconds_per_loop = 3000;
        // // vertices[0] = ( milliseconds_since_start % milliseconds_per_loop ) / float(milliseconds_per_loop) - 0.5f;
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Clear the screen
        if( background_is_black )
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        else
            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle from the 3 vertices
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        SDL_GL_SwapWindow(window);
    };

    emscripten_set_main_loop(main_loop, 0, true);

    return EXIT_SUCCESS;
}