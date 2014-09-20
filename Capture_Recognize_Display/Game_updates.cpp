#include "StdAfx.h"
#include "Game_updates.h"

#include "image_helper.h"
#include "Cam_Helper.h"
#include "SDL_stuff.h"

#include <time.h>

#include "list"

extern SDL_Surface* screen;

extern SDL_Surface* bg_calibrate;
extern SDL_Surface* bg_capture_bg;
extern SDL_Surface* bg_capture_center;
extern SDL_Surface* bg_capture_full;

extern SDL_Surface* ques_mark;
extern SDL_Surface* place_any;
extern SDL_Surface* place_any_num;

extern SDL_Surface* train_engine;
extern SDL_Surface* train_cabin;
extern SDL_Surface* train_tracks;

extern SDL_Surface* feedback_correct;
extern SDL_Surface* feedback_wrong;

extern TTF_Font *font;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

extern SDL_Surface* image_files[MAX_CHAR_USED][6];
extern Mix_Chunk* sound_files[MAX_CHAR_USED][5];

extern Mix_Chunk* sound_train;

float get_frame_time()
{
	static clock_t update_time = 0;

	clock_t current_time = clock();
	float frame_time = (float)(current_time - update_time) / CLOCKS_PER_SEC;
	update_time = current_time;

	return frame_time;
}

void game_update_0()
{
	float frame_time = get_frame_time();

	clock_t current_time = clock();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	//apply_surface(x, y, bg_calibrate, screen);

	apply_surface(x, y, bg_capture_bg, screen);

	apply_surface(x+400, y, bg_capture_center, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "0: Start", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	int recog_char = get_recog_char();
	int recog_char_index = get_char_index(recog_char);

	if (recog_char_index >=0)
	{
		char s[16];

		itoa(recog_char, s, 16);

		//Render the text
		SDL_Surface *message = TTF_RenderText_Solid( font, s, textColor );

		//If there was an error in rendering the text
		//Show the message on the screen
		if( message != NULL ) apply_surface( x+200, y+200, message, screen );
	}
	else
	{
		SDL_Surface *img;
		{
			img = place_any_num;
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+400, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
}

void game_update_1()
{
	static clock_t char_update_time = 0;

	clock_t current_time = clock();

	float frame_time = get_frame_time();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	apply_surface(x, y, bg_capture_bg, screen);

	apply_surface(x+100, y, bg_capture_center, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "1: Drop any", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	int recog_char = get_recog_char();

	//if (recog_char == 2333) recog_char = 2350;
	//recog_char = 2350;

	int recog_char_index = get_char_index(recog_char);

	if (recog_char_index >=0)
	{
		char index[8];
		string path = itoa(recog_char, index, 10);

		clock_t elapsed_time = current_time - char_update_time;
		float elapsed_time_sec = ((float)elapsed_time)/CLOCKS_PER_SEC;

		if (elapsed_time_sec > 5)
		{
			char_update_time = current_time;

			//play char sound
			play_sound(sound_files[recog_char_index][0]);
		}

		SDL_Surface *img;

		//display fill image
		if (elapsed_time_sec < 4)
		{
			img = image_files[recog_char_index][0];
			if (img) apply_surface(x+700, y+(SCREEN_HEIGHT-img->h)/2, img, screen);
		}
	}
	else
	{
		char_update_time = 0;

		SDL_Surface *img;
		{
			img = place_any;
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+100, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
}

void game_update_2()
{
	static clock_t char_update_time = 0;

	clock_t current_time = clock();

	float frame_time = get_frame_time();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	apply_surface(x, y, bg_capture_bg, screen);

	apply_surface(x+400, y, bg_capture_center, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "2: Show and Tell (1)", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	int recog_char = get_recog_char();
	//int recog_char = 2350;
	int recog_char_index = get_char_index(recog_char);
	if (recog_char_index >= 0)
	{
		char index[8];
		string path = itoa(recog_char, index, 10);

		clock_t elapsed_time = current_time - char_update_time;
		float elapsed_time_sec = ((float)elapsed_time)/CLOCKS_PER_SEC;

		if (elapsed_time_sec > 5)
		{
			char_update_time = current_time;

			//play index sound
			play_sound(sound_files[recog_char_index][1]);
		}

		SDL_Surface *img = image_files[recog_char_index][0];
		if (img) apply_surface(x+0, y+(SCREEN_HEIGHT-img->h)/2, img, screen);

		//display one random image
		if (elapsed_time_sec < 4)
		{
			img = image_files[recog_char_index][1];
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+800, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
	else
	{
		char_update_time = 0;

		SDL_Surface *img;
		{
			img = place_any;
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+400, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
}

void game_update_3()
{
	static clock_t char_update_time = 0;
	const int max_play_index = 2;
	static int play_index = max_play_index-1; // max index

	float frame_time = get_frame_time();

	clock_t current_time = clock();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	apply_surface(x, y, bg_capture_bg, screen);

	apply_surface(x+400, y, bg_capture_center, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "3: Show and Tell (2)", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	int recog_char = get_recog_char();
	//int recog_char = 2350;
	int recog_char_index = get_char_index(recog_char);
	if (recog_char_index >= 0)
	{
		char index[8];
		string path = itoa(recog_char, index, 10);

		clock_t elapsed_time = current_time - char_update_time;
		float elapsed_time_sec = ((float)elapsed_time)/CLOCKS_PER_SEC;

		if (elapsed_time_sec > 5)
		{
			char_update_time = current_time;

			play_index = (play_index + 1)%max_play_index; // mod max index

			//play index sound
			play_sound(sound_files[recog_char_index][play_index+1]);
		}

		SDL_Surface *img = image_files[recog_char_index][0];
		if (img) apply_surface(x, y+(SCREEN_HEIGHT-img->h)/2, img, screen);

		//display one random image
		if (elapsed_time_sec < 4)
		{
			if (play_index == 0)
			{
				img = image_files[recog_char_index][1];
				SDL_Rect *rect = new SDL_Rect();

				static float animation_frame_time = 0;
				static int current_frame = 0;

				if (img)
				{
					animation_frame_time += frame_time;

					if (animation_frame_time > 0.2f)
					{
						animation_frame_time = 0;
						current_frame += 1;

						int frame_count = img->w / img->h;
						if (current_frame >= frame_count) current_frame = 0;
					}

					rect->x = img->h*current_frame; rect->y = 0;
					rect->h = rect->w = img->h;
					apply_surface(x+800, y+(SCREEN_HEIGHT/2)-img->h, img, screen, rect);
				}
			}

			if (play_index == 1)
			{
				img = image_files[recog_char_index][2];
				SDL_Rect *rect = new SDL_Rect();

				static float animation_frame_time = 0;
				static int current_frame = 0;

				if (img)
				{
					animation_frame_time += frame_time;

					if (animation_frame_time > 0.2f)
					{
						animation_frame_time = 0;
						current_frame += 1;

						int frame_count = img->w / img->h;
						if (current_frame >= frame_count) current_frame = 0;
					}

					rect->x = img->h*current_frame; rect->y = 0;
					rect->h = rect->w = img->h;
					apply_surface(x+800, y+SCREEN_HEIGHT/2, img, screen, rect);
				}
			}
		}
	}
	else
	{
		char_update_time = 0;
		play_index = max_play_index-1;

		SDL_Surface *img;
		{
			img = place_any;
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+400, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
}

void game_update_4()
{
	static clock_t char_update_time = 0;
	static clock_t disp_char_update_time = 0;

	float frame_time = get_frame_time();

	clock_t current_time = clock();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	apply_surface(x, y, bg_capture_bg, screen);

	apply_surface(x+700, y, bg_capture_center, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "4: Identify the Image", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	int recog_char = get_recog_char();

	//if (recog_char == 2333) recog_char = 2350;
	//recog_char = 2350;

	int recog_char_index = get_char_index(recog_char);

	static int selection_index_count = 4;
	//static int selection_index[] = {2325, 2327, 2330, 2340, 2344, 2346, 2348, 2350, 2354};
	static int selection_index[] = {2325, 2327, 2350, 2354};
	//srand (time(NULL));
	static int disp_char_index = get_char_index(selection_index[rand() % selection_index_count]);

	if (disp_char_index >=0)
	{
		char index[8];
		string path = itoa(recog_char, index, 10);

		clock_t elapsed_time = clock() - char_update_time;
		float elapsed_time_sec = ((float)elapsed_time)/CLOCKS_PER_SEC;

		if (elapsed_time_sec > 5)
		{
			char_update_time = current_time;

			if (recog_char_index == disp_char_index)
			{
				disp_char_update_time = 0;

				//play char sound
				play_sound(sound_files[disp_char_index][1]);
			}
		}

		SDL_Surface *img;

		if ( recog_char_index >= 0 )
		{
			img = recog_char_index == disp_char_index ? feedback_correct : feedback_wrong;
			if (img) apply_surface(x+600-(img->w/2), y+(SCREEN_HEIGHT-img->h)/2, img, screen);
		}

		if (recog_char_index < 0)
		{
			img = ques_mark;
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+700, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}

		//display fill image
		if (elapsed_time_sec < 4)
		{
			img = image_files[disp_char_index][1];
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+100, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
	else
	{
		char_update_time = 0;
	}

	if (recog_char == 0)
	{
		clock_t current_time = clock();
		clock_t elapsed_time = clock() - disp_char_update_time;
		float elapsed_time_sec = ((float)elapsed_time)/CLOCKS_PER_SEC;

		if (elapsed_time_sec > 15)
		{
			disp_char_update_time = clock();
			disp_char_index = get_char_index(selection_index[rand() % selection_index_count]);
		}
	}
}

void game_update_5()
{ 
	float frame_time = get_frame_time();

	clock_t current_time = clock();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	apply_surface(x, y, bg_capture_bg, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "5: Train", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	int recog_char = get_recog_char();
	int recog_char_index = get_char_index(recog_char);

	const int train_length = 5;
	static bool train_is_moving = TRUE;
	static int train_pos = SCREEN_WIDTH;

	if (train_is_moving)
	{
		static int prev_train_pos = 0;
		prev_train_pos = train_pos;
		train_pos -= frame_time*300;
		if (train_pos <= -train_length*SCREEN_WIDTH) train_pos = SCREEN_WIDTH;

		if (prev_train_pos%SCREEN_WIDTH ==0)
		{
			play_sound(sound_train);
		}

		if (prev_train_pos < SCREEN_WIDTH && train_pos/SCREEN_WIDTH < prev_train_pos/SCREEN_WIDTH)
		{
			train_pos = (train_pos / SCREEN_WIDTH) * SCREEN_WIDTH;
			train_is_moving = FALSE;
		}
	}

	apply_surface(x, y, train_tracks, screen);

	for (int i = 0; i < train_length; ++i)
	{
		int pos = train_pos+(i*SCREEN_WIDTH);
		if (-SCREEN_WIDTH < pos || pos < SCREEN_WIDTH)
		{
			apply_surface(x+pos, y, i == 0 ? train_engine : train_cabin, screen);
		}
	}

	apply_surface(x+700, y, bg_capture_center, screen);

	if (!train_is_moving) //ask a ques
	{
		static int selection_index_count = 4;
		//static int selection_index[] = {2325, 2327, 2330, 2340, 2344, 2346, 2348, 2350, 2354};
		static int selection_index[] = {2325, 2327, 2350, 2354};
		//srand (time(NULL));
		static int disp_char_index = get_char_index(selection_index[rand() % selection_index_count]);

		if (recog_char_index >= 0 && recog_char_index == disp_char_index)
		{
			static float correct_update_time = 0;

			if (correct_update_time == 0)
			{
				play_sound(sound_files[disp_char_index][1]);
			}

			correct_update_time += frame_time;
			if (correct_update_time > 3.0f)
			{
				correct_update_time = 0;
				train_is_moving = TRUE;

				disp_char_index = get_char_index(selection_index[rand() % selection_index_count]);
			}
		}

		SDL_Surface *img;

		if (!train_is_moving && recog_char_index >= 0)
		{
			img = recog_char_index == disp_char_index ? feedback_correct : feedback_wrong;
			if (img) apply_surface(x+600-(img->w/2), y+(SCREEN_HEIGHT-img->h)/2, img, screen);
		}

		if (!train_is_moving && recog_char_index < 0)
		{
			img = ques_mark;
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+700, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}

		if (!train_is_moving)
		{
			img = image_files[disp_char_index][1];
			SDL_Rect *rect = new SDL_Rect();

			static float animation_frame_time = 0;
			static int current_frame = 0;

			if (img)
			{
				animation_frame_time += frame_time;

				if (animation_frame_time > 0.2f)
				{
					animation_frame_time = 0;
					current_frame += 1;

					int frame_count = img->w / img->h;
					if (current_frame >= frame_count) current_frame = 0;
				}

				rect->x = img->h*current_frame; rect->y = 0;
				rect->h = rect->w = img->h;
				apply_surface(x+100, y+(SCREEN_HEIGHT-img->h)/2, img, screen, rect);
			}
		}
	}
}

void game_update_6()
{
	float frame_time = get_frame_time();

	clock_t current_time = clock();

	int x = (screen->w - SCREEN_WIDTH) / 2;
	int y = 0;

	apply_surface(x, y, bg_capture_bg, screen);

	//Render the text
	SDL_Surface *message = TTF_RenderText_Solid( font, "6: Sandbox (W.I.P.)", textColor );

	//If there was an error in rendering the text
	//Show the message on the screen
	if( message != NULL ) apply_surface( x+5, y+5, message, screen );

	struct stamp {
		int type; int x,y; float time_left;
	};
	static std::list<stamp> stamps;

	extern int num_recog_char;
	extern g_OCRCharInfo *g_Output;

	static float fadeout_time = 1.0f;

	for(int i=0; i<num_recog_char; i++)
	{
		stamp s;
		s.type = g_Output->g_UnicodeChars[i];
		s.x = (g_Output->boundingBoxes[i].minX + g_Output->boundingBoxes[i].maxX) / 2;
		s.y = (g_Output->boundingBoxes[i].minY + g_Output->boundingBoxes[i].maxY) / 2;
		s.time_left = fadeout_time;

		if (stamps.size() < 20)
		{
			bool can_add = TRUE;
			for (std::list<stamp>::iterator it = stamps.begin(), end = stamps.end(); it != end; ++it)
			{
				float d = pow((it->x-s.x)*(it->x-s.x) + (it->y-s.y)*(it->y-s.y), 0.5f);
				if (d < 150)
				{
					can_add = FALSE;
					break;
				}
			}

			if (can_add) stamps.push_back(s);
		}
	}

	SDL_Surface *img;

	for (std::list<stamp>::iterator it = stamps.begin(), end = stamps.end(); it != end; ++it)
	{
		it->time_left -= frame_time;

		int char_index = get_char_index(it->type);

		if (char_index >= 0)
		{
			img = image_files[char_index][0];

			//SDL_SetAlpha(img, SDL_SRCALPHA, (it->time_left / fadeout_time) * SDL_ALPHA_OPAQUE );
			apply_surface(x+it->x, y+it->y, img, screen);
			//SDL_BlitSurface(img, NULL, screen, NULL);
		}
	}

	while (!stamps.empty())
	{
		if (stamps.front().time_left > 0) break;
		stamps.pop_front();
	}
}