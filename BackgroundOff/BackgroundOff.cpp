// BackGroundOff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

int _tmain(int argc, _TCHAR* argv[])
{
	cv::Mat frame, back, fore;
	cv::VideoCapture cap("aa.mp4");
	cv::BackgroundSubtractorMOG2 bg;
	bg.set("nmixtures", 6); // set number of gaussian mixtures
	bg.set("detectShadows", false); // turn the shadow detection off

	std::vector<std::vector<cv::Point> > contours;

	cv::namedWindow("Frame");
	cv::namedWindow("Background");
	cv::namedWindow("Foreground");

	while (cap.read(frame)){
		bg.operator()(frame, fore);
		bg.getBackgroundImage(back);
		cv::erode(fore, fore, cv::Mat());
		cv::dilate(fore, fore, cv::Mat());
		cv::findContours(fore, // binary input image 
			contours, // vector of vectors of points
			CV_RETR_EXTERNAL, // retrieve only external contours
			CV_CHAIN_APPROX_NONE); // detect all pixels of each contour
		cv::drawContours(frame, // draw contours here
			contours, // draw these contours
			-1, // draw all contours
			cv::Scalar(0, 0, 255), // set color
			2); // set thickness
		cv::imshow("Frame", frame);
		cv::imshow("Background", back);
		cv::imshow("Foreground", fore);
		if (cv::waitKey(30) >= 0) break;
	}

	return 0;
}

