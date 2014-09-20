#include "StdAfx.h"
#include "image_helper.h"

void display_image(IplImage *DispImage, IplImage *img, int x, int y, float scale)
{
	if ( !img || !DispImage) return;

	int w = img->width, h = img->height;

	// Set the image ROI to display the current image
	cvSetImageROI(DispImage, cvRect(x, y, (int)( w*scale ), (int)( h*scale )));

	// Resize the input image and copy the it to the Single Big Image
	cvResize(img, DispImage);

	// Reset the ROI in order to display the next image
	cvResetImageROI(DispImage);
}

IplImage* crop_image(IplImage *src, int x, int y, int w, int h)
{
	cvSetImageROI(src, cvRect(x, y, w, h));

	IplImage *dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels );

	cvCopy(src, dst, NULL);

	cvResetImageROI(src);

	return dst;
}
