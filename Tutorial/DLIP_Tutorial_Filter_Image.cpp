/* ------------------------------------------------------ /
*Image Proccessing with Deep Learning
* OpenCV : Filter Demo
* Created : 2021 - Spring
------------------------------------------------------ */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main()
{
	Mat src, dst;
	src = imread("../../image/Pattern_original_GaussNoise.tif", 0);
	imshow("Source Image" , src);

	int i = 3;
	Size kernelSize(i,i);

	/* Blur */
	blur(src, dst, Size(i, i), Point(-1,-1), 1);
	namedWindow("Blur", WINDOW_NORMAL);
	imshow("Blur", dst);

	/* Gaussian Filter */

	
	GaussianBlur(src, dst, kernelSize, 0, 0, 1);
	namedWindow("Gaussian", WINDOW_NORMAL);
	imshow("Gaussian", dst);


	/* Median Filter */
	// 중앙값으로 정렬
	
	medianBlur(src, dst, 3);
	namedWindow("Median", WINDOW_AUTOSIZE);
	imshow("Median", dst);


	/* Laplacian Filter */
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16U;

	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	src.convertTo(src, CV_16U);
	Mat result_laplcaian = src - dst;
	result_laplcaian.convertTo(result_laplcaian, CV_8U);
	namedWindow("Laplacian", WINDOW_AUTOSIZE);
	imshow("Laplacian", result_laplcaian);


	/* 2D Convolution of a filter kernel */
	/* Design a normalized box filter kernel 5 by 5 */
	src.convertTo(src, CV_8UC1);

	Mat kernel;
	delta = 0;
	ddepth = -1;
	kernel_size = 5;
	Point anchor = Point(-1, -1);

	// ADD YOUR CODE HERE
	// ADD YOUR CODE HERE

	filter2D(src, dst, ddepth, kernel_size, anchor);
	

	namedWindow("Conv2D", WINDOW_AUTOSIZE);
	imshow("Conv2D", dst);


	waitKey(0);
}