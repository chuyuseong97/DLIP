/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV : Filter Demo - Video
* Created: 2025-Spring
------------------------------------------------------*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	/*  open the video camera no.0  */
	VideoCapture cap(0);

	if (!cap.isOpened())	// if not success, exit the programm
	{
		cout << "Cannot open the video cam\n";
		return -1;
	}

	namedWindow("MyVideo", WINDOW_AUTOSIZE);

	int key = 0;
	int kernel_size = 11;
	int filter_type = 0;

	int ddepth = CV_16U;
	int scale = 1;
	int delta = 0;

	while (1)
	{
		Mat src, dst;

		/*  read a new frame from video  */
		bool bSuccess = cap.read(src);

		if (!bSuccess)	// if not success, break loop
		{
			cout << "Cannot find a frame from  video stream\n";
			break;
		}


		key = waitKey(30);
		if (key == 27) // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop
		{
			cout << "ESC key is pressed by user\n";
			break;
		}

		else if (key == 'b' || key == 'B')
		{
			filter_type = 1;	// blur
		}

		/* Keyboard input for other filters*/
		else if (key == 'L' || key == 'l') 
		{
			filter_type = 2;
		}

		else if (key == 'M' || key == 'm') 
		{
			filter_type = 3;
		}

		if (filter_type == 1)
			blur(src, dst, Size(kernel_size, kernel_size), Point(-1, -1));
		/* Apply filter accroding to filter type */
		else if (filter_type == 2) {
			Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
			src.convertTo(src, CV_16U);
			dst = src - dst;
			dst.convertTo(dst, CV_8U);
		}
		else if (filter_type == 3)
			medianBlur(src, dst, 3);
		else
			src.copyTo(dst);

		imshow("MyVideo", dst);
	}
	return 0;
}
