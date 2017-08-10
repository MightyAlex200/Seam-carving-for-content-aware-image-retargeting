#ifndef CARVE_H
#define CARVE_H

#include <opencv/cv.hpp>

int* get_seam(cv::Mat importance_map, bool vertical);

cv::Mat remove_seam(int* seam, cv::Mat image, bool vertical);

cv::Mat insert_seam(int* seam, cv::Mat image, bool vertical);

#endif // CARVE_H