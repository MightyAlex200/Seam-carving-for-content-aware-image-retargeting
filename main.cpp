#include <iostream>
#include <opencv/cv.hpp>
#include "sobel.h"
#include "carver.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    if(argc != 3 && argc != 2) {
        cout << "Error: Incorrect amount of arguments.\nUsage: carve <image> [vertical]" << endl;
        return 1;
    }

    bool vertical = false;

    if(argc == 3) {
        if(string(argv[2]) == "vertical") {
            vertical = true;
        }
    }

    char* image_name = argv[1];

    Mat image = imread(image_name);

    if(!image.data) {
        cout << "Unable to read image data" << endl;
        return 2;
    }

    bool remove = false;
    int* seam;

    while(image.rows > 1 && image.cols > 1) {
        Mat image_map = sobel(image);

        if(remove) {
            image = remove_seam(seam, image, vertical);
        } else {
            seam = get_seam(image_map, vertical);
            
            const int main_axis_length = vertical ? image.rows : image.cols;
            const int alt_axis_length  = vertical ? image.cols : image.rows;

            for(int alt_axis = 0; alt_axis < alt_axis_length; alt_axis++) {
                Vec3b& from_pixel = vertical ? 
                    image.at<Vec3b>(Point(alt_axis, seam[alt_axis])) :
                    image.at<Vec3b>(Point(seam[alt_axis], alt_axis));
                from_pixel[2] = 255;
                from_pixel[1] = 0;
                from_pixel[0] = 0;
            }
        }

        imshow("Seam carving for content aware image retargeting", image);
        waitKey(1);

        remove = !remove;
    }

    return 0;
}