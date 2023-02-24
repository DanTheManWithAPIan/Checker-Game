#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

class rectangle {
    int width = 50;
    int height = 50;
    int x = 500;
    int y = 500;
};




int main (int ArgCount, char **Args)
{
    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;
    SDL_Window*window =
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
                    case SDLK_UP:

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
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);

    }
    return 0;
}