#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

void display_square() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
            glVertex2f(300, 300); // Top Left
            glVertex2f(400, 300); // Top Right
            glVertex2f(400, 400); // Bottom Right
            glVertex2f(300,  400); // Bottom Left
    glEnd();
}

int main (int ArgCount, char **Args)
{
    class rectangle {
    public:
        int x = 500;
        int y = 500;
        int width = 50;
        int height = 50;
    };

    rectangle rect;

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
    float red = 0.5f;
    float green = 1.0f;
    float blue = 0.0f;
    while (running)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case 'f':
                        fullscreen = !fullscreen;
                        if (fullscreen)
                        {
                            SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        }
                        else
                        {
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
            }
            else if (Event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
        glClearColor(red, green, blue, 0.f);
        display_square();
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
    return 0;
}