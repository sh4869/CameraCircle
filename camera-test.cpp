#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char **argv)
{
 CvCapture *capture = 0;
 IplImage *frame = 0;
 int c;
 
 double width = 320, height = 240;
 
 // カメラに対するキャプチャ構造体を作成。
 if (argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
  capture = cvCreateCameraCapture(argc == 2 ? argv[1][0] - '0' : 0);
 
 cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
 cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
 
 cvNamedWindow("Capture", CV_WINDOW_AUTOSIZE);
 
 while(1)
 {
  // 画像キャプチャ。
  frame = cvQueryFrame(capture);
  cvShowImage("Capture", frame);
  
  if(cvWaitKey(33) == 'q') break;
 }
 
 // 後片付け。
 cvReleaseCapture(&capture);
 cvDestroyWindow("Capture");
 
 return 0;
}
