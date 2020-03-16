#ifndef DANA_BLENDING_H
#define DANA_BLENDING_H

#include "./dana_panorama.h"

#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/blenders.hpp"

typedef struct _fix_BGR_s {
    int B;
    int G;
    int R;
} fix_BGR;

Mat dana_blending(Mat src_based, Mat temp, const int x, dana_blending_mode_t Mode);

void dana_fix_Pixel(Mat img1, Mat img2, fix_BGR &fix);


#endif
