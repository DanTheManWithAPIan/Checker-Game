#include <cmath>
#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define PI 3.1415926535


bool move_piece(float mouse_x, float mouse_y, int p_turn) {

    if (p_turn == 0) {
        glColor3f(1.0f, 0.0f, 0.0f); // Circle Color
    } else {
        glColor3f(0.0f, 0.0f, 1.0f); // Circle Color
    }


    float triangle_amount = 20.0f; //# of triangles used to draw circle
    float radius = .1; // Radius of Circles
    float twice_pi = 2.0f * PI; // Double PI

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= triangle_amount; i++) {
        glVertex2f(
                mouse_x + (radius * std::cos(i * twice_pi / triangle_amount)),
                mouse_y + (radius * std::sin(i * twice_pi / triangle_amount)));
    }
    glEnd();
}


bool select_piece(float mouse_x, float mouse_y, float piece_locations[12][2]) {

    int player_array_length = sizeof(piece_locations) + 4;
    //std::cout << "Locations Array Length: " << player_array_length << std::endl;

        for (int j = 0; j < player_array_length; j++)
        {
            if (mouse_x < piece_locations[j][0] + 0.1f && mouse_y < piece_locations[j][1] + 0.1f
                && mouse_x > piece_locations[j][0] - 0.1f && mouse_y > piece_locations[j][1] - 0.1f)
            {
                std::cout << "Player Square Confirmed - Location (x, y): " << piece_locations[j][0] << " " << piece_locations[j][1] << std::endl;
                return true;
            }
        }
        return false;
}


void display_pieces(float piece_locations[12][2], int num_of_pieces, float red, float green, float blue) {

    glColor3f(red, green, blue); // Circle Color

    float triangle_amount = 20.0f; //# of triangles used to draw circle
    float radius = .1; // Radius of Circles
    float twice_pi = 2.0f * PI; // Double PI

    for (int loc = 0; loc < num_of_pieces; loc++) { // Loops to display circles
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
    glColor4f(0.25, 0.25, 0.25, 0.8); // Background color

    int square_counter = 1; // Square counter for each row
    int row_counter = 1; // Row counter

    for (float y = -1; y < 1; y += 0.250f) { // For loops for displaying checkerboard
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

                    square_counter += 1; // Add 1 to the row count for the row so we can progress through each row
                } else {
                square_counter += 1;
            }
        }
    }

    if (square_counter == 8) { // Part of 1st for loop
        square_counter = 1;
    }

        row_counter += 1; // Also part of 1st for loop
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

    int32_t running = 1; // On / Off boolean
    int32_t fullscreen = 0; // Fullscreen boolean
    int32_t p_mov = 0;

    float red = 0.0f; // Background Colors
    float green = 0.0f;
    float blue = 0.0f;

    int p1_piece_count = 12; // Player piece counts
    int p2_piece_count = 12;

    int p_turn = 0; // 0 is red player, 1 is blue player


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
                                 {0.625f, -0.375f}
    };

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
                                 {0.875f, 0.375f}
    };

    int p1_array_length = sizeof(p1_locations) / 8; // Length of player 1's array
    int p2_array_length = sizeof(p2_locations) / 8; // Length of player 1's array

    int orig_index = 0;
    float orig_x = 0;
    float orig_y = 0;


    static float valid_squares[32][4] = {}; // Position Matrix for storing valid squares players can move too.
    int num_of_sq = sizeof(valid_squares) / 16; // Length of black square array
    std::cout << num_of_sq;

    int square_counter = 1; // Square counter for each row
    int row_counter = 1; // Row counter
    int index_counter = 0;

    for (float y = -1; y < 1; y += 0.250f) { // For loops for finding black squares top right and bottom left coordinates
        for (float x = -1; x < 1; x += 0.250f) { // So I can test if the mouse coordinates are inside the black square coordinates then we can initiate our picking up of the piece.
            if (row_counter % 2 == 0) {
                if (square_counter % 2 == 0) {
                    valid_squares[index_counter][0] = x + .250f; // Top Right x
                    valid_squares[index_counter][1] = y + .250f; // Top Right y
                    valid_squares[index_counter][2] = x; // Bottom Left x
                    valid_squares[index_counter][3] = y; // Bottom Left y
                    index_counter += 1;
                    square_counter += 1;
                } else {
                    square_counter += 1;
                }
            } else {
                if (square_counter % 2 == 1) {
                    valid_squares[index_counter][0] = x + .250f; // Top Right x
                    valid_squares[index_counter][1] = y + .250f; // Top Right y
                    valid_squares[index_counter][2] = x; // Bottom Left x
                    valid_squares[index_counter][3] = y; // Bottom Left y
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






while (running) {
    int mouse_x, mouse_y; // Mouse coordinate variables
    SDL_GetMouseState(&mouse_x, &mouse_y); // Getting the coordinates of the mouse (x, y)

    float x = float(mouse_x) * 2 / 1000 - 1; // Formula for SDL to OpenGL coordinate plane
    float y = float(-mouse_y) * 2 / 1000 + 1;

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
            // SDL - (0, 0) is top right and (1000, 1000) is bottom left
            // OpenGL - (-1, -1) is bottom left and (1, 1) is top right

            std::cout << "Mouse x: " << x << std::endl;
            std::cout << "Mouse y: " << y << std::endl;

            if (select_piece(x, y, p1_locations) && p_turn == 0) {
                p_mov = 1;
                for (int i = 0; i < p1_array_length; i++) {
                    if (x < p1_locations[i][0] + 0.1f && y < p1_locations[i][1] + 0.1f
                        && x > p1_locations[i][0] - 0.1f && y > p1_locations[i][1] - 0.1f) {
                        orig_x = p1_locations[i][0];
                        orig_y = p1_locations[i][1];
                        orig_index = i;
                        p1_locations[i][0] = -10;
                        p1_locations[i][1] = -10;
                    }
                }
            }
            if (select_piece(x, y, p1_locations) && p_turn == 1) {
                p_mov = 1;
                for (int i = 0; i < p2_array_length; i++) {
                    if (x < p2_locations[i][0] + 0.1f && y < p2_locations[i][1] + 0.1f
                        && x > p2_locations[i][0] - 0.1f && y > p2_locations[i][1] - 0.1f) {
                        orig_x = p2_locations[i][0];
                        orig_y = p2_locations[i][1];
                        orig_index = i;
                        p2_locations[i][0] = -10;
                        p2_locations[i][1] = -10;
                    }
                }
            }
        }

        if (Event.type == SDL_MOUSEBUTTONUP) {
            // valid_squares is the matrix with all the square locations
            // x and y are the mouse coordinates
            p_mov = 0;

            if (p_turn == 0) {
                for (int i = 0; i < num_of_sq; i++) {
                    if (x < valid_squares[i][0] && y < valid_squares[i][1]
                        && x > valid_squares[i][2] && y > valid_squares[i][3]) {
                        std::cout << valid_squares[i][0] << " " << valid_squares[i][1] << " "
                                  << valid_squares[i][2] << " " << valid_squares[i][3] << std::endl;
                        p1_locations[orig_index][0] = valid_squares[i][0] - .125f;
                        p1_locations[orig_index][1] = valid_squares[i][1] - .125f;
                    }
                }
            p_turn = 1;
            } else {
                for (int i = 0; i < num_of_sq; i++) {
                    if (x < valid_squares[i][0] && y < valid_squares[i][1]
                        && x > valid_squares[i][2] && y > valid_squares[i][3]) {
                        std::cout << valid_squares[i][0] << " " << valid_squares[i][1] << " "
                                  << valid_squares[i][2] << " " << valid_squares[i][3] << std::endl;
                        p2_locations[orig_index][0] = valid_squares[i][0] - .125f;
                        p2_locations[orig_index][1] = valid_squares[i][1] - .125f;
                        p_turn = 0;
                    }
                }
            }
        }
    }
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT); // OpenGL Viewport- (-1, -1) is bottom left, (1, 1) is top right
        glClearColor(red, green, blue, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        display_checker_board(); // Displaying checkerboard

        display_pieces(p1_locations, p1_piece_count, 1.0f, 0.0f, 0.0f); // Red player

        display_pieces(p2_locations, p2_piece_count, .0f, 0.0f, 1.0f); // Blue player

        if (p_mov) {
            move_piece(x, y, p_turn);
        }
        SDL_GL_SwapWindow(window);
    }
    return 0;
}

