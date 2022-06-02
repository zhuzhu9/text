#pragma once
#include <iostream>
#include <vector>

#include "ingredients.hpp"

class Dish {
private:
    ::std::string                m_name;         // 菜名
    ::std::vector<::std::string> m_ingredients;  // 食材
    int                          m_price;        // 价格
    int                          m_profit;       // 利润

public:
    explicit Dish(::std::string name, ::std::vector<::std::string> ingredient, int price) noexcept :
            m_name(name), m_ingredients(ingredient), m_price(price), m_profit(0) {
        for (auto it : m_ingredients) {
            m_profit += Ingredients::getInstance()->getPrice(it);
        }
        m_profit = m_price - m_profit;
    }

    void setName(::std::string name) {
        this->m_name = name;
    }

    void setIngredients(::std::vector<::std::string> ingredients) {
        this->m_ingredients = ingredients;
    }

    void setPrice(int price) {
        this->m_price = price;
    }

    ::std::string getName() {
        return m_name;
    }

    ::std::vector<::std::string> getIngredients() {
        return m_ingredients;
    }

    int getPrice() {
        return m_price;
    }

    int getProfit() {
        return m_profit;
    }
};