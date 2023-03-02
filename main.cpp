#include <cmath>
#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define PI 3.1415926535


bool is_cursor_on_piece(int mouse_x, int mouse_y) {
    static int valid_squares[32][2][2] = {}; // Position Matrix for storing valid squares players can move too.

    int row_counter = 1; // Row Counter
    int square_counter = 1; // Square counter for each row
    int index_counter = 0; // Index counter for position matrix

    // For loops for getting the locations of valid squares players can move to
    for (int y = 0; y < 1000; y += 125) {
        for (int x = 0; x < 1000; x += 125) {
            if (row_counter % 2 == 0) {
                if (square_counter % 2 == 1) {
                    //std::cout << "Odd Row" << std::endl;
                    //std::cout << "Top Left: " << x << " " << y << " Bottom Left: "<< x << " " << y + 125
                    //<< " Bottom Right: " << x + 125 << " " << y + 125 << " Top Right: " << x + 125 << " " << y << std::endl;
                    valid_squares[index_counter][0][0] = x; // Bottom Left x
                    valid_squares[index_counter][0][1] = y + 125; // Bottom Left y
                    valid_squares[index_counter][1][0] = x + 125; // Top Right x
                    valid_squares[index_counter][1][1] = y; // Top Right y
                    index_counter += 1;
                    square_counter += 1;
                } else {
                    square_counter += 1;
                }
            } else {
                if (square_counter % 2 == 0) {
                    //std::cout << "Even Row" << std::endl;
                    //std::cout << "Top Left: " << x << " " << y << " Bottom Left: "<< x << " " << y + 125
                    //<< " Bottom Right: " << x + 125 << " " << y + 125 << " Top Right: " << x + 125 << " " << y << std::endl;
                    valid_squares[index_counter][0][0] = x; // Bottom Left x
                    valid_squares[index_counter][0][1] = y + 125; // Bottom Left y
                    valid_squares[index_counter][1][0] = x + 125; // Top Right x
                    valid_squares[index_counter][1][1] = y; // Top Right y
                    index_counter += 1;
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
    for (int i = 0; i < sizeof(valid_squares); i++) {
        if (mouse_x > valid_squares[i][0][0] && mouse_x < valid_squares[i][1][0]
         && mouse_y > valid_squares[i][1][1] && mouse_y < valid_squares[i][0][1]) {
            return true;
        } else {
            return false;
        }
    }
}

bool is_piece_on_square(float p_locations[12][2]) {

    static float valid_squares[32][2][2] = {}; // Position Matrix for storing valid squares players can move too.

    int square_counter = 1; // Square counter for each row
    int row_counter = 1; // Row counter
    int index_counter = 0;
    // For loops for displaying checkerboard
    for (float y = -1; y < 1; y += 0.250f) {
        for (float x = -1; x < 1; x += 0.250f) {
            if (row_counter % 2 == 0) {
                if (square_counter % 2 == 0) {
                    valid_squares[index_counter][0][0] = x + .250f; // Top Right x
                    valid_squares[index_counter][0][1] = y + .250f; // Top Right y
                    valid_squares[index_counter][1][0] = x; // Bottom Left x
                    valid_squares[index_counter][1][1] = y; // Bottom Left y
                    index_counter += 1;
                    square_counter += 1;
                } else {
                    square_counter += 1;
                }
            } else {
                if (square_counter % 2 == 1) {
                    valid_squares[index_counter][0][0] = x + .250f; // Top Right x
                    valid_squares[index_counter][0][1] = y + .250f; // Top Right y
                    valid_squares[index_counter][1][0] = x; // Bottom Left x
                    valid_squares[index_counter][1][1] = y; // Bottom Left y
                    index_counter += 1;
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
    for (int i = 0; i <= 64; i++) {
        std::cout << valid_squares[i][0][0] << " " << valid_squares[i][0][1] << std::endl;
        //for (int j = 0; j <= 12; j++) {
            //if (p_locations[j][0] < valid_squares[i][0][0] && p_locations[j][0] > valid_squares[i][1][0]
                //&& p_locations[j][1] > valid_squares[i][1][1] && p_locations[j][1] < valid_squares[i][0][1]) {
                //return true;
            //} else {
                //return false;
            //}
        //}
    }
}


bool is_cursor_on_square(float mouse_x, float mouse_y, float piece_locations[12][2]) {

    static float valid_squares[32][2][2] = {}; // Position Matrix for storing valid squares players can move too.

    int square_counter = 1; // Square counter for each row
    int row_counter = 1; // Row counter
    int index_counter = 0;
    // For loops for displaying checkerboard
    for (float y = -1; y < 1; y += 0.250f) {
        for (float x = -1; x < 1; x += 0.250f) {
            if (row_counter % 2 == 0) {
                if (square_counter % 2 == 0) {
                    valid_squares[index_counter][0][0] = x + .250f; // Top Right x
                    valid_squares[index_counter][0][1] = y + .250f; // Top Right y
                    valid_squares[index_counter][1][0] = x; // Bottom Left x
                    valid_squares[index_counter][1][1] = y; // Bottom Left y
                    index_counter += 1;
                    square_counter += 1;
                } else {
                    square_counter += 1;
                }
            } else {
                if (square_counter % 2 == 1) {
                    valid_squares[index_counter][0][0] = x + .250f; // Top Right x
                    valid_squares[index_counter][0][1] = y + .250f; // Top Right y
                    valid_squares[index_counter][1][0] = x; // Bottom Left x
                    valid_squares[index_counter][1][1] = y; // Bottom Left y
                    index_counter += 1;
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
    for (int i = 0; i <= 32; i++) {
        //std::cout << valid_squares[i][0][0] << " " << valid_squares[i][0][1] << std::endl;
        //if (mouse_x < valid_squares[i][0][0] && mouse_x > valid_squares[i][1][0]
           //&& mouse_y > valid_squares[i][1][1] && mouse_y < valid_squares[i][0][1]) {
            //return true;
        //} else {
            //return false;
        //}
    }
}




void display_pieces(float piece_locations[12][2], int num_of_pieces, float red, float green, float blue) {
    int triangle_amount = 20; //# of triangles used to draw circle
    float radius = .1; // Radius of Circles
    float twice_pi = 2.0f * PI; // Double PI
    glColor3f(red, green, blue); // Circle Color
    // Loops to display circles
    for (int loc = 0; loc < num_of_pieces; loc++) {
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= triangle_amount; i++) {
            glVertex2f(
                    piece_locations[loc][0] + (radius * std::cos(i * twice_pi / triangle_amount)),
                    piece_locations[loc][1] + (radius * std::sin(i * twice_pi / triangle_amount))
                    );
        }
        glEnd();
    }
}


void display_checker_board() {
    glClear(GL_COLOR_BUFFER_BIT); // Clearing the Window
    glColor3f(1.0, 1.0, 1.0); // Background color
    int square_counter = 1; // Square counter for each row
    int row_counter = 1; // Row counter
    // For loops for displaying checkerboard
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



// Functions above main below



int main (int ArgCount, char **Args)
{
    uint32_t windowFlags = SDL_WINDOW_OPENGL;
    SDL_Window* window =
            SDL_CreateWindow(
                    "OpenGL Test",
                    200,
                    100,  // Creating a window using SDL
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

    int p1_piece_count = 12; // Player piece counts
    int p2_piece_count = 12;

    float p1_locations[12][2] = {{-0.875f, -0.875f}, // Player 1 locations (x, y)
                                 {-0.375f, -0.875f},
                                 {0.125f, -0.875f},
                                 {0.625f, -0.875f},
                                 {-0.625f, -0.625f},
                                 {-0.125f, -0.625f},
                                 {0.375f, -0.625f},
                                 {0.875f, -0.625f},
                                 {-0.875f, -0.375f},
                                 {-0.375f, -0.375f},
                                 {0.125f, -0.375f},
                                 {0.625f, -0.375f}};

    float p2_locations[12][2] = {{-0.625f, 0.875f}, // Player 2 locations (x, y)
                                 {-0.125f, 0.875f},
                                 {0.375f, 0.875f},
                                 {0.875f, 0.875f},
                                 {-0.875f, 0.625f},
                                 {-0.375f, 0.625f},
                                 {0.125f, 0.625f},
                                 {0.625f, 0.625f},
                                 {-0.625f, 0.375f},
                                 {-0.125f, 0.375f},
                                 {0.375f, 0.375f},
                                 {0.875f, 0.375f}};

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
                int mouse_x, mouse_y; // Mouse coordinate variables
                SDL_GetMouseState(&mouse_x, &mouse_y); // Getting the coordinates of the mouse (x, y)
                float x = float(mouse_x) * 2 / 1000 - 1; // Formula for coordinate plane
                float y = float(-mouse_y) * 2 / 1000 + 1;
                is_cursor_on_square(x, y, p1_locations);
                is_piece_on_square(p1_locations);
            }
        }
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT); // OpenGL Viewport- (-1, -1) is bottom left, (1, 1) is top right
        glClearColor(red, green, blue, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        display_checker_board(); // Displaying checkerboard

        display_pieces(p1_locations, p1_piece_count, 1.0f, 0.0f, 0.0f); // Red player

        display_pieces(p2_locations, p2_piece_count, .0f, 0.0f, 1.0f); // Blue player

        SDL_GL_SwapWindow(window);
    }
    return 0;
}