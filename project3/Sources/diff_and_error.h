#ifndef DIFF_AND_ERROR_H
#define DIFF_AND_ERROR_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

float Diff_and_Error(const Mat& In, Mat& dst, Mat& GT_Image, bool output_img);

#endif // DIFF_AND_ERROR_H
