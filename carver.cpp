#include <stdlib.h>
#include <opencv/cv.hpp>

using namespace cv;

int* get_seam(Mat importance_map, bool vertical) {
    const int main_axis_length = vertical ? importance_map.rows : importance_map.cols;
    const int alt_axis_length  = vertical ? importance_map.cols : importance_map.rows;
    
    int* r_coords = NULL;
    uint last_sum = -1;
    
    for(int main_axis = 0; main_axis < main_axis_length; main_axis++) {
        int mutable_main_axis = main_axis;
        int sum = 0;
        int* coords = (int*)calloc(alt_axis_length, sizeof(int));
        
        // Go down the alt_axis with the path of least resistance
        for(int alt_axis = 0; alt_axis < alt_axis_length; alt_axis++) {
            coords[alt_axis] = mutable_main_axis;
            uint8_t default_opt = vertical ? 
                importance_map.at<uint8_t>(Point(alt_axis, mutable_main_axis)):
                importance_map.at<uint8_t>(Point(mutable_main_axis, alt_axis));
            uint8_t higher_opt = vertical ? 
                importance_map.at<uint8_t>(Point(alt_axis, mutable_main_axis+1)):
                importance_map.at<uint8_t>(Point(mutable_main_axis+1, alt_axis));
            uint8_t lower_opt = vertical ? 
                importance_map.at<uint8_t>(Point(alt_axis, mutable_main_axis-1)):
                importance_map.at<uint8_t>(Point(mutable_main_axis-1, alt_axis));
            if(higher_opt < lower_opt && higher_opt < default_opt && mutable_main_axis != main_axis_length - 1) {
                mutable_main_axis++;
                sum += higher_opt;
            } else if(lower_opt < higher_opt && lower_opt < default_opt && mutable_main_axis != 0) {
                mutable_main_axis--;
                sum += lower_opt;
            } else {
                sum += default_opt;
            }
        }

        if(sum < last_sum) {
            r_coords = coords;
            last_sum = sum;
        } else {
            free(coords);
        } 
    }

    return r_coords;
}

Mat remove_seam(int* seam, Mat image, bool vertical) {
    const int main_axis_length = vertical ? image.rows : image.cols;
    const int alt_axis_length  = vertical ? image.cols : image.rows;

    Mat rMat = *new Mat();

    for(int alt_axis = 0; alt_axis < alt_axis_length; alt_axis++) {
        for(int main_axis = seam[alt_axis]; main_axis < main_axis_length-1; main_axis++) {
            Vec3b& from_pixel = vertical ?
                image.at<Vec3b>(Point(alt_axis, main_axis)) :
                image.at<Vec3b>(Point(main_axis, alt_axis));
            Vec3b& to_pixel = vertical ?
                image.at<Vec3b>(Point(alt_axis, main_axis+1)) :
                image.at<Vec3b>(Point(main_axis+1, alt_axis));
            from_pixel = to_pixel;
        }
    }

    Rect crop_rectangle(0, 0, image.cols-!vertical, image.rows-vertical);
    rMat = image(crop_rectangle);
    
    return rMat;
}