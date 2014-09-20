#include "StdAfx.h"
#include "devanagari_keyboard.h"

int devanagari_key_pressed()
{
	extern SDL_Event event;

	//If a key was pressed
	if ( event.type == SDL_KEYDOWN )
	{
		bool shift_pressed = event.key.keysym.mod & KMOD_RSHIFT || event.key.keysym.mod & KMOD_LSHIFT;

		switch ( event.key.keysym.sym )
		{
		case SDLK_d: if (shift_pressed) return 2309; return 0;
		case SDLK_e: if (shift_pressed) return 2310; return 0;
		case SDLK_f: if (shift_pressed)	return 2311; return 0;
		case SDLK_r: if (shift_pressed)	return 2312; return 0;
		case SDLK_g: if (shift_pressed) return 2313; return 0;
		case SDLK_t: if (shift_pressed) return 2314; return 0;
		case SDLK_s: if (shift_pressed) return 2318; return 0;
		case SDLK_w: if (shift_pressed) return 2319; return 0;
		case SDLK_a: if (shift_pressed) return 2323; return 0;
		case SDLK_q: if (shift_pressed) return 2324; return 0;
		case SDLK_k: if (shift_pressed) return 2326; return 2325;
		case SDLK_i: if (shift_pressed) return 2328; return 2327;
		case SDLK_u: if (shift_pressed) return 2329; return 2361;
		case SDLK_SEMICOLON: if (shift_pressed) return 2331; return 2330;
		case SDLK_p: if (shift_pressed) return 2333; return 2332;
		case SDLK_RIGHTBRACKET: if (shift_pressed) return 2334;
		case SDLK_QUOTE: if (shift_pressed)	return 2336; return 2335;
		case SDLK_LEFTBRACKET: if (shift_pressed) return 2338; return 2337;
		case SDLK_c: if (shift_pressed)	return 2339; return 2350;
		case SDLK_l: if (shift_pressed)	return 2341; return 2340;
		case SDLK_o: if (shift_pressed) return 2343; return 2342;
		case SDLK_v: if (shift_pressed)	return 2345; return 2344;
		case SDLK_h: if (shift_pressed)	return 2347; return 2346;
		case SDLK_y: if (shift_pressed)	return 2349; return 2348;
		case SDLK_SLASH: if (shift_pressed) return 2399; return 2351;
		case SDLK_j: if (shift_pressed) return 2353; return 2352;
		case SDLK_n: if (shift_pressed) return 2355; return 2354;
		case SDLK_b: if (shift_pressed) return 2356; return 2357;
		case SDLK_m: if (shift_pressed) return 2358; return 2360;
		case SDLK_0: return 2406;
		case SDLK_1: return 2407;
		case SDLK_2: return 2408;
		case SDLK_3: return 2409;
		case SDLK_4: return 2410;
		case SDLK_5: return 2411;
		case SDLK_6: return 2412;
		case SDLK_7: return 2413;
		case SDLK_8: return 2414;
		case SDLK_9: return 2415;
		case SDLK_COMMA: if (shift_pressed) return 2359; break;
		}
	}

	return 0;
}
