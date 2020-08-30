#include "stereoalgo.h"


StereoAlgo::StereoAlgo()
{
    m_s16MaxDisp = 0;
    m_s16MaxDisp = 0;
    m_u8BlockSize = 0;
    m_u8UniqueRatio = 0;
    m_u16P1 =0;
    m_u16P2 =0;

}

StereoAlgo::~StereoAlgo()
{

}

void StereoAlgo::ComputeAlgo(cv::Mat LeftImg, cv::Mat RightImg, cv::Mat *DepthImg)
{

}

e_StereoAlgoType StereoAlgo::GetStereoType(void)
{
    return m_eStereoAlgo;
}

void StereoAlgo::GetPixelCostFunction(int **ppCostFncPtr, int32_t *ps32CostSize, uint16_t u16XPos, uint16_t u16YPos, e_PlotCost ePlotFunc)
{
    *ppCostFncPtr = nullptr;
    *ps32CostSize = 0;
}

void StereoAlgo::SetMinDisp(int16_t s16MinDisp)
{
    m_s16MinDisp  =s16MinDisp;

}
void StereoAlgo::SetMaxDisp(int16_t s16MaxDisp)
{
    m_s16MaxDisp = s16MaxDisp;
}
void StereoAlgo::SetBlockSize(uint8_t u8BlockSize)
{
    m_u8BlockSize = u8BlockSize;
}
void StereoAlgo::SetUniqueRatio(uint8_t u8UniqueRatio)
{
    m_u8UniqueRatio = u8UniqueRatio;
}

void StereoAlgo::SetP1(uint16_t u16P1)
{
    m_u16P1 = u16P1;
}

void StereoAlgo::SetP2(uint16_t u16P2)
{
    m_u16P2 = u16P2;
}
