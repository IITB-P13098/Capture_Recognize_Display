#pragma once

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

void display_image(IplImage *DispImage, IplImage *img, int x = 0, int y = 0, float scale = 1);

IplImage* crop_image(IplImage *src, int x, int y, int w, int h);