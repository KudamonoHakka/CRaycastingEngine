#include "render.h"
#include <math.h>

SDL_Window* init_window(const char* name, int width, int height)
{
  SDL_Window* win = SDL_CreateWindow( name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
  return win;
}

SDL_Renderer* init_renderer(SDL_Window* win)
{
  SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  return rend;
}

void draw_rectangle(SDL_Renderer* ren, int dims[4],unsigned char colors[4])
{
  SDL_Rect rect;
  rect.x = dims[0];
  rect.y = dims[1];
  rect.w = dims[2];
  rect.h = dims[3];

  SDL_SetRenderDrawColor(ren, colors[0], colors[1], colors[2], colors[3]);

  SDL_RenderFillRect(ren, &rect);
}


void draw_vertical_gradient(SDL_Renderer* ren, int pos[4], unsigned char start_colors[3], unsigned char end_colors[3])
{
  for (int i = 0; i < pos[3]-pos[1]; i++)
  {
    int rect_dims[4] = {pos[0], pos[1]+i, pos[2]-pos[0], 1};

    unsigned char color1 = (unsigned char)start_colors[0] + (end_colors[0]-start_colors[0])*((float)i/(pos[3]-pos[1]));

    unsigned char color2 = (unsigned char)start_colors[1] + (end_colors[1]-start_colors[1])*((float)i/(pos[3]-pos[1]));

    unsigned char color3 = (unsigned char)start_colors[2] + (end_colors[2]-start_colors[2])*((float)i/(pos[3]-pos[1]));

    unsigned char rect_colors[4] = {color1, color2, color3, 255};
    draw_rectangle(ren, rect_dims, rect_colors);
  }
}

void render_frame(SDL_Renderer* ren, float* distances, int res_width, int res_height, float max_distance)
{

 SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

  //Clear the window (set background color)
  SDL_RenderClear(ren);

int grad_dims[4] = {0, res_height/2, res_width, res_height};
    unsigned char start_color[3] = {0, 0, 0};
    unsigned char end_color[3] = {255, 255, 255};
    draw_vertical_gradient(ren, grad_dims, start_color, end_color);

  for (int i = 0; i < res_width; i++)
  {
    unsigned char rect_colors[4] = {100, 100, 100, 255};
    int rect_dims[4] = {i, (res_height - ((float)res_height*(1.0-distances[i]/max_distance)))/2, 1, (float)res_height*(1.0-distances[i]/max_distance)};

    draw_rectangle(ren, rect_dims, rect_colors);
  }
  SDL_RenderPresent(ren);
}



float get_ray_distance(float deg, float* pos, float increment, float max_distance, char* map_area, int* map_dims)
{
  float return_distance = 0.0;
  int steps = 0;
  while (steps < max_distance/increment && return_distance < max_distance && map_area[(int)((/*height*/((int)(sin(deg*3.141592/180)*return_distance+pos[1]))*map_dims[0])+(/*width*/(int)(cos(deg*3.141592/180)*return_distance+pos[0])))] != '#')
  {
    return_distance += increment;
    steps++;
  }
  return return_distance;
}

float* get_distances(float cam_deg, float* cam_pos, float fov, int res, float max_distance, char* map_area, int* map_dims)
{
  float* return_distances = malloc(sizeof(float)*res);
  for (int i = 0; i < res; i++)
  {
    return_distances[i] = get_ray_distance((cam_deg-fov/2)+(i/(float)res)*fov, cam_pos, 0.01, max_distance, map_area, map_dims);
  }
  return return_distances;

}
