/**
 * @file Unit.hpp 
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @author Kajetan Powala (powala.kajetan11@gmail.com)
 * @brief Define unit class
 * @version 1.0
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
**/

#ifndef SRC_LIB_UNIT_HPP_
#define SRC_LIB_UNIT_HPP_

#include <string>
#include <cstdlib>
#include <ctime>

#include "Config.hpp"

enum bonus_str{
    add_bullet,
    pop_bullet,
    hard_brick,
    none,
};

class Unit_class{
 private:
        std::string icon;
        bool is_bonus;
        bonus_str bonus;

 public:
    ~Unit_class() {}
    Unit_class() {
        int z = rand()%config::LUCK;
        if (z == 0) {
            this->is_bonus = true;
            this->icon = "#++#";
            this->bonus = add_bullet;
        } else if (z == 1) {
            this->is_bonus = true;
            this->icon = "#--#";
            this->bonus = pop_bullet;
        } else if (z == 2 || z == 3) {
            this->is_bonus = true;
            this->icon = "#XX#";
            this->bonus = hard_brick;
        } else {
            this->is_bonus = false;
            this->icon = "####";
            this->bonus = none;
        }
    }
    std::string get_icon() {
        return this->icon;
    }
    bool get_is_bonus() {
        return this->is_bonus;
    }
    void set_is_bonus(bool is_bonus) {
        this->is_bonus = is_bonus;
    }
    void set_bonus(bonus_str bonus) {
        this->bonus = bonus;
    }
    void set_icon(std::string icon) {
        this->icon = icon;
    }
    bonus_str get_bonus() {
        return this->bonus;
    }
};

#endif  // SRC_LIB_UNIT_HPP_
