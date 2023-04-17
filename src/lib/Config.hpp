/**
 * @file Config.hpp 
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @author Kajetan Powala (powala.kajetan11@gmail.com)
 * @brief Define config variable
 * @version 1.0
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
**/
#ifndef SRC_LIB_CONFIG_HPP_
#define SRC_LIB_CONFIG_HPP_

struct game_config {
        int r;  //  czas
        int w;  //  wiersz
        int k;  //  kolumna
        int b;  //  startowa ilosc bloczkow
        int n;  //  max random dodania bloczka
};

namespace config {
const int LUCK = 12;
const int MAX_AMMO_BONUS_LVL = 3;
const int MIN_AMMO_BONUS_LVL = 1;
const char FRAME_CHAR = '#';
const int PADDING = 2;
const int MAX_BONUS_LEN = 4;  //  UNUSED
const int MAX_POSITION_SIZE = 50;  //  UNUSED??


game_config DEFAULT_GAME_CONFIG {
    r:2, w:8, k:5, b:3, n:4
    };
}  // namespace config

#endif  // SRC_LIB_CONFIG_HPP_
