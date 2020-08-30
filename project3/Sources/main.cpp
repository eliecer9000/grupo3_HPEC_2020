
#include <QDir>

#include "diff_and_error.h"
#include "histogram.h"
#include <iostream>
#include <fstream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "sgbm.h"

#define MAX_UINT64 std::numeric_limits<unsigned long long>::max()

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
    int MinDisp = 0;
    int MaxDisp = 32;
    int m_u8BlockSize_half = 5;
    int P1 = 2;
    int P2 = 60;
    int UniqRatio = 0;
    int SGBMDir = 3;
    string sources = "/home/eliecer/Downloads/Project3_Code/Test_data/";

    StereoFPGA *m_pStereoImg = new StereoFPGA();

    /* Load the images */
    Mat in_imgR= imread(sources + "Prof_R.png", IMREAD_GRAYSCALE);
    Mat in_imgL= imread(sources + "Prof_L.png", IMREAD_GRAYSCALE);

    m_pStereoImg->SetMinDisp(static_cast<int16_t>(MinDisp));
    m_pStereoImg->SetMaxDisp(static_cast<int16_t>(MaxDisp));
    m_pStereoImg->SetBlockSize(static_cast<uint8_t>(m_u8BlockSize_half));
    m_pStereoImg->SetP1(static_cast<uint16_t>(P1));
    m_pStereoImg->SetP2(static_cast<uint16_t>(P2));
    m_pStereoImg->SetUniqueRatio(static_cast<uint8_t>(UniqRatio));
    m_pStereoImg->SetNumOfDirections(static_cast<uint8_t>(SGBMDir));

    /* Check if computation can start -> both images are correctly loaded and parameters are valid */
    if (in_imgL.data == NULL)
    {
        printf("Cannot read left IMG.\n");
    }

    if ((in_imgR.data == NULL) & (in_imgR.size == in_imgL.size))
    {
        printf("Cannot read right IMG or incompatible size.\n");
    }

    //m_u8BlockSize_half must have odd size
    if(m_u8BlockSize_half%2 == 0){
        fprintf(stderr,"\n**********SAD Window size must be an odd number**********\n");
    }

    cv::Mat DepthImg;

    /**********************************************
     * Compute SGBM and copy the result in DepthImg
     **********************************************/
    m_pStereoImg->ComputeAlgo(in_imgL, in_imgR, &DepthImg);
    printf("Algorithm is done\n");

    return 0;
}
