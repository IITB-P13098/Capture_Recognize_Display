
#include <tchar.h>
#include <cv.h>
#include "cxcore.h"
#include "highgui.h"
//#include "cxtypes.h" 

#ifdef CALC_EXPORTS
	#define CALC_API __declspec (dllexport)
#else
	#define CALC_API __declspec (dllimport)
#endif
#define SOME_INSTN_BUF		260
#define APP_MAX_SHAPES		6 //Maximum allowed cut-outs/shapes placed on toy

	//typedef void (WINAPI * PCTOR) (IplImage *frame,g_Resolution camRes,g_Resolution scrRes);

	typedef struct g_BoundingBox_Struct
	{
		unsigned int minX;
		unsigned int minY;
		unsigned int maxX;
		unsigned int maxY;				
	} g_BoundingBox;

	typedef struct g_Centroid_Struct
	{
		unsigned int x;	 
		unsigned int y;	
	} g_Centroid;

	typedef struct g_OCRCharInfo_Struct
	{
		float g_Angle[APP_MAX_SHAPES];//Angle or tilt
		g_BoundingBox boundingBoxes[APP_MAX_SHAPES];
		//Bounding box around the shape of char/numeral
		wchar_t g_UnicodeChars[APP_MAX_SHAPES];	
		//Array of Unicode chars		
		g_Centroid centroids[APP_MAX_SHAPES]; 	// Centroid of each character						
	} g_OCRCharInfo;		

	typedef struct g_Resolution_Struct
	{
		unsigned int width;	 
		unsigned int height;	
	} g_Resolution;


	//private:	
	//TCHAR m_szLastUsedFunc[SOME_INSTN_BUF];
	//public:
	//CCalc (); 
	extern "C" int __cdecl fn_CaliberateCamera (IplImage* inputImage, g_Resolution cameraReso,g_Resolution screenReso);
  	extern "C" void __cdecl fn_InitEngine (); 	
	//extern "C" g_OCRCharInfo* __cdecl  fn_RecognizeChars(IplImage* inputImage, int alphaNumeralFlag);
	extern "C" int __cdecl  fn_RecognizeChars(IplImage* inputImage, int alphanumeral,g_OCRCharInfo** g_Output);

	extern "C" void __cdecl fn_FreeEngine(void);
	extern "C" char* __cdecl fn_EngineVersionInfo(void);

  	//TCHAR* GetLastUsedFunc ();

	/*
class CALC_API toydll
{
	private:	
	TCHAR m_szLastUsedFunc[SOME_INSTN_BUF];
	public:
		//CCalc (); 
  	void fn_InitEngine ();
 	int fn_CaliberateCamera (IplImage* inputImage, g_Resolution cameraReso,g_Resolution screenReso);
	g_OCRCharInfo * fn_RecognizeChars(IplImage* inputImage, int alphaNumeralFlag);
	void fn_FreeEngine(void);
	char* fn_EngineVersionInfo(void);


  	TCHAR* GetLastUsedFunc ();
};*/