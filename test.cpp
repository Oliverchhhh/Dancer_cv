#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
int main() {
    // 读取图片
    cv::Mat image = cv::imread("dataset/WIN_20241119_21_18_44_Pro.jpg");

    // 检查图片是否成功加载
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }
    Vec3b sumColor(0, 0, 0);
    Vec3b sum(254, 246, 221);
    Vec3b sume(2, 3, 50);
    sumColor=sumColor+sum;
    cout<<"color"<<(int)sumColor[0]<<"xiaihg"<<(int)sumColor[1]<<"dgsj"<<(int)sumColor[2]<<endl;
    sumColor=sumColor+sume;
    cout<<"color"<<(int)sumColor[0]<<"xiaihg"<<(int)sumColor[1]<<"dgsj"<<(int)sumColor[2]<<endl;
    return 0;
}
