#include <iostream>

class ReadPicture {
public:
    virtual void read() = 0;
};

class ReadGIF : public ReadPicture {
public:
    void read() {
        std::cout << "Reading a GIF file" << std::endl;
    }
};

class ReadJPG : public ReadPicture {
public:
    void read() {
        std::cout << "Reading a JPG file" << std::endl;
    }
};

class ReadPictureFactory {
public:
    virtual ReadPicture* createReadPicture() = 0;
};

class ReadGIFFactory : public ReadPictureFactory {
public:
    virtual ReadPicture* createReadPicture() {
        ReadPicture* readPicture = new ReadGIF();
        return readPicture;
    }
};

class ReadJPGFactory : public ReadPictureFactory {
    public:
    virtual ReadPicture* createReadPicture() {
        ReadPicture* readPicture = new ReadJPG();
        return readPicture;
    }
};