#include <iostream>

#include "jiami.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Component* a = new AJiami();
    Component* b = new jiami1(a);

    b->show();

    Component* c = new jiami2(b);
    c->show();

    return 0;
}