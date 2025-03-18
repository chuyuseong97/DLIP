/*------------------------------------------------------------------------------------------\
@ Deep Learning & Image Processing  by Yuseong CHU - Handong Global University

Author          : Yuseong_CHU
Created         : 11-03-2025
Modified        : 11-03-2025
Language/ver	: C++
Course		: Deep Learning & Image Processing

Description     : "Assignment(1 week)"
/------------------------------------------------------------------------------------------*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	/*  read image  */
	String HGU_logo = "../../image/image.jpg";  // class
	Mat img = imread(HGU_logo);  //Mat class
	Mat img_gray = imread(HGU_logo, 0);  // read in grayscale

	/* initial image dimensions */
	int width  = img_gray.cols;
	int height = img_gray.rows;

	/*  write image  */
	String save_img = "writeTest.jpg";  // C++ class/syntax (String, cout, cin)
	imwrite(save_img, img);

	/* Resize image */
	Mat img_resize;
	resize(img_gray, img_resize, Size(width / 2, height / 2));

	/* Flip image */
	Mat img_flip;
	flip(img_resize, img_flip, -1);

	/* ROI */
	Rect r(127, 146, 200, 200);
	Mat img_ROI = img_gray(r);

	/* Create output images initialized with white color */
	Mat Output_1 = Mat::ones(img_gray.size(), CV_8UC1) * 255;
	Mat Output_2 = Mat::ones(img_gray.size(), CV_8UC1) * 255;
	Mat Output_3 = Mat::ones(img_gray.size(), CV_8UC1) * 255;

	/*  Output #1  */
	for (int i = 0; i < img_resize.rows; i++) {
		for (int j = 0; j < img_resize.cols; j++) {
			Output_1.at<uchar>(i, j) = img_resize.at<uchar>(i, j);
		}  
	}

	/*  Output #2  */
	int x_offset = (height - img_flip.rows) / 2;
	int y_offset = (width - img_flip.cols) / 2;

	for (int i = 0; i < img_flip.rows; i++) {
		for (int j = 0; j < img_flip.cols; j++) {
			Output_2.at<uchar>(i + x_offset,j + y_offset) = img_flip.at<uchar>(i, j);
		}
	}

	/*  Output #3  */
	int x_offset_2 = height - img_flip.rows;
	int y_offset_2 = width - img_flip.cols;

	for (int i = 0; i < img_ROI.rows; i++) {
		for (int j = 0; j < img_ROI.cols; j++) {
			Output_3.at<uchar>(i + x_offset_2, j + y_offset_2) = img_ROI.at<uchar>(i, j);
		}
	}
	
	/*  display image  */
	namedWindow("image_gray", WINDOW_AUTOSIZE);
	imshow("image_gray", img_gray);
	imshow("Output #1", Output_1);
	imshow("Output #2", Output_2);
	imshow("Output #3", Output_3);


	waitKey(0);
}
