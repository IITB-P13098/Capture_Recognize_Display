// Capture_Recognize_Display.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cam_Helper.h"
#include "image_helper.h"
#include "Game_updates.h"
#include "SDL_stuff.h"
#include "devanagari_keyboard.h"

#include "Window.h"

//The event structure
SDL_Event event;

extern SDL_Surface* screen;

int game_type = 0;
int capture_type = 0;
void update()
{
	//If a key was pressed
	if( event.type == SDL_KEYDOWN )
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_0: game_type = 0; break;
		case SDLK_1: game_type = 1; break;
		case SDLK_2: game_type = 2; break;
		case SDLK_3: game_type = 3; break;
		case SDLK_4: game_type = 4; break;
		case SDLK_5: game_type = 5; break;
		case SDLK_6: game_type = 6; break;
		}
	}

	switch (game_type)
	{
 	case 0: game_update_0(); capture_type = CAPTURE_CENTER; break;
	case 1: game_update_1(); capture_type = CAPTURE_LEFT; break;
	case 2: game_update_2(); capture_type = CAPTURE_CENTER; break;
	case 3: game_update_3(); capture_type = CAPTURE_CENTER; break;
	case 4: game_update_4(); capture_type = CAPTURE_RIGHT; break;
	case 5: game_update_5(); capture_type = CAPTURE_RIGHT; break;
	case 6: game_update_6(); capture_type = CAPTURE_FULL; break;
	}
}

int chars_used[] = {2309, 2310, 2311, 2312, 2313,
					2314, 2318, 2319, 2323, 2324,
					2325, 2326, 2327, 2328, 2329,
					2330, 2331, 2332, 2333, 2334,
					2335, 2336, 2337, 2338, 2339,
					2340, 2341, 2342, 2343, 2344,
					2346, 2347, 2348, 2349, 2350,
					2351, 2352, 2354, 2357, 2358,
					2359, 2360, 2361};
int* get_char_used() { return chars_used; }

std::map<int,int> char_map;
void char_map_init()
{
	for (int i = 0; i < MAX_CHAR_USED; i++)
		char_map[chars_used[i]] = i;
}

int get_char_index(int c)
{
	map<int,int>::iterator it = char_map.find(c); 
	if (it != char_map.end())
	{
		return it->second;
	}
	return -1;
}

void manupulate_recog_char()
{
	extern int recog_char;

	//If a key was pressed
	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_BACKSPACE: recog_char = 0; break;
		default: recog_char = devanagari_key_pressed();
		}
	}
}

int _tmain(int argc, char* argv[])
{
	srand (time(NULL));

	init_cam();

	char_map_init();

	//Quit flag
	bool quit = false;

	//Initialize
	if (!init_sdl_stuffs()) 
	{
		return 0;
	}

	//Create a window
	Window myWindow;

	//If the window failed
	if( myWindow.error() == true )
	{
		return 1;    
	}

	//Load the files
	if (!load_files())
	{
		return 0;
	}

	//While the user hasn't quit
	while( !quit )
	{
		//While there's events to handle
		while( SDL_PollEvent( &event ) )
		{
			//Handle window events
			myWindow.handle_events();

			//If the user has Xed out the window
			if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
		}

		//If the window failed
		if( myWindow.error() == true )
		{
			return 1;    
		}

		//Fill the screen white
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 256, 256, 256 ) );

		manupulate_recog_char();
		update();
		update_cam(capture_type);

		//Update the screen
		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}
	}

	//Free surfaces, fonts and sounds
	//then quit SDL_mixer, SDL_ttf and SDL
	clean_up();

	exit_cam();

	return 0;
}
