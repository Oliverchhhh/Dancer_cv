#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

// 滑块的大小
const int SLIDER_SIZE = 5;

// 使用 K-means 聚类分割图像
void kmeansSegmentation(Mat& img, int clusters) {
    // 将图像数据转换为一个一维向量
    Mat imgData = img.reshape(1, img.rows * img.cols);
    imgData.convertTo(imgData, CV_32F);  // 转换为 float 类型

    // 进行 K-means 聚类
    Mat labels, centers;
    kmeans(imgData, clusters, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 100, 0.2), 10, KMEANS_PP_CENTERS, centers);

    // 将聚类中心转换为 Vec3b 类型
    centers.convertTo(centers, CV_8U);

    // 将聚类结果应用到原图像
    Mat segmentedImg = img.clone();
    for (int i = 0; i < img.rows * img.cols; i++) {
        int clusterIdx = labels.at<int>(i);
        // 获取聚类中心，并转换为 Vec3b
        Vec3b color(centers.at<float>(clusterIdx, 0), centers.at<float>(clusterIdx, 1), centers.at<float>(clusterIdx, 2));
        segmentedImg.at<Vec3b>(i / img.cols, i % img.cols) = color;
    }

    // // 显示聚类后的结果
    // imshow("K-means Segmentation", segmentedImg);
    // 另存聚类后的结果
    imwrite("segmented_image4.jpg", segmentedImg);
    

    // waitKey(0);
}

// 计算滑块区域的平均颜色
Vec3b calculateAverageColor(const Mat& img, int x, int y, int sliderSize) {
    // 确保滑块不会越界
    int startX = x;
    int startY = y;
    int endX = min(img.cols, x + sliderSize);
    int endY = min(img.rows, y + sliderSize);
    int B=0,G=0,R=0;

    int count = 0;

    for (int i = startY; i < endY; i++) {
        for (int j = startX; j < endX; j++) {
            // sumColor += img.at<Vec3b>(i, j);  // 累加 RGB 颜色
            B+=img.at<Vec3b>(i, j)[0];
            G+=img.at<Vec3b>(i, j)[1];
            R+=img.at<Vec3b>(i, j)[2];
            cout<<"color"<<B<<"xiaihg"<<G<<"dgsj"<<R<<endl;
            count++;
        }
    }
    
    // 绿色条件
    if (G > 100 && R < 70 && B < 70) {
        return cv::Vec3b(0, 255, 0); // 绿色
    }
    // 白色条件
    else if (abs(R - G) < 50 && abs(G - B) < 50 && R > 100 && G > 100 && B > 100) {
        return cv::Vec3b(255, 255, 255); // 白色
    }
    // 其他颜色
    else {
        return cv::Vec3b(0, 0, 0); // 其他颜色 (黑色)
    }
    // return Vec3b(B / count, G / count, R / count);
}

// 遍历图像使用滑块计算颜色，并进行聚类
void processImage(const Mat& img, int clusters) {
    Mat result = img.clone();
    for (int y = 0; y < img.rows; y += SLIDER_SIZE) {
        for (int x = 0; x < img.cols; x += SLIDER_SIZE) {
            // 计算滑块区域的平均颜色
            Vec3b avgColor = calculateAverageColor(img, x, y, SLIDER_SIZE);

            // 设置滑块区域的颜色为平均颜色
            for (int i = y; i < min(y + SLIDER_SIZE, img.rows); i++) {
                for (int j = x; j < min(x + SLIDER_SIZE, img.cols); j++) {
                    result.at<Vec3b>(i, j) = avgColor;
                }
            }
        }
    }

    // 显示结果图像
    // imshow("Processed Image", result);
    imwrite("Processed_image4.jpg", result);

    // waitKey(0);

    // 使用 K-means 进行聚类分割
    kmeansSegmentation(result, clusters);
}

int main(int argc, char** argv) {
    // 加载图像
    string imagePath = "dataset/WIN_20241119_21_18_53_Pro.jpg";  // 图像路径
    Mat img = imread(imagePath);
    imshow("IMAGE", img);
    waitKey(0);
    if (img.empty()) {
        cout << "Error loading image!" << endl;
        return -1;
    }

    // 处理图像：设置聚类数量为5
    processImage(img, 5);

    return 0;
}
