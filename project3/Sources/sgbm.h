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
  void compute_census_transform (cv::Mat img, uint64_t * ct);
  int compute_hamming_distance (uint64_t a, uint64_t b);
  void compute_hamming (uint64_t * ct1, uint64_t * ct2, int *accumulatedCost);

  int compute_SGM (int *initCost, cv::Mat * disparitySGBM);
  void cost_aggregation (int *aggregatedCost, int *Lr);
  void cost_computation (int *Lr, int *initCost);
  int find_minLri (int *Lrpr);
  void init_Lr (int *Lr, int *initCost);

  void calc_disp (int *Cost, cv::Mat * disparityBM);

  uint8_t m_u8Directions;
  uint16_t m_u16height_after_census, m_u16width_after_census;
  float_t m_fFactor;
  uint16_t m_u16TotalDisp;


  int *m_ActiveInitCost = nullptr;
  int *m_ActiveLrCost = nullptr;
  int *m_ActiveAggrCost = nullptr;

};

#endif // STEREOFPGA_H