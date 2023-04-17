/**
 * @file main.cpp
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @author Kajetan Powala (powala.kajetan11@gmail.com)
 * @brief main file
 * @version 1.0
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
**/


#include <iostream>
#include "lib/Game.hpp"



int main() {
    srand(time(0));
    Game game = Game();
    while (true) {
        game.menu();
        int c;
        std::cin >> c;
        result r;
        switch (c) {
        case 1:
            r = game.play();
            if  (r.win) {
                std::cout << "You win" << std::endl << std::endl;
            } else if (r.lose) {
                std::cout << "You lose" << std::endl << std::endl;
            }
            break;
        case 2:
            game.settings();
            break;
        case 3:
            game.scores();
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
