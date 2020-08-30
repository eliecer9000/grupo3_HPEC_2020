#ifndef STEREOALGO_H
#define STEREOALGO_H

#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"


typedef enum
{
    eStereoAlgoType_OpenCV =0,  ///< verwendet den OpenCV-Algorithmus
    eStereoAlgoType_FPGA,       ///< verwendet den bei SensoPart implementierten Alogirthmus
    eStereoAlgoType_NoAlgo,     ///< kein Algorithmus zur Berechnung hinterlegt
}e_StereoAlgoType;


typedef enum
{
    ePlotCost_Aggregated =0,    ///< gibt die AggregatedCost aus
    ePlotCost_Hamming,          ///< gibt die Costfunction der Hammingdistanz aus
    ePlotCost_LR1,              ///< gibt die Costfunction der linken Richtung aus
    ePlotCost_LR2,              ///< gibt die Costfunction der linksoben Richtung aus
    ePlotCost_LR3,              ///< gibt die Costfunction der oben Richtung aus
    ePlotCost_LR4,              ///< gibt die Costfunction der rechtsoben Richtung aus
}e_PlotCost;


class StereoAlgo
{
public:
    /*******************************
     * Konsturktor/Destruktor
     ******************************/
    StereoAlgo();
    virtual ~StereoAlgo();

    /*******************************
     * Funktionsdeklaration
     ******************************/
    virtual void ComputeAlgo(cv::Mat LeftImg, cv::Mat RightImg, cv::Mat *DepthImg);

    virtual void SetMinDisp(int16_t s16MinDisp);
    virtual void SetMaxDisp(int16_t s16MaxDisp);
    virtual void SetBlockSize(uint8_t u8BlockSize);
    virtual void SetUniqueRatio(uint8_t u8UniqueRatio);
    virtual void SetP1(uint16_t u16P1);
    virtual void SetP2(uint16_t u16P2);

    e_StereoAlgoType GetStereoType();
    virtual void GetPixelCostFunction(int **ppCostFncPtr, int32_t *ps32CostSize, uint16_t u16XPos, uint16_t u16YPos, e_PlotCost ePlotFunc);


    // DEBUG:
    uint8_t m_u8DEBUGDirections = 0x0F; // Bitmaske, um die zugelassenen Richtungen anzuzeigen
    uint8_t m_u8DEBUGLeftNeighbor = 2;


protected:

    /*******************************
     * Variablendeklaration
     ******************************/
    int16_t m_s16MinDisp;
    int16_t m_s16MaxDisp;

    uint8_t m_u8BlockSize;
    uint8_t m_u8UniqueRatio;

    // SGBM
    uint16_t m_u16P1;
    uint16_t m_u16P2;

    e_StereoAlgoType m_eStereoAlgo = eStereoAlgoType_NoAlgo;

};

#endif // STEREOALGO_H
