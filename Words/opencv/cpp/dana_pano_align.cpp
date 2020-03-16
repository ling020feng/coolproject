#include "include/dana_panorama.h"
#include "include/dana_pano_align.h"
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_ERROR, "dana_panorama", x)
//三星论文中 two-align最后一步的对齐,主要解决水平方向上的对齐
int dana_temp_match_x(Mat source, Mat temp)
{ 
    Mat image_matched;
//    D("source W: %d ,source H: %d ,temp W: %d,temp H: %d ",source.cols,source.rows,temp.cols,temp.rows);
//    D("source :%d,temp : %d ",source.step[0],temp.step[0],temp.size);
//    D("matchTemplate pre.....");//会内存泄漏
    cv::matchTemplate(source, temp, image_matched, cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
//    D("matchTemplate last.....");

    cv::Point minLoc, maxLoc;
    //寻找x坐标上最佳匹配位置
    cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);
//    D("minMaxLoc last.....");

    image_matched.release();
    return maxLoc.x;
}
