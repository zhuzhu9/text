#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "config.h"

using ::std::ifstream;
using ::std::string;
using ::std::stringstream;

class Ingredients {
private:
    ::std::map<::std::string, int> ingredients;
    static Ingredients*            m_ingredients;

    void saveToFile() {
        ::std::ofstream ofs(PATH "ingredients.data");
        for (auto& i : ingredients) {
            ofs << i.first << " " << i.second << ::std::endl;
        }
        ofs.close();
    }

public:
    explicit Ingredients() noexcept {
        ifstream ifs(PATH "ingredients.data");
        string   line;
        while (getline(ifs, line)) {
            stringstream ss(line);
            string       ingredientName;
            int          price;
            ss >> ingredientName >> price;
            ingredients.emplace(::std::make_pair(ingredientName, price));
        }
        ifs.close();
    }

    ::std::string getIngredients(::std::string ingredient) {
        auto it = ingredients.find(ingredient);
        if (it != ingredients.end()) {
            return (it->first);
        }
        return nullptr;
    }

    int getPrice(::std::string ingredient) {
        auto it = ingredients.find(ingredient);
        if (it != ingredients.end()) {
            return (it->second);
        }
        return 0;
    }

    void addIngredients(::std::string ingredient, int price) {
        ingredients.emplace(::std::make_pair(ingredient, price));
        saveToFile();
    }

    void showIngredients() {
        for (auto it : ingredients) {
            ::std::cout << it.first << " " << it.second << ::std::endl;
        }
    }

    bool deleteIngredient(::std::string ingredient) {
        if (ingredients.erase(ingredient) == 1) {
            saveToFile();
            return true;
        }
        return false;
    }

    bool changeIngredientPrice(::std::string ingredient, int price) {
        auto it = ingredients.find(ingredient);
        if (it != ingredients.end()) {
            it->second = price;
            return true;
            saveToFile();
        }
        return false;
    }

    static Ingredients* getInstance();
};

Ingredients* Ingredients::m_ingredients = nullptr;

Ingredients* Ingredients::getInstance() {
    if (m_ingredients == nullptr) {
        m_ingredients = new Ingredients();
    }
    return m_ingredients;
}