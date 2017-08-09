#include <opencv/cv.hpp>

using namespace cv;

Mat sobel(Mat src) {
    Mat src_gray;
    Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    cvtColor(src, src_gray, CV_BGR2GRAY);
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    return grad;
}