#include "include/dana_panorama.h"
#include "include/dana_cam_cabli.h"
#include "include/dana_pano_align.h"
#include "include/dana_blending.h"
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_ERROR, "dana_panorama", x)
// double cameraMat[3][3]={{1086.824276893329,0, 539.5},{0, 1086.824276893329, 959.5},{0, 0, 1}};//1080x1920的camera坐标参数
//double dist[5]={-0.4177642150313481,0.2237463754008228,0,0,-0.0716236427291802};
static Mat dana_stitich_proc(Mat frame_cam1, Mat frame_cam2, const int align_x, dana_blending_mode_t Mode);


dana_pano_info  *dana_pano_info_create( const int align_x, dana_blending_mode_t Mode, double cameraMat[][3],  double dist[],int W,int H)
{   
    dana_pano_info  *pano_info = new dana_pano_info; 
    pano_info->align_x  =  align_x;
    pano_info->Mode  =  Mode;
    pano_info->cameraMat = cameraMat;
    pano_info->dist  =  dist;
    dana_cam_cablib_init(cameraMat, dist, &(pano_info->map_coff), W, H);
    return pano_info;
}

void dana_pano_process(dana_pano_info *pano, Mat newImg ,bool IS_FIRST)
{
//    D("dana_pano_process start ......");

    dana_cam_cablib_proc(newImg,pano->map_coff);
//    D("IS_FIRST : %d ",IS_FIRST);
    if (0 == IS_FIRST) {
        pano->outimg = dana_stitich_proc(pano->outimg, newImg, pano->align_x, pano->Mode);
    } else {
        pano->outimg =newImg;
    }
}

void dana_pano_info_destroy(dana_pano_info *pano)
{
//    D("dana_pano_info_destroy  ......");

    pano->outimg.release();
        pano->map_coff.map_x.release();
        pano->map_coff.map_y.release();
        delete pano;
        pano = nullptr ;
}
//#if 0
//Mat dana_pano_handle(int img_no, Mat newImg, const int align_x,  dana_blending_mode_t Mode, double cameraMat[][3],  double dist[])
//{
//
//  if(1 == img_no)
//  {
//    int W = newImg.cols;
//    int H = newImg.rows;
//    dana_cam_cablib_init(cameraMat,dist,map_coff,W,H);
//  }
//  dana_cam_cablib_proc(newImg,map_coff);
//  if(1 < img_no)
//  {
//  result = dana_stitich_proc(result, newImg, align_x, Mode);
//  }
//  else
//  {
//      result=newImg;
//  }
//  return result;
//}
//
//
//Mat dana_pano_proc(vector<Mat> img_array, const int img_size, const int align_x, dana_blending_mode_t Mode,  double cameraMat[][3], double dist[])
//{
//    int stitich_loop = 0;
//    cabli_map map_coff;
//    int W = img_array[0].cols;
//    int H = img_array[0].rows;
//
//    dana_cam_cablib_init(cameraMat, dist, map_coff, W, H);
//
//    Mat result;
//
//    for (stitich_loop=0; stitich_loop<img_size; stitich_loop++) {
//        dana_cam_cablib_proc(img_array[stitich_loop], map_coff);
//    }
//
//    Mat frame_cam1, frame_cam2;
//    frame_cam1 = img_array[0];
//    frame_cam2 = img_array[1];
//    result = dana_stitich_proc(frame_cam1, frame_cam2, align_x, Mode);
//
//    for (stitich_loop=2; stitich_loop<img_size; stitich_loop++) {
//        result = dana_stitich_proc(result, img_array[stitich_loop], align_x, Mode);
//    }
//
//    return result;
//}
//#endif
static Mat dana_stitich_proc(Mat frame_cam1, Mat frame_cam2, const int align_x, dana_blending_mode_t Mode)
{
//    D("dana_stitich_proc start  ......");
  //  D()
    int W = frame_cam1.cols;
    int H = frame_cam1.rows;
    int W1 = frame_cam2.cols;
    int H1 = frame_cam2.rows;
    int res_x = 0, res;
    Mat result;
    fix_BGR fix_con;
//    D("align_x %d W : %d H:%d W1 :%d H1:%d ",align_x,W,H,W1,H1);//W:上次拼接后图的宽 W1：新用来拼接的图 1920

    if (0 == align_x) {   
        //-------------------------------------
        //获取模板匹配在width上的位移
        Mat temp;//(H1, temp_width, CV_8UC3, Scalar(0));
        Mat base_match;
        int offset_H = 50;
        int offset_W = 20;
        int temp_width = 40;
        int temp_num = 1;

// 崩溃点 W可能为0
        if(W == 0)
        {
            return frame_cam2;
        }
        frame_cam1(Rect(W-W1,0,W1,H1)).copyTo(base_match);  // 匹配一张照片宽度
        //frame_cam1(Rect(W-W1*0.75,0,W1*0.75,H1)).copyTo(base_match);// 缩小匹配区域为W1*0.75张部分
//            D("frame_cam2 pre ...");
            //frame_cam2(Rect(offset_W + i*temp_width, offset_H, temp_width, H1 - 2*offset_H)).copyTo(temp);//x,y,w,h
            frame_cam2(Rect(0, offset_H, 60, H1 - 2*offset_H)).copyTo(temp);//x,y,w,h

//            D("pre res_x : %d ",res_x);
            res_x += dana_temp_match_x(base_match, temp);
//        for (int i=0; i<temp_num; i++) {
//            D("frame_cam2 pre ...");
//            //frame_cam2(Rect(offset_W + i*temp_width, offset_H, temp_width, H1 - 2*offset_H)).copyTo(temp);//x,y,w,h
//            frame_cam2(Rect(0, offset_H, 60, H1 - 2*offset_H)).copyTo(temp);//x,y,w,h
//            D("pre res_x : %d ",res_x);
//            res_x += dana_temp_match_x(base_match, temp);
//
//            D("res_x : %d ",res_x);
//        }
        base_match.release();
        temp.release();
        //res = W1-res_x/temp_num + temp_width*temp_num/2 + offset_W;
        //res = W1-res_x/temp_num;
        res =W1-res_x;
//        if (res >= W1) {
//            res = W1/2;
//        }
    } else {
        res = align_x;
//        D("else res : %d",res);

    }
//    D("res : %d",res);
    if(res == 0)
    {
        res = 5;
    } else if(res == 1920)
    {
        res = 1915;
    }
        //---------------------------------------
        //光照补偿
//    Mat cover_region_1(H, res, CV_8UC3, Scalar(0));
        Mat cover_region_1(H, res, CV_8UC3, Scalar(0));
//        Mat cover_region_2(H, res, CV_8UC3, Scalar(0));
    Mat cover_region_2(H, W1-res, CV_8UC3, Scalar(0));
//    frame_cam1(Rect(W-res, 0, res, H)).copyTo(cover_region_1);
        frame_cam1(Rect(W-res, 0, res, H)).copyTo(cover_region_1);
//    frame_cam2(Rect(0, 0, res, H)).copyTo(cover_region_2);
        frame_cam2(Rect(res, 0, W1-res, H)).copyTo(cover_region_2);
        dana_fix_Pixel(cover_region_1, cover_region_2, fix_con);

        int x, y;

        for (y = 0; y < frame_cam2.rows; y++) {
            for (x = 0; x < frame_cam2.cols; x++) {
                frame_cam2.at<Vec3b>(y, x)[0] =
                        (frame_cam2.at<Vec3b>(y, x)[0] + fix_con.B) < 0 ? 0 : (
                                (frame_cam2.at<Vec3b>(y, x)[0] + fix_con.B) > 255 ? 255 : (
                                        frame_cam2.at<Vec3b>(y, x)[0] + fix_con.B));
                frame_cam2.at<Vec3b>(y, x)[1] =
                        (frame_cam2.at<Vec3b>(y, x)[1] + fix_con.G) < 0 ? 0 : (
                                (frame_cam2.at<Vec3b>(y, x)[1] + fix_con.G) > 255 ? 255 : (
                                        frame_cam2.at<Vec3b>(y, x)[1] + fix_con.G));
                frame_cam2.at<Vec3b>(y, x)[2] =
                        (frame_cam2.at<Vec3b>(y, x)[2] + fix_con.R) < 0 ? 0 : (
                                (frame_cam2.at<Vec3b>(y, x)[2] + fix_con.R) > 255 ? 255 : (
                                        frame_cam2.at<Vec3b>(y, x)[2] + fix_con.R));
            }
        }
        //cout<<fix_con.B<<"  "<<fix_con.G<<" "<<fix_con.R<<endl;
        //-------------------------------------
        //重叠部分融合
//    D("dana_blending pre ......");
    result = dana_blending(frame_cam1, frame_cam2, res, Mode);
    frame_cam1.release();
    frame_cam2.release();
    cover_region_1.release();
    cover_region_2.release();
    return result;
}
