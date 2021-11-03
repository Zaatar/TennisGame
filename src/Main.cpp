#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <GL/GLU.h>

using std::cout;
using std::endl;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc = 0, char **argv = nullptr)
{
    GLfloat points[] = {
        0.1f, 0.1f, 0.0f,
        0.9f, 0.1f, 0.0f,
        0.9f, 0.9f, 0.0f,
        0.1f, 0.9f, 0.0f};

    //Handle args
    if (argc > 0)
    {
        for (int i = 0; i < argc; ++i)
        {
            cout << argv[i] << endl;
        }
    }

    SDL_Window *window = nullptr;
    SDL_GLContext context;
    int flags = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL failed to initialize." << endl;
        return 1;
    }

    //Initialize window and openGL
    window = SDL_CreateWindow("Tennis Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vao = 0;
    GLuint vbo = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char *vertexShader =
        "#version 430\n"
        "in vec3 vertexPosition;"
        "void main() {"
        "   gl_Position = vec4(vertexPosition, 1.0);"
        "}";

    const char *fragmentShader =
        "#version 430\n"
        "out vec4 fragmentColor;"
        "void main() {"
        "   fragmentColor = vec4(1.0f,1.0f,1.0f,1.0f);"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    cout << "Vertex Shader created!" << endl;
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    cout << "Fragment Shader created!" << endl;
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    cout << "Shader program created!" << endl;

    //Get info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported: " << version << endl;

    //Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); //enable depth testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    //Set viewport and clear color
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

    cout << "Prior to using shader program" << endl;
    glUseProgram(shaderProgram);
    cout << "After using shader program" << endl;
    glBindVertexArray(vao);
    cout << "After binding vertex array" << endl;
    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

    /*GLUquadricObj *quadric = NULL;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluSphere(quadric, 0.15f, 15, 15);
    */
    SDL_GL_SwapWindow(window); //Swapbuffer

    //Quit
    SDL_Delay(5000);
    //gluDeleteQuadric(quadric);
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);

    return 0;
}