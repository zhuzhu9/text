#include <iostream>

#include "airplane.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    {
        plane* plane1 = new helicopter("helicpoter1");
        plane1->fly();

        plane* plane2 = new airPlane("airPlane1");
        plane2->fly();

        plane* plane3 = new fighter("fighter1");
        plane3->fly();

        plane* plane4 = new harrier("harrier");
        plane4->fly();
    }

    return 0;
}