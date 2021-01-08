#include "render.h"
#include "area_map.h"

int main()
{
  int SCREEN_WIDTH = 1500;
  int SCREEN_HEIGHT = 480;

  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0){ printf("Something's wrong with SDL: %s\n", SDL_GetError()); return 1;}

  window = init_window("Raycast Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  
  if( window == NULL )
  {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    SDL_Quit();
    return 1;
  }
  SDL_Renderer *renderer = init_renderer(window);
  if (renderer == NULL)
  {
    SDL_DestroyWindow(window);
    printf("Renderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  //Set the color of the background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  //Clear the window (set background color)
  SDL_RenderClear(renderer);
  
  char* test_map = load_map("test.txt", 10, 10);
  int* plr_pos = map_cam_pos(test_map, 10, 10);
  float* cam_pos = malloc(sizeof(float)*2);
  cam_pos[0] = (float)plr_pos[0];
  cam_pos[1] = (float)plr_pos[1];
  
  int* map_dims = malloc(sizeof(int)*2);
  map_dims[0] = 10;
  map_dims[1] = 10;

  unsigned char* img_buffer = load_texture("bricks.jpg",800, 470);

  for (int b = 0; b < 1000; b++)
  {
    int i = b;
    i = i%360;
  //float* distances = get_distances(-i, cam_pos, 30.0, SCREEN_WIDTH, 7.0, test_map, map_dims);
    /*if (b == 1)
    {
      for (int l = 0; l < SCREEN_WIDTH; l++)
      {
        printf("%.6f ", 1.0-distances[l]/10.0);
      }
    }*/
  int grad_dims[4] = {0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2};
    unsigned char start_color[3] = {0, 0, 0};
    unsigned char end_color[3] = {255, 255, 255};
    draw_vertical_gradient(renderer, grad_dims, start_color, end_color);
    //render_frame(renderer, distances, SCREEN_WIDTH, SCREEN_HEIGHT, 7.0);
    SDL_Delay(1);
  }
    //Display
  return 0;
}
