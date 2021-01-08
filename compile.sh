gcc -c main.c -lSDL2_image -g `sdl2-config --cflags --libs` -lm;
gcc -c area_map.c -lSDL2_image -g `sdl2-config --cflags --libs` -lm;
gcc -c render.c -lSDL2_image -g `sdl2-config --cflags --libs` -lm;
gcc render.o area_map.o main.o -lSDL2_image -g `sdl2-config --cflags --libs` -lm -o output;
