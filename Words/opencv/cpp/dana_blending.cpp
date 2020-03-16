#include "include/dana_blending.h"
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_ERROR, "dana_panorama", x)
#define min_thi(a,b,c) (a>b?(b>c?c:b):(a>c?c:a));

static Mat dana_mutli_band_blending(Mat image1, Mat image2);
static unsigned int mat_square(Vec3b array1, Vec3b array2);
static Mat dana_optimal_seamline_blending(Mat image1, Mat image2);//最佳缝合线

Mat dana_blending(Mat src_based, Mat temp, const int x, dana_blending_mode_t Mode)
{
//    D("dana_blending start ......");

    int W = src_based.cols;
    int H = src_based.rows;
    int W1 = temp.cols;
    int B;
    int G;
    int R;
    float q_temp = 0.0;

    Mat shift_img(H, W1+W-x, CV_8UC3, Scalar(0));
    src_based(Rect(0, 0, W-x, H)).copyTo(shift_img(Rect(0, 0, W-x, H)));
    temp(Rect(x, 0, W1-x, H)).copyTo(shift_img(Rect(W, 0, W1-x, H)));

    if (DANA_BLENDING_MODE_LINEAR == Mode) {
        int m_x, m_y;
        for (m_y=0; m_y<H; m_y++) {
            for(m_x=0; m_x<x; m_x++) {
                q_temp = CV_PI/2*(float)(m_x/(x*1.0));
                B = (int)(src_based.at<Vec3b>(m_y, W-x + m_x)[0] * pow(cos(q_temp), 2) + temp.at<Vec3b>(m_y, m_x)[0] * pow(sin(q_temp), 2));
                G = (int)(src_based.at<Vec3b>(m_y, W-x + m_x)[1] * pow(cos(q_temp), 2) + temp.at<Vec3b>(m_y, m_x)[1] * pow(sin(q_temp), 2));
                R = (int)(src_based.at<Vec3b>(m_y, W-x + m_x)[2] * pow(cos(q_temp), 2) + temp.at<Vec3b>(m_y, m_x)[2] * pow(sin(q_temp), 2));

                shift_img.at<Vec3b>(m_y, W-x + m_x)[0] = (B>255)?255:B;
                shift_img.at<Vec3b>(m_y, W-x + m_x)[1] = (G>255)?255:G;
                shift_img.at<Vec3b>(m_y, W-x + m_x)[2] = (R>255)?255:R;
            }
        }
    } else if (DANA_BLENDING_MODE_MUTLI_BAND == Mode) {
        Mat image1(H, x, CV_8UC3, Scalar(0));
        Mat image2(H, x, CV_8UC3, Scalar(0));
        Mat result(H, x, CV_8UC3, Scalar(0));

        src_based(Rect(W-x, 0, x, H)).copyTo(image1);

        temp(Rect(0, 0, x, H)).copyTo(image2);

        result = dana_mutli_band_blending(image1, image2);
        result.copyTo(shift_img(Rect(W-x, 0, x, H)));
    } else if (DANA_BLENDING_MODE_OPTIMAL_SEAMLINE == Mode) {
        Mat image1(H, x, CV_8UC3, Scalar(0));
        Mat image2(H, x, CV_8UC3, Scalar(0));
        Mat result(H, x, CV_8UC3, Scalar(0));
        src_based(Rect(W-x, 0, x, H)).copyTo(image1);
        temp(Rect(0, 0, x, H)).copyTo(image2);
        result = dana_optimal_seamline_blending(image1, image2);
        result.copyTo(shift_img(Rect(W-x, 0, x, H)));
    }

    return shift_img;
}

static Mat dana_mutli_band_blending(Mat image1, Mat image2)//mutli-band算法
{
//    D("dana_mutli_band_blending start ......");

    Mat image1s, image2s;
    image1.convertTo(image1s, CV_16S);
    image2.convertTo(image2s, CV_16S);
    Mat mask1(image1s.size(), CV_8U);
    mask1(Rect(0, 0, mask1.cols/2, mask1.rows)).setTo(255);
    mask1(Rect(mask1.cols/2, 0, mask1.cols - mask1.cols/2, mask1.rows)).setTo(0);

    Mat mask2(image2s.size(), CV_8U);
    mask2(Rect(0, 0, mask2.cols/2, mask2.rows)).setTo(0);
    mask2(Rect(mask2.cols/2, 0, mask2.cols - mask2.cols/2, mask2.rows)).setTo(255);

    detail::MultiBandBlender blender(false, 5);//调试

    blender.prepare(Rect(0, 0, max(image1s.cols, image2s.cols), max(image1s.rows, image2s.rows)));
    blender.feed(image1s, mask1, Point(0,0));
    blender.feed(image2s, mask2, Point(0,0));

    Mat result_s, result_mask;
    blender.blend(result_s, result_mask);
    Mat result; result_s.convertTo(result, CV_8U);

    return result;
}

static unsigned int mat_square(Vec3b array1, Vec3b array2)
{
    int i=0;
    unsigned int sum=0;

    for (i=0; i<3; i++) {
        sum += (array1[i] - array2[i]) * (array1[i] - array2[i]);
    }

    return sum;
}
static Mat dana_optimal_seamline_blending(Mat image1, Mat image2)//最佳缝合线算法
{
//    D("dana_optimal_seamline_blending start ......");

    int W=image1.cols;
    int H=image1.rows;
    Mat shift_img(H, W, CV_8UC3, Scalar(0));
    int cost_x, cost_y;
    int min_temp;
    unsigned long min_cost=0;
    unsigned long *ERR_cost = (unsigned long *) malloc(sizeof(unsigned long) * W * H);
    if (NULL == ERR_cost) {
        // ? TODO
    }

    for (cost_x=0; cost_x<W; cost_x++) {
        *(ERR_cost+cost_x) = mat_square(image1.at<Vec3b>(0, cost_x), image2.at<Vec3b>(0, cost_x));
    }

    for (cost_y=1;cost_y<H;cost_y++) {
        *(ERR_cost+cost_y*W) = mat_square(image1.at<Vec3b>(cost_y, 0), image2.at<Vec3b>(cost_y, 0)) + min(*(ERR_cost + (cost_y - 1)*W), *(ERR_cost + (cost_y - 1)*W + 1));

        for (cost_x=1; cost_x<W-1; cost_x++) {   
            *(ERR_cost+cost_y*W + cost_x) = mat_square(image1.at<Vec3b>(cost_y, cost_x), image2.at<Vec3b>(cost_y, cost_x)) + min_thi(*(ERR_cost + (cost_y - 1)*W + cost_x -1 ), *(ERR_cost + (cost_y - 1)*W + cost_x), *(ERR_cost + (cost_y - 1)*W + cost_x + 1));
        }  

        *(ERR_cost + (cost_y + 1)*W - 1) = mat_square(image1.at<Vec3b>(cost_y, W - 1), image2.at<Vec3b>(cost_y, W - 1)) + min(*(ERR_cost + cost_y*W - 1), *(ERR_cost + cost_y*W -2 ));
    }

    for (cost_y=0; cost_y<H; cost_y++) { 
        min_cost = ~(unsigned long)0;
        min_temp = 0;

        for (cost_x=0; cost_x<W; cost_x++) { 
            if (*(ERR_cost+cost_y*W + cost_x) <= min_cost) {
                min_temp = cost_x;
                min_cost = *(ERR_cost + cost_y*W + cost_x);
            }
        }
        for (int i=0; i<W; i++) { 
            if (i < min_temp) {
                shift_img.at<Vec3b>(cost_y, i)[0] = image1.at<Vec3b>(cost_y, i)[0];
                shift_img.at<Vec3b>(cost_y, i)[1] = image1.at<Vec3b>(cost_y, i)[1];
                shift_img.at<Vec3b>(cost_y, i)[2] = image1.at<Vec3b>(cost_y, i)[2];
            } else {
                shift_img.at<Vec3b>(cost_y, i)[0] = image2.at<Vec3b>(cost_y, i)[0];
                shift_img.at<Vec3b>(cost_y, i)[1] = image2.at<Vec3b>(cost_y, i)[1];
                shift_img.at<Vec3b>(cost_y, i)[2] = image2.at<Vec3b>(cost_y, i)[2];
            }
        }
    }
    free(ERR_cost);

    return shift_img;

}

//---------------------------------
//论文中光照补偿算法,[利用重叠区域的方差与均值分布]
//-----------------------------------
void dana_fix_Pixel(Mat  img1, Mat  img2, fix_BGR  &fix)
{
    Mat tmp_m, tmp_sd;
    Mat img = img2.clone();
    double m1[3] = {0}, sd1[3] = {0}, m2[3] = {0}, sd2[3] = {0}, m[3] = {0};
    
    meanStdDev(img1, tmp_m, tmp_sd);
    m1[0] = tmp_m.at<double>(0, 0);
    m1[1] = tmp_m.at<double>(0, 1);
    m1[2] = tmp_m.at<double>(0, 2);
    sd1[0] = tmp_sd.at<double>(0, 0);
    sd1[1] = tmp_sd.at<double>(0, 1);
    sd1[2] = tmp_sd.at<double>(0, 2);
    meanStdDev(img2, tmp_m, tmp_sd);
    m2[0] = tmp_m.at<double>(0, 0);
    m2[1] = tmp_m.at<double>(0, 1);
    m2[2] = tmp_m.at<double>(0, 2);
    sd2[0] = tmp_sd.at<double>(0, 0);
    sd2[1] = tmp_sd.at<double>(0, 1);
    sd2[2] = tmp_sd.at<double>(0, 2);
    
    int x, y;
    int temp[3];
    for(y=0; y<img2.rows; y++) {
        for(x=0; x<img2.cols; x++)
        {
            temp[0] = ((img2.at<Vec3b>(y, x)[0] - m2[0])*(sd1[0]/sd2[0]) + m1[0])<0?0:(((img2.at<Vec3b>(y, x)[0] - m2[0])*(sd1[0]/sd2[0]) + m1[0])>255?255:((img2.at<Vec3b>(y, x)[0] - m2[0])*(sd1[0]/sd2[0]) + m1[0]));
            temp[1] = ((img2.at<Vec3b>(y, x)[1] - m2[1])*(sd1[1]/sd2[1]) + m1[1])<0?0:(((img2.at<Vec3b>(y, x)[1] - m2[1])*(sd1[1]/sd2[1]) + m1[1])>255?255:((img2.at<Vec3b>(y, x)[1] - m2[1])*(sd1[1]/sd2[1]) + m1[1]));
            temp[2] = ((img2.at<Vec3b>(y, x)[2] - m2[2])*(sd1[2]/sd2[2]) + m1[2])<0?0:(((img2.at<Vec3b>(y, x)[2] - m2[2])*(sd1[2]/sd2[2]) + m1[2])>255?255:((img2.at<Vec3b>(y, x)[2] - m2[2])*(sd1[2]/sd2[2]) + m1[2]));

            img.at<Vec3b>(y, x)[0] = (unsigned char)temp[0];
            img.at<Vec3b>(y, x)[1] = (unsigned char)temp[1];
            img.at<Vec3b>(y, x)[2] = (unsigned char)temp[2];
        }
    }
    meanStdDev(img, tmp_m, tmp_sd);
    m[0] = tmp_m.at<double>(0, 0);
    m[1] = tmp_m.at<double>(0, 1);
    m[2] = tmp_m.at<double>(0, 2);
    fix.B = (int)(m[0] - m2[0]);
    fix.G = (int)(m[1] - m2[1]);
    fix.R = (int)(m[2] - m2[2]);
}

