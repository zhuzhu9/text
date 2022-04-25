#include <iostream>

using namespace std;

class Image {
public:
    virtual void display() = 0;
};

class RealImage : public Image {
public:
    string m_name;
    RealImage(string str) : m_name(str) {
        cout << "Image" << m_name << " is opening." << endl;
    }
    void display() override {
        cout << "display " << m_name << endl;
    }
};

class ProxyImage : public Image {
private:
    RealImage* m_image;

public:
    string m_name;
    ProxyImage(string str) : m_name(str) {
    }
    void display() override {
        if (m_image == nullptr) m_image = new RealImage(m_name);
        m_image->display();
    }
};

int main(int argc, char* argv[]) {
    ProxyImage* image = new ProxyImage("test");
    image->display();

    image->display();
    return 0;
}