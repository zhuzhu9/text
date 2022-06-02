#pragma once
#include <map>

#include "dish.hpp"

class Menu {
private:
    ::std::map<int, Dish> m_dish;
    int                   m_count = 0;
    static Menu*          m_menu;

    void saveToFile() {
        ::std::ofstream ofs(PATH "menu.data");
        for (auto& i : m_dish) {
            ofs << i.second.getName() << " ";
            for (auto& j : i.second.getIngredients()) {
                ofs << j << " ";
            }
            ofs << "# " << i.second.getPrice() << " " << i.second.getProfit() << ::std::endl;
        }
        ofs.close();
    }

public:
    Menu() = delete;
    explicit Menu(int count) noexcept {
        ifstream ifs(PATH "menu.data");
        string   line;
        while (getline(ifs, line)) {
            stringstream          ss(line);
            string                menuName;
            string                ingredientName;
            ::std::vector<string> ingredients;
            int                   price;
            ss >> menuName;
            while (ss >> ingredientName) {
                if (ingredientName != "#") {
                    ingredients.emplace_back(ingredientName);
                } else {
                    break;
                }
            }
            ss >> price;

            Dish dish(menuName, ingredients, price);
            m_dish.emplace(::std::make_pair(++count, dish));
        }
        ifs.close();
        this->m_count = count;
    }

    static Menu* getInstance();

    void showMenu() {
        for (auto it : m_dish) {
            ::std::cout << it.first << ": " << it.second.getName() << " " << it.second.getPrice() << " " << ::std::endl;
        }
    }

    bool addDish(Dish dish) {
        m_dish.emplace(::std::make_pair(++m_count, dish));
        saveToFile();
        return true;
    }

    bool deleteDish(::std::string dishName) {
        for (auto it : m_dish) {
            if (it.second.getName() == dishName) {
                m_dish.erase(it.first);
                saveToFile();
                --m_count;
                return true;
            }
        }
        return false;
    }
};

Menu* Menu::m_menu = nullptr;
Menu* Menu ::getInstance() {
    if (m_menu == nullptr) {
        m_menu = new Menu(0);
    }
    return m_menu;
}
