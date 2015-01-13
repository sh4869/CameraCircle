#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

using namespace cv;

int main(int argc, char **argv)
{
	CvCapture *capture = 0;
	IplImage *frame = 0,*gray_img = 0;
	CvMemStorage *storage;
	CvSeq *circles = 0;
	int c,i;
	float *p;

	double width = 320, height = 240;

	// カメラに対するキャプチャ構造体を作成。
	if (argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
		capture = cvCreateCameraCapture(argc == 2 ? argv[1][0] - '0' : 0);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);

	cvNamedWindow("Capture", CV_WINDOW_AUTOSIZE);

	while(1)
	{
		frame = cvQueryFrame(capture);
		CvSize sizeOfImage = cvGetSize(frame);
		gray_img = cvCreateImage(sizeOfImage,IPL_DEPTH_8U,1);

		cvCvtColor(frame,gray_img,CV_BGR2GRAY);

		cvSmooth(gray_img,gray_img,CV_GAUSSIAN,11,11,0,0);
		storage = cvCreateMemStorage(0);

		circles = cvHoughCircles(gray_img,storage,CV_HOUGH_GRADIENT,
				1,100,20,50,10,MAX(gray_img->width,gray_img->height));

		for (i = 0; i < circles->total; i++) {
			p = (float *) cvGetSeqElem (circles, i);
			cvCircle (frame, cvPoint (cvRound (p[0]), cvRound (p[1])), 3, CV_RGB (0, 255, 0), -1, 8, 0);
			cvCircle (frame, cvPoint (cvRound (p[0]), cvRound (p[1])), cvRound (p[2]), CV_RGB (255, 0, 0), 3, 8, 0);
		}

		cvShowImage("Capture", frame);
		if(cvWaitKey(33) == 'q') break;
	}

	// 後片付け。
	cvReleaseCapture(&capture);
	cvDestroyWindow("Capture");

	return 0;
}
