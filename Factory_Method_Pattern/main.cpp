#include <iostream>

#include "picture.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    ReadPictureFactory* readPictureFactory = new ReadGIFFactory();
    // ReadPictureFactory* readPictureFactory = new ReadJPGFactory();
    ReadPicture*        readPicture        = readPictureFactory->createReadPicture();
    readPicture->read();
    return 0;
}