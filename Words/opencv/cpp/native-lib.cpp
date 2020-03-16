#include <jni.h>
#include <string>

#include "include/dana_panorama.h"
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_ERROR, "dana_panorama", x)
dana_pano_info *pano;

extern "C"
JNIEXPORT void JNICALL
Java_com_nel_panorama_PanoManager_init(JNIEnv *env, jclass type) {
//    D("Java_com_nel_panorama_PanoManager_init start ......");

    // TODO
//    double cameraMat[3][3] = {{1086.824276893329 / 2, 0,                     960},//C314横屏参数
//                              {0,                     1086.824276893329 / 2, 520},
//                              {0,                     0,                     1}};//1920x1080的camera坐标参数
//    double cameraMat[3][3] = {{1926.824276893329 /2, 0,                     960},
//                              {0,                     1086.824276893329 / 2, 520},
//                              {0,                     0,                     1}};//1920x1080的camera坐标参数
    double cameraMat[3][3] = {{1086.824276893329 /2, 0,                     960},
                              {0,                     1086.824276893329/2 , 520},//carema
                              {0,                     0,                     1}};//1920x1080的camera坐标参数
    //k1:正数以中心点为轴水平畸变为凸面，负数凹面 k2:正数以中心点为轴水平畸变为凸面，负数凹面
    // p1:纵向拉伸 p2:水平拉伸 k3:水平弯曲
//    double dist[5] =   {-0.000000603134787144, 0.00040400320554751, 0.016200000134787144,0.006039177460954e-005, -0.0000060000000001};//竖直方向弯曲导致bottom黑边
//      double dist[5] =  {-0.009000003134787144, 0.00040400320554751, 0.016200000134787144,0.006039177460954e-005, -0.0000060000000001};//图片融合处模糊
      double dist[5] =  {-0.009000003134787144, 0.00060400320554751, 0.016200000134787144,0.006039177460954e-005, -0.0000060000000001};
    //2：图片拼接融合算法，提取图片特征点和融合区域算法有区别 1920：需要拼接的单张图片宽，950：需要拼接的单张图片高
        pano = nullptr ;
        pano = dana_pano_info_create(0, (dana_blending_mode_t) 2, cameraMat, dist, 1920, 950);
//    pano = dana_pano_info_create(0, (dana_blending_mode_t) 2, cameraMat, dist, 1920/2, 1080/2-65);//2倍
//    pano = dana_pano_info_create(0, (dana_blending_mode_t) 2, cameraMat, dist, 1920/4, 1080/4-15);//4倍
//    pano = dana_pano_info_create(0, (dana_blending_mode_t) 2, cameraMat, dist, 1920/8, 1080/8-8);//8倍


    /*   double cameraMat[3][3] = {{1086.824276893329 / 2, 0,                 *//*    270},//H1竖屏参数
                              {0,                     1086.824276893329 / 2, 540},
                              {0,                     0,                     1}};
    double dist[5] = {-0.4177642150313481, 0.2237463754008228, 0, 0, -0.0716236427291802};
    pano = dana_pano_info_create(0, (dana_blending_mode_t) 2, cameraMat, dist, 540, 960);*/

}

void process(const char *filename, bool isFistFile) {
//    D("process start ......");
    Mat img = imread(filename, 1);
	Mat newImg;
   // resize(img,newImg,Size(540,960),0,0,INTER_LINEAR);
   // resize(img,newImg,Size(1920,1080),0,0,INTER_LINEAR);// 参数：原图 输出图 输出图大小 x比例 y比例 放大INTER_LINEAR 缩小INTER_AREA
    resize(img,newImg,Size(1920,1080),0,0,INTER_LINEAR);
//    D("isFistFile : %d ",isFistFile);
    if (isFistFile) {
        dana_pano_process(pano, newImg, 1);
    } else {
        dana_pano_process(pano, newImg, 0);
    }
    img.release();
    newImg.release();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_nel_panorama_PanoManager_process(JNIEnv *env, jclass type, jstring filename_,
                                        jboolean isFistFile) {
    const char *filename = env->GetStringUTFChars(filename_, 0);
    process(filename, isFistFile);
    // TODO

}

extern "C"
JNIEXPORT void JNICALL
Java_com_nel_panorama_PanoManager_destroy(JNIEnv *env, jclass type, jstring des_) {
    const char *des = env->GetStringUTFChars(des_, 0);
    // TODO
    imwrite(des, pano->outimg);
    pano->outimg.release();
    dana_pano_info_destroy(pano);
    //delete pano;
}