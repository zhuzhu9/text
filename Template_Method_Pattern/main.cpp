#include <iostream>

class TemplateClass {
public:
    TemplateClass();
    TemplateClass(TemplateClass&&)      = default;
    TemplateClass(const TemplateClass&) = default;
    TemplateClass& operator=(TemplateClass&&) = default;
    TemplateClass& operator=(const TemplateClass&) = default;
    virtual ~TemplateClass();

    void TemplateMethod() {
        ::std::cout << "主要流程开始" << ::std::endl;
        PrimitiveOperation1();
        PrimitiveOperation2();
        ::std::cout << "主要流程结束" << ::std::endl;
    }

    virtual void PrimitiveOperation1() = 0;

    virtual void PrimitiveOperation2() = 0;
};

TemplateClass::TemplateClass() {
}

TemplateClass::~TemplateClass() {
}

class ConcreteClassA : public TemplateClass {
public:
    void PrimitiveOperation1() override {
        ::std::cout << "A1" << ::std::endl;
    }

    void PrimitiveOperation2() override {
        ::std::cout << "A2" << ::std::endl;
    }
};

class ConcreteClassB : public TemplateClass {
public:
    void PrimitiveOperation1() override {
        ::std::cout << "B1" << ::std::endl;
    }

    void PrimitiveOperation2() override {
        ::std::cout << "B2" << ::std::endl;
    }
};

int main(int argc, char* argv[]) {
    TemplateClass* a = new ConcreteClassA();
    TemplateClass* b = new ConcreteClassB();

    a->TemplateMethod();
    b->TemplateMethod();

    return 0;
}