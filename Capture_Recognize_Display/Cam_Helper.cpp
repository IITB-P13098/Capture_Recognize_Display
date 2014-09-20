#include "StdAfx.h"
#include "Cam_Helper.h"

#include "image_helper.h"

HINSTANCE m_HIDevRecEngineDLL;

CvCapture* capture;
int num_recog_char;
g_OCRCharInfo *g_Output;

int recog_char = 0;
int get_recog_char() { return recog_char; }

#include <time.h>
clock_t update_time;

_fnInitEngine pFnInitEngine;
_fnCaliberateCamera pFnCaliberateCamera;
_fnRecognizeChars pFnRecognizeChars;
_fnFreeEngine pFnFreeEngine;
_fnEngineVersionInfo pFnEngineVersionInfo;

int init_cam()
{
	TCHAR strEnginesFilePath[MAX_FILE_PATH];
	TCHAR strFolderPath[MAX_FILE_PATH]={0};
	GetModuleFileName(NULL, strFolderPath, _MAX_PATH); 
	*wcsrchr(strFolderPath,'\\') = '\0';
	wcscpy(strEnginesFilePath,strFolderPath);
	wcscat(strEnginesFilePath,L"\\OCRtoyDLL.dll");

	m_HIDevRecEngineDLL = LoadLibrary(strEnginesFilePath);

	if (m_HIDevRecEngineDLL == NULL) exit(0);

	pFnInitEngine        = (_fnInitEngine)GetProcAddress(m_HIDevRecEngineDLL,"fn_InitEngine");
	pFnCaliberateCamera  = (_fnCaliberateCamera)GetProcAddress(m_HIDevRecEngineDLL,"fn_CaliberateCamera");
	pFnRecognizeChars    = (_fnRecognizeChars)GetProcAddress(m_HIDevRecEngineDLL,"fn_RecognizeChars");
	pFnFreeEngine        = (_fnFreeEngine)GetProcAddress(m_HIDevRecEngineDLL,"fn_FreeEngine");
	pFnEngineVersionInfo = (_fnEngineVersionInfo)GetProcAddress(m_HIDevRecEngineDLL,"fn_EngineVersionInfo");

	init_cam_2();
}

int init_cam_2()
{
	//----Calibrate the camera / screen
	//This image needs to be shown on the LCD screen
	IplImage *image = cvLoadImage("fourCorners.bmp");
	cvNamedWindow( "cam view", CV_WINDOW_AUTOSIZE );
	cvShowImage("cam view",image);

	capture = cvCaptureFromCAM(0);
	if ( !capture )
	{
		fprintf( stderr, "ERROR: capture is NULL \n" );
		getchar();
		return -1;
	}

	IplImage *curr_frame = cvQueryFrame(capture);

	//--Calibrate
	g_Resolution screenResolution;
	screenResolution.width  = 640; //width of the screen
	screenResolution.height = 480; //height of the screen
	g_Resolution cameraResolution;
	cameraResolution.width  = curr_frame->width;  //width of the camera
	cameraResolution.height = curr_frame->height; //height of the camera

	int calibrationFlag = pFnCaliberateCamera(curr_frame, cameraResolution, screenResolution);
	if(calibrationFlag == 1)
	{
		printf("caliberation done\n");
	}
	else
	{
		printf("caliberation failed\n");
		return 0;
	}

	//--Init engine
	pFnInitEngine();
	printf("Engine initialised successfully...\n");

	g_Output=(g_OCRCharInfo *)malloc(sizeof(g_OCRCharInfo));
	if(g_Output==NULL)
	{
		printf("Mem allocation problem");
	}
}	

void exit_cam()
{
	cvDestroyWindow( "cam view" );
	cvReleaseCapture( &capture );

	pFnFreeEngine();
	printf("Engine freed successfully...\n");

	FreeLibrary(m_HIDevRecEngineDLL);
	m_HIDevRecEngineDLL = NULL;
}

void update_cam(int capture_type)
{
	//Sleep(10); // in milisecond
	clock_t current_time = clock();
	clock_t elapsed_time = clock() - update_time;
	float elapsed_time_sec = ((float)elapsed_time)/CLOCKS_PER_SEC;

	//if (elapsed_time_sec < 1.0f) return;

	update_time = current_time;

	// Get one frame
	IplImage *curr_frame = cvQueryFrame( capture );
	if ( !curr_frame )
	{
		fprintf( stderr, "ERROR: frame is null...\n" );
		getchar();
		exit(0);
	}
	cvShowImage( "cam view", curr_frame );

	cvResetImageROI(curr_frame);
	switch (capture_type)
	{
	case CAPTURE_LEFT_HALF:
		cvSetImageROI(curr_frame, cvRect(0, 0, curr_frame->width/2, curr_frame->height));
		break;
	case CAPTURE_LEFT:
		cvSetImageROI(curr_frame, cvRect(0, 0, curr_frame->width/3, curr_frame->height));
		break;
	case CAPTURE_RIGHT_HALF:
		cvSetImageROI(curr_frame, cvRect(curr_frame->width/2, 0, curr_frame->width/2, curr_frame->height));
		break;
	case CAPTURE_RIGHT:
		cvSetImageROI(curr_frame, cvRect(2*curr_frame->width/3, 0, curr_frame->width/3, curr_frame->height));
		break;
	case CAPTURE_CENTER:
		cvSetImageROI(curr_frame, cvRect(curr_frame->width/3, 0, curr_frame->width/3, curr_frame->height)); 
		break;
	}

// 	int w = curr_frame->width, h = curr_frame->height;
// 	float scale = 0.35f;
// 	IplImage *curr_frame_small = cvCreateImage( cvSize(w*scale, h*scale), 8, 3 );
// 	cvSet(curr_frame_small, cvScalar(255,255,255));
// 
// 	//crop capture
// 	IplImage* cropped_curr_frame = 0;
// 	switch (capture_type)
// 	{
// 	case CAPTURE_LEFT:
// 		cropped_curr_frame = crop_image(curr_frame, 0, 0, curr_frame->width/2, curr_frame->height);
// 
// 		//set capture to white and display cropped image
// 		cvSet(curr_frame, cvScalar(255,255,255));
// 		display_image(curr_frame, cropped_curr_frame);
// 		break;
// 	case CAPTURE_RIGHT:
// 		cropped_curr_frame = crop_image(curr_frame, curr_frame->width/2, 0, curr_frame->width/2, curr_frame->height);
// 		cvSet(curr_frame, cvScalar(255,255,255));
// 		display_image(curr_frame, cropped_curr_frame, curr_frame->width/2);
// 		break;
// 	case CAPTURE_CENTER:
// 		cropped_curr_frame = crop_image(curr_frame, curr_frame->width/3, 0, curr_frame->width/3, curr_frame->height);
// 		cvSet(curr_frame, cvScalar(255,255,255));
// 		display_image(curr_frame, cropped_curr_frame, curr_frame->width/3);
// 		break;
// 	}
// 
// 	display_image(curr_frame_small, curr_frame, 0, 0, scale);
// 	cvShowImage( "cam view", curr_frame_small );

	static int prev_temp_recog_char = 0, temp_recog_char = 0, recog_char_count = 0;
	temp_recog_char = 0;

	num_recog_char = pFnRecognizeChars(curr_frame,0,&g_Output);
	printf("\n\n\nTest: chars recog count: %d",num_recog_char);

	for(int i=0; i<num_recog_char; i++)
	{
		int g_Output_char = g_Output->g_UnicodeChars[i];

		if (i>0)
		{
			if (!is_laying_inside_conture(g_Output->boundingBoxes[i-1], g_Output->boundingBoxes[i]))
			{
				temp_recog_char = g_Output_char;
			}
		}
		else
		{
			temp_recog_char = g_Output_char;
		}

		temp_recog_char = g_Output_char;

		//printf("\n%d", a);

		printf("\nTest: Angle:%f Char:%d(%x) Bounded by:(%d,%d)(%d,%d) with centroid at(%d,%d) ",
			g_Output->g_Angle[i],
			g_Output_char,
			g_Output->g_UnicodeChars[i],
			(g_Output->boundingBoxes[i]).minX,
			(g_Output->boundingBoxes[i]).minY,
			(g_Output->boundingBoxes[i]).maxX,
			(g_Output->boundingBoxes[i]).maxY,
			(g_Output->centroids[i]).x,
			(g_Output->centroids[i]).y);
	}

//	cvReleaseImage(&cropped_curr_frame);
//	cvReleaseImage(&curr_frame_small);
	//cvReleaseImage(&curr_frame);

	//recog_char = temp_recog_char; return;

	if (prev_temp_recog_char == temp_recog_char)
	{
		recog_char_count = min(recog_char_count+1, 10);

		if (recog_char_count > 5)
		{
			recog_char = prev_temp_recog_char;
		}
	}
	else
	{
		recog_char_count = max(recog_char_count-1, 0);

		if (recog_char_count == 0)
		{
			prev_temp_recog_char = temp_recog_char;
		}
	}
}

bool is_laying_inside_conture(g_BoundingBox smaller, g_BoundingBox bigger)
{
	if (min(bigger.maxX, bigger.minX) <= min(smaller.maxX, smaller.minX))
	{
		if (max(smaller.maxX, smaller.minX) <= max(bigger.maxX, bigger.minX))
		{
			if (min(bigger.maxY, bigger.minY) <= min(smaller.maxY, smaller.minY))
			{
				if (max(smaller.maxY, smaller.minY) <= max(bigger.maxY, bigger.minY))
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}