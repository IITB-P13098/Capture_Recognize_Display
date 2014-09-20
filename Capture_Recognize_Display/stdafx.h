// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <math.h>

#include <time.h>

#include <map>
#include <string>
using namespace std;

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "SDL.h"

#define MAX_FILE_PATH 256

using namespace cv;
// TODO: reference additional headers your program requires here


#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 900
#define SCREEN_BPP    32


#define MAX_CHAR_USED 43
int* get_char_used();
int get_char_index(int c);