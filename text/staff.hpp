#pragma once
#include <iostream>

#include "dish.hpp"
#include "ingredients.hpp"
#include "menu.hpp"

class AbstractStaff {
public:
    virtual bool addIngredient(::std::string name, int price)                  = 0;
    virtual void showIngredients()                                             = 0;
    virtual bool changeIngredientPrice(::std::string ingredient, int newPrice) = 0;
    virtual bool deleteIngredient(::std::string ingredientName)                = 0;
    virtual int  getIngredient(::std::string ingredientName)                   = 0;
    virtual bool addMenu()                                                     = 0;
    virtual void showMenu()                                                    = 0;
    virtual bool deleteMenu(::std::string menuName)                            = 0;
    virtual ~AbstractStaff() {
    }
};

class Staff : public AbstractStaff {
public:
    void showMenu() override {
        Menu::getInstance()->showMenu();
    }
    bool addIngredient(::std::string name, int price) override {
        Ingredients::getInstance()->addIngredients(name, price);
        return true;
    }

    void showIngredients() override {
        Ingredients::getInstance()->showIngredients();
    }
    bool changeIngredientPrice(::std::string ingredient, int newPrice) override {
        return Ingredients::getInstance()->changeIngredientPrice(ingredient, newPrice);
    }

    bool deleteIngredient(::std::string ingredientName) override {
        return Ingredients::getInstance()->deleteIngredient(ingredientName);
    }

    int getIngredient(::std::string ingredientName) override {
        return Ingredients::getInstance()->getPrice(ingredientName);
    }
    bool addMenu() override {
        ::std::string dishName;
        ::std::cout << "请输入菜名: ";
        ::std::cin >> dishName;
        ::std::vector<::std::string> ingredients;
        ::std::string                ingredient;
        ::std::cout << "请输入食材: (输入\"end\"结束) ";
        while (::std::cin >> ingredient && ingredient != "end") {
            ingredients.push_back(ingredient);
        }
        int price;
        ::std::cout << "请输入菜品价格: ";
        ::std::cin >> price;
        return Menu::getInstance()->addDish(Dish(dishName, ingredients, price));
    }
    bool deleteMenu(::std::string menuName) override {
        return Menu::getInstance()->deleteDish(menuName);
    }
};

class StaffProxy : public AbstractStaff {
private:
    AbstractStaff* m_staff;
    ::std::string  m_position;

public:
    explicit StaffProxy(::std::string position) noexcept : m_position(position) {
        m_staff = new Staff();
    }
    ~StaffProxy() {
        delete m_staff;
    }

    int getIngredient(::std::string ingredientName) override {
        if (m_position == "经理") {
            return m_staff->getIngredient(ingredientName);
        } else if (m_position == "厨师") {
            return m_staff->getIngredient(ingredientName);
        } else {
            ::std::cout << "您没有权限查询食材" << ::std::endl;
            return -1;
        }
    }
    bool addIngredient(::std::string name, int price) override {
        if (m_position == "经理") {
            return m_staff->addIngredient(name, price);
        } else {
            ::std::cout << "您没有权限添加食材" << ::std::endl;
            return false;
        }
    }

    void showIngredients() override {
        if (m_position == "经理") {
            m_staff->showIngredients();
        } else if (m_position == "厨师") {
            return m_staff->showIngredients();
        } else {
            ::std::cout << "您没有权限查看食材" << ::std::endl;
            return;
        }
    }

    bool changeIngredientPrice(::std::string ingredient, int newPrice) override {
        if (m_position == "经理") {
            return m_staff->changeIngredientPrice(ingredient, newPrice);
        } else if (m_position == "厨师") {
            return m_staff->changeIngredientPrice(ingredient, newPrice);
        } else {
            ::std::cout << "您没有权限查看食材" << ::std::endl;
            return false;
        }
    }

    bool deleteIngredient(::std::string ingredientName) override {
        if (m_position == "经理") {
            return m_staff->deleteIngredient(ingredientName);
        } else {
            ::std::cout << "您没有权限删除食材" << ::std::endl;
            return false;
        }
    }

    bool addMenu() override {
        if (m_position == "经理") {
            return m_staff->addMenu();
        } else if (m_position == "厨师") {
            return m_staff->addMenu();
        } else {
            ::std::cout << "您没有权限添加菜单" << ::std::endl;
            return false;
        }
    }

    void showMenu() override {
        return m_staff->showMenu();
    }

    bool deleteMenu(::std::string menuName) override {
        if (m_position == "经理") {
            return m_staff->deleteMenu(menuName);
        } else if (m_position == "厨师") {
            return m_staff->deleteMenu(menuName);
        } else {
            ::std::cout << "您没有权限删除菜单" << ::std::endl;
            return false;
        }
    }
};

class Manager {
public:
    enum class StaffType {
        Manager,
        Cook,
        Customer,
        Guest,  //游客
    };

public:
    explicit Manager() : m_manager(new StaffProxy("经理")), m_cook(new StaffProxy("厨师")), m_customer_count(0) {
    }

    StaffProxy* getStaff(StaffType type) {
        // ::std::cout << "type" << (int)type << ::std::endl;
        if (type == StaffType::Manager) {
            return m_manager;
        } else if (type == StaffType::Cook) {
            return m_cook;
        } else if (type == StaffType::Customer) {
            StaffProxy* customer = new StaffProxy("顾客");
            ++m_customer_count;
            m_customer.emplace(::std::make_pair(m_customer_count, customer));
            return customer;
        }
        return nullptr;
    }

    // Customer* getCustomer(int customerId) {
    //     auto it = m_customer.find(customerId);
    //     if (it == m_customer.end()) {
    //         Customer* customer = new Customer();
    //         ++m_customer_count;
    //         m_customer.emplace(::std::make_pair(m_customer_count, customer));
    //         return m_customer.find(m_customer_count)->second;
    //     }
    //     return it->second;
    // }

    // Customer* getCustomer() {
    //     Customer* customer = new Customer();
    //     ++m_customer_count;
    //     m_customer.emplace(::std::make_pair(m_customer_count, customer));
    //     return m_customer.find(m_customer_count)->second;
    // }

    ~Manager() {
        delete m_manager;
        delete m_cook;
        for (auto it = m_customer.begin(); it != m_customer.end(); ++it) {
            delete it->second;
        }
    }

private:
    StaffProxy*             m_manager;
    StaffProxy*             m_cook;
    ::std::map<int, StaffProxy*> m_customer;
    int                     m_customer_count;
};

class Oper {
public:
    explicit Oper() : m_manager(Manager()), m_position(Manager::StaffType::Customer), m_is_login(false) {
    }

    bool is_login() {
        return m_is_login;
    }

    void set_login(bool is_login) {
        m_is_login = is_login;
    }

    void set_position(Manager::StaffType position) {
        m_position = position;
    }

    StaffProxy* getStaff() {
        return m_manager.getStaff(m_position);
    }

    // Customer* getCustomer(int customerId) {
    //     return m_manager.getCustomer(customerId);
    // }

    // Customer* getCustomer() {
    //     return m_manager.getCustomer();
    // }

private:
    Manager            m_manager;
    Manager::StaffType m_position;
    bool               m_is_login;
};