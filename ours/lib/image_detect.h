#ifndef _image_detect_
#define _image_detect_

#include <vector>
#include <opencv2/opencv.hpp>

/*
郭政和
public:
    // 执行图像处理，分为几个步骤
    void processImage();
    // 1.hsv
    // 
        
    // 将检测出的图形的坐标转换为机器人世界坐标
    cv::Point2f convertToRobotCoordinates(const cv::Point& imagePoint);

private:
    // 图像预处理：去噪、增强等
    void preprocessImage();
        
    // 坐标转换：从图像坐标到机器人坐标
    cv::Point2f transformToRobotCoordinates(const cv::Point& imagePoint);

陈辉
private:
    // 使用聚类算法进行图形拟合
    void clusterAndFitShapes();

    // 对图像进行像素分类
    void classifyPixels();

    // 颜色分类：识别绿色、白色和其他区域
    bool isGreen(const cv::Vec3b& pixel);
    bool isWhite(const cv::Vec3b& pixel);

李周健
public:
    // 获取检测到的白色同心圆的位置(在图片坐标系的坐标)
    std::vector<cv::Point> getDetectedConcentricCircles();

    // 获取检测到的白色十字标志的位置(在图片坐标系的坐标)
    std::vector<cv::Point> getDetectedCrosses();

    // 获取图像中的白线的位置(在图片坐标系的坐标)
    std::vector<cv::Vec4i> getDetectedWhiteLines();
private:
    // 图像检测：白线检测
    void detectWhiteLines();

    // 图像检测：同心圆检测
    void detectConcentricCircles();

    // 图像检测：十字标志检测
    void detectCrosses();
*/

class RobocupFieldProcessor {
public:

    // 构造函数，接收图像路径
    RobocupFieldProcessor(const std::string& imagePath);

    // 执行图像处理，分为几个步骤
    void processImage();
    // HSV 不能用灰度图

    // 获取检测到的白色同心圆的位置(在图片坐标系的坐标)
    std::vector<cv::Point> getDetectedConcentricCircles();

    // 获取检测到的白色十字标志的位置(在图片坐标系的坐标)
    std::vector<cv::Point> getDetectedCrosses();

    // 获取图像中的白线的位置(在图片坐标系的坐标)
    std::vector<cv::Vec4i> getDetectedWhiteLines();

    // 将检测出的图形的坐标转换为机器人世界坐标
    cv::Point2f convertToRobotCoordinates(const cv::Point& imagePoint);

private:
    // 原始图像
    cv::Mat originalImage;

    // 分割后的图像（绿色区域、白色区域和其他区域）
    cv::Mat greenRegion;
    cv::Mat whiteRegion;
    cv::Mat otherRegion;

    // 存储检测到的图形
    std::vector<cv::Point> concentricCircles;
    std::vector<cv::Point> crosses;
    std::vector<cv::Vec4i> whiteLines;

    //变量请自行添加


    // 对图像进行像素分类
    void classifyPixels();

    // 使用聚类算法进行图形拟合
    void clusterAndFitShapes();
    // 1.原来的图片，画上白色的线，把圆和直线标出来 2.x-y 
    ··#··
    ·#·#·
    ··#·· 15像素块
      
      #    
    #   #
      #

    // 图像检测：白线检测
    void detectWhiteLines();

    // 图像检测：同心圆检测
    void detectConcentricCircles();

    // 图像检测：十字标志检测
    void detectCrosses();

    // 坐标转换：从图像坐标到机器人坐标
    cv::Point2f transformToRobotCoordinates(const cv::Point& imagePoint);

    // 图像预处理：去噪、增强等
    void preprocessImage();

    // 颜色分类：识别绿色、白色和其他区域
    bool isGreen(const cv::Vec3b& pixel);
    bool isWhite(const cv::Vec3b& pixel);
};

#endif