#ifndef DANA_CAM_CABLI_H
#define DANA_CAM_CABLI_H

#include "./dana_panorama.h"


// 支持多个任务

//void dana_cam_cablib_init(double cameraMat[][3], double dist[], cabli_map *cabli_coff, const int W, const int H);
void dana_cam_cablib_init(double cameraMat[][3], double dist[], cabli_map *cabli_coff, const int W, const int H);
void dana_cam_cablib_proc(Mat &img,cabli_map cabli_coff);

#endif
