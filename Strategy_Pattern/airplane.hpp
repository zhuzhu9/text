#include <iostream>

using namespace std;

class TakeOff {
public:
    virtual void takeOff() = 0;
};

class verticalTakeOff : public TakeOff {
public:
    virtual void takeOff() {
        cout << "Vertical TakeOff" << endl;
    }
};

class longDistanceTakeOff : public TakeOff {
public:
    virtual void takeOff() {
        cout << "Long Distance TakeOff" << endl;
    }
};

class Fly {
public:
    virtual void fly() = 0;
};

class subSonicFly : public Fly {
public:
    virtual void fly() {
        cout << "SubSonic Fly" << endl;
    }
};

class superSonicFly : public Fly {
public:
    virtual void fly() {
        cout << "SuperSonic Fly" << endl;
    }
};

class plane {
protected:
    TakeOff* takeoff;
    Fly*     flyType;
    string   name;

public:
    plane(TakeOff* takeoff, Fly* flyType, string name) {
        this->takeoff = takeoff;
        this->flyType = flyType;
        this->name    = name;
    }

    void fly() {
        show();
        takeoff->takeOff();
        flyType->fly();
    }

    virtual ~plane() {
        delete takeoff;
        delete flyType;
    }

    virtual void show() = 0;
};

class helicopter : public plane {
public:
    helicopter(string name) : plane(new verticalTakeOff(), new subSonicFly(), name) {
    }
    void show() {
        cout << "Helicopter: " << name << endl;
    }
};

class airPlane : public plane {
public:
    airPlane(string name) : plane(new longDistanceTakeOff(), new superSonicFly(), name) {
    }
    void show() {
        cout << "AirPlane: " << name << endl;
    }
};

class fighter : public plane {
public:
    fighter(string name) : plane(new longDistanceTakeOff(), new superSonicFly(), name) {
    }
    void show() {
        cout << "Fighter: " << name << endl;
    }
};

class harrier : public plane {
public:
    harrier(string name) : plane(new verticalTakeOff(), new superSonicFly(), name) {
    }
    void show() {
        cout << "Harrier: " << name << endl;
    }
};