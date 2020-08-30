#include "diff_and_error.h"

float Diff_and_Error(const Mat& In, Mat& dst, Mat& GT_Image, bool output_img){
    unsigned char diff=0;
    volatile float error =0;
    int count = 0;

    for (int i=0; i<In.rows; i++) {
        for (int j=0; j<In.cols; j++) {
            if((GT_Image.at<unsigned char>(i,j)!=0))
            {
                diff = abs(In.at<unsigned char>(i,j) - GT_Image.at<unsigned char>(i,j));
                error += diff;
                if(output_img){
                    dst.at<unsigned char>(i,j) = diff;
                }
                count ++;
            }
            else if (output_img) {
                dst.at<unsigned char>(i,j) = 0;
            }
        }
    }

    return error/(count);
}
