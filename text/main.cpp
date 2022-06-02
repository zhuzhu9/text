#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "config.h"
#include "staff.hpp"

using ::std::cout;
using ::std::ifstream;
using ::std::string;
using ::std::stringstream;

Oper a;

class Account {
private:
    ::std::map<string, string> m_manager_account;
    ::std::map<string, string> m_cook_account;

public:
    Account() {
        {
            ifstream ifs(PATH "manager.data");
            string   line;
            while (getline(ifs, line)) {
                stringstream ss(line);
                string       name, password;
                ss >> name >> password;
                m_manager_account.emplace(::std::make_pair(name, password));
            }
            ifs.close();
        }
        {
            ifstream ifs(PATH "cook.data");
            string   line;
            while (getline(ifs, line)) {
                stringstream ss(line);
                string       name, password;
                ss >> name >> password;
                m_cook_account.emplace(::std::make_pair(name, password));
            }
            ifs.close();
        }
    }

    Manager::StaffType login(string name, string password) {
        if (m_manager_account.find(name) != m_manager_account.end()) {
            if (m_manager_account[name] == password) {
                a.set_login(true);
                return Manager::StaffType::Manager;
            }
        } else if (m_cook_account.find(name) != m_cook_account.end()) {
            if (m_cook_account[name] == password) {
                a.set_login(true);
                return Manager::StaffType::Cook;
            }
        }

        a.set_login(false);
        return Manager::StaffType::Guest;
    }
};

int main(int argc, char* argv[]) {
    Account account;

    ::std::cout << "Hello!" << ::std::endl;
    ::std::cout << "****************************" << ::std::endl;
    ::std::cout << "欢迎使用员工管理系统" << ::std::endl;
    ::std::cout << "****************************" << ::std::endl;
    char step = 0;

    while (1) {
        ::std::cout << "请选择操作：" << ::std::endl;
        ::std::cout << "****************************" << ::std::endl;
        ::std::cout << "0:员工登录" << ::std::endl;
        ::std::cout << "1:查看菜单" << ::std::endl;
        ::std::cout << "2:增加菜单" << ::std::endl;
        ::std::cout << "3:删除菜单" << ::std::endl;
        ::std::cout << "4:查看原材料" << ::std::endl;
        ::std::cout << "5:增加原材料" << ::std::endl;
        ::std::cout << "6:修改原材料" << ::std::endl;
        ::std::cout << "7:删除原材料" << ::std::endl;
        ::std::cout << "8:查看订单" << ::std::endl;
        ::std::cout << "9:添加订单" << ::std::endl;
        ::std::cout << "x:退出系统" << ::std::endl;
        ::std::cout << "****************************" << ::std::endl;

        step = ::std::getchar();
        ::std::cin.clear();
        switch (step) {
            case '0': {
                string name;
                string password;
                ::std::cout << "****************************" << ::std::endl;
                ::std::cout << "请输入用户名：" << ::std::endl;
                ::std::cout << "****************************" << ::std::endl;
                ::std::cin >> name;
                ::std::cout << "****************************" << ::std::endl;
                ::std::cout << "请输入密码：" << ::std::endl;
                ::std::cout << "****************************" << ::std::endl;
                ::std::cin >> password;
                ::std::cin.clear();
                ::std::cout << "****************************" << ::std::endl;
                switch (account.login(name, password)) {
                    case Manager::StaffType::Manager:
                        a.set_position(Manager::StaffType::Manager);
                        break;
                    case Manager::StaffType::Cook:
                        a.set_position(Manager::StaffType::Cook);
                        break;
                    case Manager::StaffType::Guest:
                        a.set_position(Manager::StaffType::Guest);

                        ::std::cout << "****************************" << ::std::endl;
                        ::std::cout << "用户名或密码错误！" << ::std::endl;
                        ::std::cout << "****************************" << ::std::endl;
                        break;
                    default:
                        break;
                }
            } break;

            case '1': {
                a.getStaff()->showMenu();
            } break;

            case '2': {
                a.getStaff()->addMenu();
                ::std::cin.clear();
            } break;

            case '3': {
                ::std::string menuName;
                ::std::cout << "****************************" << ::std::endl;
                ::std::cout << "请输入要删除的菜单名：" << ::std::endl;
                ::std::cin >> menuName;
                ::std::cin.clear();
                a.getStaff()->deleteMenu(menuName);
            } break;

            case '4':
                a.getStaff()->showIngredients();
                break;

            case '5': {
                string ingredientName;
                int    ingredientPrice;
                ::std::cout << "请输入原材料名称：" << ::std::endl;
                ::std::cin >> ingredientName;
                ::std::cout << "请输入原材料价格：" << ::std::endl;
                ::std::cin >> ingredientPrice;
                ::std::cin.clear();
                a.getStaff()->addIngredient(ingredientName, ingredientPrice);
            } break;

            case '6': {
                string ingredientName;
                int    ingredientPrice;
                ::std::cout << "请输入原材料名称：" << ::std::endl;
                ::std::cin >> ingredientName;
                ::std::cout << "请输入原材料新的价格：" << ::std::endl;
                ::std::cin >> ingredientPrice;
                ::std::cin.clear();
                if (a.getStaff()->changeIngredientPrice(ingredientName, ingredientPrice)) {
                    ::std::cout << "修改成功！" << ::std::endl;
                } else {
                    ::std::cout << "修改失败！" << ::std::endl;
                }
            } break;

            case '7': {
                string ingredientName;
                ::std::cout << "请输入原材料名称：" << ::std::endl;
                ::std::cin >> ingredientName;
                ::std::cin.clear();
                if (a.getStaff()->deleteIngredient(ingredientName)) {
                    ::std::cout << "修改成功！" << ::std::endl;
                } else {
                    ::std::cout << "修改失败！" << ::std::endl;
                }
            } break;

            case '8':
                break;

            case '9':
                break;

            case 'x':
                return 0;

            default:
                break;
        }

        ::std::cout << "按回车键继续" << ::std::endl;
        ::std::getchar();
        ::std::cin.clear();
    }

    return 0;
}