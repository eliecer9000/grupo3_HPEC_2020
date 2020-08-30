#ifndef STEREOFPGA_H
#define STEREOFPGA_H

#include "stereoalgo.h"

class StereoFPGA:public StereoAlgo
{
public:
    /*******************************
     * Consturctor/Destructor
     ******************************/
  StereoFPGA ();
  ~StereoFPGA ();

    /*******************************
     * Functions/Variables Deklaration
     ******************************/
  void SetNumOfDirections (uint8_t u8NewDirect);
  void ComputeAlgo (cv::Mat LeftImg, cv::Mat RightImg, cv::Mat * DepthImg);
  uint16_t m_u16xMin, m_u16xMax, m_u16yMin, m_u16yMax;
  uint8_t m_u8BlockSize_half;

private:
    /*********************************
     * Functions/Variables Deklaration
     *********************************/
  void compute_census_transform (cv::Mat img, uint32_t * ct);
  uint8_t compute_hamming_distance (uint32_t a, uint32_t b);
  void compute_hamming (uint32_t * ct1, uint32_t * ct2, uint8_t *accumulatedCost);

  int compute_SGM (uint8_t *initCost, cv::Mat * disparitySGBM);
  void cost_aggregation (uint16_t *aggregatedCost, uint8_t *Lr);
  void cost_computation (uint8_t *Lr, uint8_t *initCost);
  uint8_t find_minLri (uint8_t *Lrpr);
  void init_Lr (uint8_t *Lr, uint8_t *initCost);

  void calc_disp (uint16_t *Cost, cv::Mat * disparityBM);

  uint8_t m_u8Directions;
  uint16_t m_u16height_after_census, m_u16width_after_census;
  float_t m_fFactor;
  uint16_t m_u16TotalDisp;


  uint8_t *m_ActiveInitCost = nullptr;
  uint8_t *m_ActiveLrCost = nullptr;
  uint16_t *m_ActiveAggrCost = nullptr;

};

#endif // STEREOFPGA_H
