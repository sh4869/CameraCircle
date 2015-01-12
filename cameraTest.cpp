#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
 CvCapture *capture = 0;
 IplImage *frame = 0;
 int c;
 
 //double width = 160, height = 120;
 double width = 320, height = 240;
 //double width = 640, height = 480;
 //double width = 800, height = 600;
 
 // カメラに対するキャプチャ構造体を作成。
 if (argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
  capture = cvCreateCameraCapture(argc == 2 ? argv[1][0] - '0' : 0);
 
 // キャプチャサイズの設定。
 cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
 cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
 
 // ウィンドウ作成。
 cvNamedWindow("Capture", CV_WINDOW_AUTOSIZE);
 
 while(1)
 {
  // 画像キャプチャ。
  frame = cvQueryFrame(capture);
  cvShowImage("Capture", frame);
  
  c = cvWaitKey(2);
  if(c == '\x1b') break;
  //sleep(2);
 }
 
 // 後片付け。
 cvReleaseCapture(&capture);
 cvDestroyWindow("Capture");
 
 return 0;
}
