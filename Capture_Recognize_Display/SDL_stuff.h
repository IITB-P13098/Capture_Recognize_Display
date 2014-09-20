#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>

bool init_sdl_stuffs();

bool load_files();

void clean_up();

SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

void play_sound(Mix_Chunk *sound, bool loop = 0);