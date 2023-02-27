#include <cmath>
#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <cmath>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define PI 3.1415926535

class Player_pieces {
    float piece_locations;
    int num_of_pieces;

    public:
        void display_red_pieces(GLfloat x, GLfloat y, GLfloat radius){
            int triangle_amount = 20; //# of triangles used to draw circle

            //GLfloat radius = 0.8f; //radius
            float twice_pi = 2.0f * PI;

            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y); // center of circle
            for(int i = 0; i <= triangle_amount; i++) {
                glVertex2f(
                    x + (radius * std::cos(i *  twice_pi / triangle_amount)),
                    y + (radius * std::sin(i * twice_pi / triangle_amount))
                );
            }
            glEnd();
        };
};


void display_checker_board() {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    int square_counter = 1;
    int row_counter = 1;

    for (float y = -1; y < 1; y += 0.250f) {
        for (float x = -1; x < 1; x += 0.250f) {
            if (row_counter % 2 == 0) {
                if (square_counter % 2 == 1) {
                    glBegin(GL_POLYGON);
                    glVertex2f(x, y); // Bottom Left
                    glVertex2f(x, y + 0.250f); // Top left
                    glVertex2f(x + 0.250f, y + 0.250f); // Top Right
                    glVertex2f(x + 0.250f, y); // Bottom Right

                    glEnd();
                    glFlush();

                    square_counter += 1;
                } else {
                    square_counter += 1;
                }
            } else {
                if (square_counter % 2 == 0) {
                    glBegin(GL_POLYGON);
                    glVertex2f(x, y); // Bottom Left
                    glVertex2f(x, y + 0.250f); // Top left
                    glVertex2f(x + 0.250f, y + 0.250f); // Top Right
                    glVertex2f(x + 0.250f, y); // Bottom Right

                    glEnd();
                    glFlush();

                    square_counter += 1;
            } else {
                square_counter += 1;
                }
            }
        }
    if (square_counter == 8) {
        square_counter = 1;
    }
        row_counter += 1;
    }
}


int main (int ArgCount, char **Args)
{
    Player_pieces p1{};
    Player_pieces p2{};
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
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;

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
        if (Event.type == SDL_MOUSEBUTTONDOWN) {

        }
        }
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
        glClearColor(red, green, blue, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        display_checker_board();
        p1.display_red_pieces(-0.875, -0.875, -.1);
        SDL_GL_SwapWindow(window);
    }
    return 0;
}