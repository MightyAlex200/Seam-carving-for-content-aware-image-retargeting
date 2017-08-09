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
            for(int x = 0; x < image.cols; x++) {
                for(int y = seam[x]; y < image.rows-1; y++) {
                    Vec3b& from_pixel = image.at<Vec3b>(Point(x, y));
                    Vec3b& to_pixel   = image.at<Vec3b>(Point(x, y+1));
                    from_pixel = to_pixel;
                }
            }
            Rect crop_rectangle(0, 0, image.cols, image.rows-1);
            image = image(crop_rectangle);
        } else {
            seam = get_seam(image_map, true);
            for(int x = 0; x < image.cols; x++) {
                Vec3b& from_pixel = image.at<Vec3b>(Point(x, seam[x]));
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