# Implementation of seam carving for content aware image retargeting in C++

[GitHub link](https://github.com/MightyAlex200/Seam-carving-for-content-aware-image-retargeting/tree/master)

This is a simple implementation of [seam carving](https://www.youtube.com/watch?v=6NcIJXTlugc) in C++. It requires [OpenCV](http://opencv.org/). [Here](https://youtu.be/8Mj0ztTIdMY) is a video of the program in action.

## Usage
The application takes 1 mandatory argument and 1 optional argument: `<image> [vertical]`. An example of proper usage would be `./carve testimage.png` or `./carve testimage3.png vertical`.

## Compiling
The Makefile should be able to compile everything for you provided you have `g++`, `pkg-config`, and OpenCV installed and correctly configured. Simply run `make` to compile everything into a binary named `carver`. To clean the generated files, type `make clean`

## License
This software is licensed under the LGPLv3. See `LICENSE` for more information.