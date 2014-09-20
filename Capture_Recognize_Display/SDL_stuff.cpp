#include "StdAfx.h"
#include "SDL_stuff.h"

SDL_Surface *screen = NULL;

SDL_Surface *bg_calibrate = NULL;
SDL_Surface *bg_capture_bg = NULL;
SDL_Surface *bg_capture_center = NULL;
SDL_Surface *bg_capture_full = NULL;

SDL_Surface *ques_mark = NULL;
SDL_Surface *place_any = NULL;
SDL_Surface *place_any_num = NULL;

SDL_Surface *train_engine = NULL;
SDL_Surface *train_cabin = NULL;
SDL_Surface *train_tracks = NULL;

SDL_Surface *feedback_correct = NULL;
SDL_Surface *feedback_wrong = NULL;

//The font
TTF_Font *font = NULL;

//The images that will be used
SDL_Surface *image_files[MAX_CHAR_USED][6];

//The sound effects that will be used
Mix_Chunk *sound_files[MAX_CHAR_USED][5];

Mix_Chunk *sound_train = NULL;

SDL_Surface *load_image( std::string filename )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( filename.c_str() );

	return loadedImage;

// 	//If the image loaded
// 	if( loadedImage != NULL )
// 	{
// 		//Create an optimized surface
// 		optimizedImage = SDL_DisplayFormat( loadedImage );
// 
// 		//Free the old surface
// 		SDL_FreeSurface( loadedImage );
// 
// 		//If the surface was optimized
// 		if( optimizedImage != NULL )
// 		{
// 			//Color key surface
// 			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
// 		}
// 	}
// 
// 	//Return the optimized surface
// 	return optimizedImage;
}

bool init_sdl_stuffs()
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	//Set up the screen
	//screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		return false;
	}

	//If there was an error in setting up the screen
	//if( screen == NULL )
	//{
	//	return false;
	//}

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( "OCR Toy", NULL );

	return true;
}

bool load_files()
{
	bg_calibrate = load_image( "images/calibrate.png" );
	bg_capture_bg = load_image( "images/capture bg.png" );
	bg_capture_center = load_image( "images/capture center.png" );
	bg_capture_full = load_image( "images/capture full.png" );

	ques_mark = load_image( "images/ques mark.png" );
	place_any = load_image( "images/place_any.png" );
	place_any_num = load_image( "images/place_any_num.png" );

	train_engine = load_image( "images/train/engine.png" );
	train_cabin = load_image( "images/train/cabin.png" );
	train_tracks = load_image( "images/train/tracks.png" );

	feedback_correct = load_image( "images/feedback_correct.png" );
	feedback_wrong = load_image( "images/feedback_wrong.png" );

	int *chars_used = get_char_used();
	for (int i = 0; i < MAX_CHAR_USED; i++)
	{
		char index[8];
		string str_index = itoa(chars_used[i], index, 10);

		sound_files[i][0] = Mix_LoadWAV( string("sounds/char/" + str_index +   ".wav").c_str() );
		sound_files[i][1] = Mix_LoadWAV( string("sounds/char/" + str_index + "-a.wav").c_str() );
		sound_files[i][2] = Mix_LoadWAV( string("sounds/char/" + str_index + "-b.wav").c_str() );
		sound_files[i][3] = Mix_LoadWAV( string("sounds/char/" + str_index +   ".wav").c_str() );
		sound_files[i][4] = Mix_LoadWAV( string("sounds/char/" + str_index +   ".wav").c_str() );

// 		sound_files[i][0] = Mix_LoadWAV( string("sounds/char/" + str_index +   ".wav").c_str() );
// 		sound_files[i][1] = Mix_LoadWAV( string("sounds/char/" + str_index + "-a.wav").c_str() );
// 		sound_files[i][2] = Mix_LoadWAV( string("sounds/char/" + str_index + "-b.wav").c_str() );
// 		sound_files[i][3] = Mix_LoadWAV( string("sounds/char/" + str_index + "-c.wav").c_str() );
// 		sound_files[i][4] = Mix_LoadWAV( string("sounds/char/" + str_index + "-d.wav").c_str() );

		//If there was a problem loading the sound effects
		if( !sound_files[i][0] || !sound_files[i][1] || !sound_files[i][2] 
			|| !sound_files[i][3] || !sound_files[i][4] )
		{
			//return false;
		}

		sound_train = Mix_LoadWAV( "sounds/train.wav" );

		image_files[i][0] = load_image( string("images/char/" + str_index +      ".png").c_str() );
		image_files[i][1] = load_image( string("images/char/" + str_index +    "-a.png").c_str() );
		image_files[i][2] = load_image( string("images/char/" + str_index +    "-b.png").c_str() );
		image_files[i][3] = load_image( string("images/char/" + str_index +      ".png").c_str() );
		image_files[i][4] = load_image( string("images/char/" + str_index +      ".png").c_str() );
		image_files[i][5] = load_image( string("images/char/" + str_index + "-fill.png").c_str() );

// 		image_files[i][0] = load_image( string("images/char/" + str_index +      ".png").c_str() );
// 		image_files[i][1] = load_image( string("images/char/" + str_index +    "-a.png").c_str() );
// 		image_files[i][2] = load_image( string("images/char/" + str_index +    "-b.png").c_str() );
// 		image_files[i][3] = load_image( string("images/char/" + str_index +    "-c.png").c_str() );
// 		image_files[i][4] = load_image( string("images/char/" + str_index +    "-d.png").c_str() );
// 		image_files[i][5] = load_image( string("images/char/" + str_index + "-fill.png").c_str() );

		if( !image_files[i][0] || !image_files[i][1] || !image_files[i][2]
			|| !image_files[i][3] || !image_files[i][4] || !image_files[i][5] )
		{
			//return false;
		}
	}

	//Open the font
	font = TTF_OpenFont( "fonts/calibri.ttf", 25 );

	//If everything loaded fine
	return true;
}

void clean_up()
{
	for (int i = 0; i < MAX_CHAR_USED; i++)
	{
		for (int j = 0; j < 5; j++)
			Mix_FreeChunk(sound_files[i][j]);

		for (int j = 0; j < 6; j++)
			SDL_FreeSurface(image_files[i][j]);
	}

	Mix_FreeChunk(sound_train);

	SDL_FreeSurface(bg_calibrate);
	SDL_FreeSurface(bg_capture_bg);
	SDL_FreeSurface(bg_capture_center);
	SDL_FreeSurface(bg_capture_full);

	SDL_FreeSurface(ques_mark);
	SDL_FreeSurface(place_any);
	SDL_FreeSurface(place_any_num);

	SDL_FreeSurface(train_engine);
	SDL_FreeSurface(train_cabin);
	SDL_FreeSurface(train_tracks);

	SDL_FreeSurface(feedback_correct);
	SDL_FreeSurface(feedback_wrong);

	//Close the font
	TTF_CloseFont( font );

	//Quit SDL_ttf
	TTF_Quit();

	//Quit SDL_mixer
	Mix_CloseAudio();

	//Quit SDL
	SDL_Quit();
}

void play_sound(Mix_Chunk *sound, bool loop)
{
	if (!sound) return;

	Mix_PlayChannel( -1, sound, loop );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
	if (!source || !destination) return;

	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface( source, clip, destination, &offset );
}
