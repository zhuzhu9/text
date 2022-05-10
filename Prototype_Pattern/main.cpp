#include <iostream>

class Customer {
private:
    int* m_ptr;

public:
    Customer() = default;
    Customer(int num) : m_ptr(new int(num)) {
    }
    Customer(const Customer& c) noexcept {
        m_ptr  = new int;
        *m_ptr = *(c.m_ptr);
    }
    Customer(Customer&& c) noexcept : m_ptr(c.m_ptr) {
        c.m_ptr = nullptr;
    }
    ~Customer() {
        if (m_ptr != nullptr) {
            delete m_ptr;
        }
        m_ptr = nullptr;
    }
    void print() {
        std::cout << *m_ptr << std::endl;
    }
};

Customer getCustomer() {
    Customer a(2);
    return a;
}

int main(int argc, char* argv[]) {
    Customer c1 = getCustomer();

    c1.print();

    return 0;
}