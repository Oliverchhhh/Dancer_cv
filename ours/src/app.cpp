#include "image_detect.h"


// 预处理图像，去噪、调整等
void RobocupFieldProcessor::preprocessImage() {
    cv::cvtColor(originalImage, originalImage, cv::COLOR_BGR2GRAY);  // 转为灰度图
    // 可以在这里添加滤波、对比度增强等步骤
}

// 像素分类，将图像分为绿色、白色和其他区域
void RobocupFieldProcessor::classifyPixels() {
    greenRegion = cv::Mat::zeros(originalImage.size(), CV_8UC1);
    whiteRegion = cv::Mat::zeros(originalImage.size(), CV_8UC1);
    otherRegion = cv::Mat::zeros(originalImage.size(), CV_8UC1);

    for (int y = 0; y < originalImage.rows; y++) {
        for (int x = 0; x < originalImage.cols; x++) {
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
            if (isGreen(pixel)) {
                greenRegion.at<uchar>(y, x) = 255;
            } else if (isWhite(pixel)) {
                whiteRegion.at<uchar>(y, x) = 255;
            } else {
                otherRegion.at<uchar>(y, x) = 255;
            }
        }
    }
}

// 判断像素是否为绿色
bool RobocupFieldProcessor::isGreen(const cv::Vec3b& pixel) {
    return (pixel[1] > 100 && pixel[0] < 50 && pixel[2] < 50);  // 简单的绿色判断条件
}

// 判断像素是否为白色
bool RobocupFieldProcessor::isWhite(const cv::Vec3b& pixel) {
    return (pixel[0] > 200 && pixel[1] > 200 && pixel[2] > 200);  // 简单的白色判断条件
}

// 使用聚类算法拟合图形（可扩展为更多图形检测）
void RobocupFieldProcessor::clusterAndFitShapes() {
    // 这里可以用KMeans等方法对图像区域进行聚类，以识别图形
}

// 检测白线
void RobocupFieldProcessor::detectWhiteLines() {
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(whiteRegion, lines, 1, CV_PI / 180, 50, 50, 10);  // 霍夫变换检测直线
    whiteLines = lines;
}

// 检测白色同心圆
void RobocupFieldProcessor::detectConcentricCircles() {
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(whiteRegion, circles, cv::HOUGH_GRADIENT, 1, whiteRegion.rows / 8, 100, 30, 10, 300);
    for (auto& circle : circles) {
        concentricCircles.push_back(cv::Point(circle[0], circle[1]));  // 圆心坐标
    }
}

// 检测十字标志
void RobocupFieldProcessor::detectCrosses() {
    // 基于形态学处理或模板匹配等方法检测十字形标志
}

// 坐标转换：将图像坐标转换为机器人世界坐标
cv::Point2f RobocupFieldProcessor::convertToRobotCoordinates(const cv::Point& imagePoint) {
    return transformToRobotCoordinates(imagePoint);
}

// 实际坐标转换实现
cv::Point2f RobocupFieldProcessor::transformToRobotCoordinates(const cv::Point& imagePoint) {
    // 根据机器人坐标系的定义，进行转换（此部分需要根据具体的场地和相机标定信息进行调整）
    // 示例：假设图像左上角为原点，单位转换等
    float robotX = imagePoint.x * 0.01;  // 简单的缩放示例
    float robotY = imagePoint.y * 0.01;
    return cv::Point2f(robotX, robotY);
}

