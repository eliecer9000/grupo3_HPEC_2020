#include "histogram.h"

Mat Histogram(const Mat& In){

    int bins =256;
    int channels[] = {0};
    int histSize[] = {bins};
    float rangeGray[] = {0,255};
    const float* ranges[] = {rangeGray};
    cv::Mat histogram;
    double MaxVal;

    calcHist(&In, 1, channels, cv::Mat(),histogram, 1, histSize, ranges, true, false);
    cv::minMaxLoc(histogram, Q_NULLPTR, &MaxVal, Q_NULLPTR, Q_NULLPTR);
    cv::Mat outputImage;
    outputImage.create(480,640, CV_8UC(3));
    outputImage = cv::Scalar::all(256);

    cv::Point p1(0,0), p2(0, outputImage.rows-1);
    for(int i=0; i< bins; i++)
    {
        float value = histogram.at<float>(i,0);
        value = static_cast<float>(MaxVal) - value;
        value = value / static_cast<float>(MaxVal) * (outputImage.rows);
        p1.y = static_cast<int>(value);
        p2.x = static_cast<int>(float(i+1) * float(outputImage.cols) / float(bins));
        rectangle(outputImage, p1, p2, cv::Scalar::all(0));
        p1.x = p2.x;
    }
    return outputImage;
}
