#include "include/dana_cam_cabli.h"



//--------------------------------------------
//通过棋盘图标定获取下面的参数,对于不同camera需要提前标定
//--------------------------------------------

// double cameraMat[3][3]={{1086.824276893329,0, 539.5},{0, 1086.824276893329, 959.5},{0, 0, 1}};//1080x1920的camera坐标参数
//double dist[5]={-0.4177642150313481,0.2237463754008228,0,0,-0.0716236427291802};

// 支持多个任务

void dana_cam_cablib_init(double cameraMat[][3], double dist[], cabli_map *cabli_coff, const int W, const int H)
{ 
    Mat newCamMat;
    Mat R = Mat::eye(3, 3, CV_32F);
    Mat cameraMatrix = Mat(3, 3, CV_64F, cameraMat); 
    Mat distCoeffs = Mat(5, 1, CV_64F, dist);
    initUndistortRectifyMap(cameraMatrix, distCoeffs, R, newCamMat, Size(W, H), CV_32FC1, cabli_coff->map_x, cabli_coff->map_y);
}

void dana_cam_cablib_proc(Mat &img, cabli_map cabli_coff)
{ 
    //Mat rview;
    remap(img, img, cabli_coff.map_x, cabli_coff.map_y, INTER_LINEAR);
    //return rview;
}

