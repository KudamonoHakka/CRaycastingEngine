#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void draw_rectangle(SDL_Renderer* ren, int dims[4],unsigned char colors[4]);

void draw_vertical_gradient(SDL_Renderer* ren, int pos[4], unsigned char start_colors[3], unsigned char end_colors[3]);


void render_frame(SDL_Renderer* ren, float* distances, int res_width, int res_height, float max_distance);

float* get_distances(float cam_deg, float* cam_pos, float fov, int res, float max_distance, char* map_area, int* map_dims);
SDL_Window* init_window(const char* name, int width, int height);
SDL_Renderer* init_renderer(SDL_Window* win);
