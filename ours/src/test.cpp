#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // 指定图片路径
    string path = "dataset/WIN_20241119_21_18_48_Pro.jpg";
    cv::Mat img = imread(path);  // 读取图像

    // 显示图像
    imshow("Display Image", img);
    // imshow("Display Image", test);

    // 等待按键按下，关闭窗口
    waitKey(0);

    return 0;
}
