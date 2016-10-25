#include "camera.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

// Capture size
#define WIDTH 512 // Width of Image
#define HEIGHT 512 // Height of Image
RNG rng(12345); // RNG

int main(int argc, char *argv[])
{
	// Open the camera at 30fps, one level of downsampling, and BGR conversion
	CCamera* cam = StartCamera(WIDTH, HEIGHT, 30, 1, true);

	// Prompt the User The 'Program' is Running
	printf("--- Badass Contour & COM Finder v1 ---\n");
	printf("Initializing...");
	// Create a New Control Window
	namedWindow("Control --Push My Buttons ;)--", CV_WINDOW_AUTOSIZE);
	int iLowH = 0;
	int iHighH = 179;
	int iLowS = 0;
	int iHighS = 255;
	int iLowV = 0;
	int iHighV = 255;
	int iStructSize = 5;
	// Create trackbars in "Control" window
	cvCreateTrackbar("Low Hue", "Control --Push My Buttons ;)--", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("High Hue", "Control --Push My Buttons ;)--", &iHighH, 179);	
	cvCreateTrackbar("Low Sat", "Control --Push My Buttons ;)--", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("High Sat", "Control --Push My Buttons ;)--", &iHighS, 255);
	cvCreateTrackbar("Low Value", "Control --Push My Buttons ;)--", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("High Value", "Control --Push My Buttons ;)--", &iHighV, 255);
	cvCreateTrackbar("M Struct Size", "Control --Push My Buttons ;)--", &iStructSize, 255);
	// Create the display windows
	namedWindow("Display", WINDOW_AUTOSIZE);
	namedWindow("Thresholded", WINDOW_AUTOSIZE);
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	Mat thresh_img;
	Mat display_img;
	Mat hsv_img;
	Mat kernel;
	
	// Infinite Loop
	for (;;) {
		display_img = cam->Capture(0); // Acquire an image
		
		// If the image was not acquired
		if (!display_img.data) {
			printf("Failed to acquire an image :L *cries* \n");
			continue;
		}

		// If the image was successfully acquired
		cvtColor(display_img, hsv_img, COLOR_BGR2HSV); // Convert to HSV Colour Space
		imshow("Display", display_img); //Show the original image
		// Display the result of the current calibration settings
		display_img = display_img.clone(); // Deep Copy Because we will modify it below
		//Generate structural element
		kernel = getStructuringElement(MORPH_RECT, Size(iStructSize, iStructSize));
		// Apply morphological 'Open'
		morphologyEx(hsv_img, hsv_img, MORPH_OPEN, kernel);
		// Apply morphological 'Close'
		morphologyEx(hsv_img, hsv_img, MORPH_CLOSE, kernel);
		inRange(hsv_img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresh_img); // Threshold the image
		imshow("Thresholded", thresh_img); // Show the thresholded image
		imshow("Display", display_img); // Draw the final image
		
		// Find the Contours
		vector<vector<Point> > contours;
		Mat canny_output;
		vector<Vec4i> hierarchy;
		int cx;
		int cy;
		int thresh = 100;
		Canny(thresh_img, canny_output, 50, 150, 3 );
		findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));	
		// Get the Moments
		vector<Moments> mu(contours.size() );
		for( int i = 0; i < contours.size(); i++ ) { 
			mu[i] = moments( contours[i], false ); 
		}
		// Get the Centre of Mass for each Countour
		vector<Point2f> mc( contours.size() );
		for( int i = 0; i < contours.size(); i++ ) { 
			mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); 
		}

		// Draw the Contours
		Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
		for( int i = 0; i< contours.size(); i++ )
		{
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
			circle( drawing, mc[i], 4, color, -1, 8, 0 );
		}
		imshow( "Contours", drawing ); // Draw the Countours
		
		// Print the Countour(s) and the associated COM(s)
		printf("\t Area + Center of Mass for each detected Countour \n");
		printf("\t Countours Found [%i] \n", contours.size());
		for( int i = 0; i< contours.size(); i++ ) {
			printf("Contour[%d] | Area [%.2f] Center of Mass [%.2f,%.2f]\n", i, contourArea(contours[i]), mc[i].x, mc[i].y);
	 
		}
		
		// Allow openCV to process GUI events
		waitKey(100);

		// Update the GUI
		waitKey(10);
	}

	StopCamera();
}
