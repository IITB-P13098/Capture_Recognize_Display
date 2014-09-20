#pragma once

#include "Toy.h"
typedef void (*_fnInitEngine)();
typedef int  (*_fnRecognizeChars)(IplImage* inputImage,int fAlphaNumeral,g_OCRCharInfo** g_OutputCharInfoAll);
typedef int  (*_fnCaliberateCamera)(IplImage* inputImage,g_Resolution cameraReso,g_Resolution screenResolution);
typedef void (*_fnFreeEngine)();
typedef char*(*_fnEngineVersionInfo)();

int  init_cam();
int  init_cam_2();
void update_cam(int capture_type);
void exit_cam();

int get_recog_char();

bool is_laying_inside_conture(g_BoundingBox first, g_BoundingBox second);

#define CAPTURE_FULL        0
#define CAPTURE_LEFT_HALF   1
#define CAPTURE_LEFT        2
#define CAPTURE_RIGHT_HALF  3
#define CAPTURE_RIGHT       4
#define CAPTURE_CENTER      5
