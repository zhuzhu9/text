#include <iostream>

class Component {
public:
    virtual void show(){};
};

class Decorator : public Component {
private:
    Component* comp;

public:
    Decorator(Component* c) : comp(c) {
    }

    void show() {
        comp->show();
    }
};

class AJiami : public Component {
public:
    void show() {
        std::cout << "is a jiami" << std::endl;
    }
};

class jiami1 : public Decorator {
public:
    jiami1(Component* c) : Decorator(c) {
    }
    void show() {
        Decorator::show();
        std::cout << "jiami1" << std::endl;
    }
};

class jiami2 : public Decorator {
public:
    jiami2(Component* c) : Decorator(c) {
    }
    void show() {
        Decorator::show();
        std::cout << "jiami2" << std::endl;
    }
};

class jiami3 : public Decorator {
public:
    jiami3(Component* c) : Decorator(c) {
    }
    void show() {
        Decorator::show();
        std::cout << "jiami3" << std::endl;
    }
};