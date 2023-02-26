#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

void display_square() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0); // Bottom left
    glVertex2i(0, 2); // top left
    glVertex2i(2, 2); // top right
    glVertex2i(2, 0); // bottom right
    glEnd();
    glFlush();
}

void display_checker_board() {
    int squares = 8;
    int matrix[80][2] = {};

    for (float i = -1; i < 1; i += .250) {
        for (float j = -1; j < 1; j += .250) {
            
        }
    }
}


int main (int ArgCount, char **Args)
{
    class sqaure {
    public:
        int x = 500;
        int y = 500;
        int width = 50;
        int height = 50;
    };

    uint32_t windowFlags = SDL_WINDOW_OPENGL;
    SDL_Window* window =
            SDL_CreateWindow(
                    "OpenGL Test",
                    200,
                    100,
                    WIN_WIDTH,
                    WIN_HEIGHT,
                    windowFlags
            );
    assert(window);
    SDL_GLContext Context = SDL_GL_CreateContext(window);

    int32_t running = 1;
    int32_t fullscreen = 0;
    float red = 1.0f;
    float green = 1.0f;
    float blue = 1.0f;

    while (running)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_KEYDOWN) {
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case 'f':
                        fullscreen = !fullscreen;
                        if (fullscreen) {
                            SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        } else {
                            SDL_SetWindowFullscreen(window, windowFlags);
                        }
                        break;
                    case 'n':
                        red = 1.0f;
                        break;
                    case 'b':
                        red = 0.5f;
                        break;
                    default:
                        break;
                }
            } else if (Event.type == SDL_QUIT) {
                running = 0;
            }
        }
        glViewport(-500, -500, WIN_WIDTH, WIN_HEIGHT);
        glClearColor(red, green, blue, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        display_square();
        SDL_GL_SwapWindow(window);
    }
    return 0;
}