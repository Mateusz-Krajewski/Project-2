/**
 * @file Player.hpp 
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @author Kajetan Powala (powala.kajetan11@gmail.com)
 * @brief Define player class
 * @version 1.0
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
**/

#ifndef SRC_LIB_PLAYER_HPP_
#define SRC_LIB_PLAYER_HPP_

#include <string>
#include <queue>
#include <map>

#include "Config.hpp"
#include "Unit.hpp"


enum bonuses{
    num_of_bullet
};


class Player_class{
 private:
        int position;
        std::map<bonuses, int> bonus;
        std::string icon = "|<>|";

 public:
    void reset() {
        this->bonus.clear();
        this->bonus[num_of_bullet] = 1;
    }
    Player_class() {
            this->bonus[num_of_bullet] = 1;
    }
    ~Player_class() {}
    std::string get_icon() {
        return this->icon;
    }
    int get_position() {
        return this->position;
    }
    std::map<bonuses, int> get_bonuses() {
        return this->bonus;
    }
    void set_position(int pos) {
        this->position = pos;
    }
    //  lvl:+1 or -1
    void set_bonus(bonus_str name){
        switch (name) {
        case add_bullet:
            if (this->bonus[num_of_bullet]+1 <= config::MAX_AMMO_BONUS_LVL) {
            this->bonus[num_of_bullet]+=1;
            }
            break;
        case pop_bullet:
            if (this->bonus[num_of_bullet]-1 >= config::MIN_AMMO_BONUS_LVL) {
            this->bonus[num_of_bullet] -= 1;
            }
            break;
        default:
            break;
        }
    }
};




#endif  //  SRC_LIB_PLAYER_HPP_
