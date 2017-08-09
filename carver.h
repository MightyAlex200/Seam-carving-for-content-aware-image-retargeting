#ifndef CARVE_H
#define CARVE_H

#include <opencv/cv.hpp>

int* get_seam(cv::Mat importance_map, bool vertical);

#endif // CARVE_H