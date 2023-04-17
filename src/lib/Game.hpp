/**
 * @file Game.hpp 
 * @author Mateusz Krajewski (matikrajek42@gmail.com)
 * @author Kajetan Powala (powala.kajetan11@gmail.com)
 * @brief Define game class
 * @version 1.0
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
**/

#ifndef SRC_LIB_GAME_HPP_
#define SRC_LIB_GAME_HPP_

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>
#include <iostream>
#include <stack>
#include <future>
#include <thread>
#include <string>
#include <utility>

#include "Player.hpp"
#include "Unit.hpp"
#include "Config.hpp"


class Game;
struct result {
    bool win;
    bool lose;
    int game_time;
};


void clearConsole() {
    std::system("clear");
}


int get_move_thread(game_config config) {
    std::cout << "Enter your move:\n";
    std::promise<int> promise;

    std::future<int> future = promise.get_future();
    auto async_result = std::async(std::launch::async, [&promise, config]() {
        int a;
        do {
            std::cin >> a;
        }while(a < 1 || a >= (config.k+1));
        promise.set_value(a);
    });
    async_result.wait();
    return future.get();
}


void print(const std::vector<std::string>& inputVector) {
    char frameChar = config::FRAME_CHAR;
    int padding = config::PADDING;
    int longestString = 0;
    for (const auto& str : inputVector) {
        if (str.length() > longestString) {
            longestString = str.length();
        }
    }

    std::string frameLine(longestString + 2*padding + 2, frameChar);

    std::cout << frameLine << std::endl;

    for (const auto& str : inputVector) {
        std::cout << frameChar << std::string(padding, ' ')
        << str << std::string(padding, ' ');
        std::cout << std::string(longestString - str.length(), ' ')
        << frameChar << std::endl;
    }

    std::cout << frameLine << std::endl;
}


class Game {
 private:
        game_config Config;
        std::vector<std::queue<Unit_class>> board;
        Player_class Player;
        int points = 0;

        result isWin() {
            result r;
            bool win = true;
            bool lose = false;
            for (size_t i = 0; i < this->board.size(); i++) {
                if (this->board[i].size() > this->Config.w) {
                    lose = true;
                }
                if (this->board[i].size() != 0) {
                    win = false;
                }
            }
            r.win = win;
            r.lose = lose;
            return r;
        }
    void generate_board() {
        for (int i = 0; i < this->Config.k; i++) {
            this->board.push_back(std::queue<Unit_class>{});
            for (int j = 0; j < this->Config.b; j++) {
                this->board[i].push(Unit_class());
            }
        }
    }
    int generate_random() {
        return this->Config.r+rand()%(this->Config.n);
    }
    void reset_board() {
        for (auto& queue : this->board) {
            while (!queue.empty()) {
                queue.pop();
            }
        }
        this->board.clear();
    }
    void reset_player() {
        this->Player.reset();
    }
    void destroy_block(int pos) {
        int x = this->Player.get_bonuses()[num_of_bullet];
        for (int i = 0; i < x; i++) {
        if (!this->get_board()[pos].empty()) {
            this->points++;
            if (!this->board[pos].front().get_is_bonus()) {
                this->board[pos].pop();
            } else {
                switch (this->board[pos].front().get_bonus()) {
                case add_bullet:
                    this->Player.set_bonus(
                        this->board[pos].front().get_bonus());
                    this->board[pos].pop();
                    break;
                case pop_bullet:
                    this->Player.set_bonus(
                        this->board[pos].front().get_bonus());
                    this->board[pos].pop();
                    break;
                case hard_brick:
                    this->board[pos].front().set_is_bonus(false);
                    this->board[pos].front().set_bonus(none);
                    this->board[pos].front().set_icon("####");
                    break;
                default:
                    break;
                }
            }
        }
        }
    }


 public:
    void scores() {
        clearConsole();
        std::vector<std::string> v;
        v.push_back("tabela wynikow");
        std::fstream file;
        std::string line;
        file.open("scores.txt", std::ios::in);
        if (!file.is_open()) {
            return;
        }
        while (!file.eof()) {
            std::getline(file, line);
            v.push_back(line);
        }
        file.close();
        print(v);
    }

    void add_blocks() {
        for ( int i = 0; i < this->board.size(); i++ ) {
            this->board[i].push(Unit_class());
        }
    }
    void move(int pos) {
        pos--;
        this->set_Player_position(pos);
        destroy_block(pos);
    }
    void save_score() {
        std::string name;
        std::cout << "Enter your nickname: ";
        std::cin >> name;
        std::fstream file;
        file.open("scores.txt", std::ios::app);
        if (!file.is_open()) {
            std::cout << "ERROR! Score can not be saved." << std::endl;
        } else {
        file << name << "\t" << this->points << "\n";
        }
        file.close();
    }
    result play() {
        this->points = 0;
        this->generate_board();
        if ((this->Config.k)%2 == 0) {
            this->Player.set_position(((this->Config.k)/2)-1);
        } else {
            this->Player.set_position((((this->Config.k)/2)));
        }
        int moves_from_last_add  = 0;
        int los = generate_random();
        while (true) {
            result r = isWin();
            if (r.lose || r.win) {
                if (r.win) {
                    this->save_score();
                }
                this->reset_player();
                this->reset_board();
                return r;
            }
            clearConsole();
            this->print_board();
            int n = get_move_thread(this->get_config());
            this->move(n);
            moves_from_last_add++;
            if (moves_from_last_add >= los) {
                los = generate_random();
                this->add_blocks();
                moves_from_last_add = 0;
            }
        }
        this->reset_board();
    }

    void menu() {
        print({"1.Play", "2.Settings", "3.Scores", "4.Exit"});
    }

    void settings() {
        clearConsole();
        int c;
        do {
        print({"What do you want to set:",
        "1.Rows(w)", "2.Columns(k)",
        "3.Start blocks(b)", "4.Max random time(n)",
        "5.Blocks add time(r)", "6.Exit"});
        int set;
        std::cin >> c;
        switch (c) {
        case 1:
            std::cout << "Set the number of Rows:" << this->Config.w << "\n";
            std::cin >> set;
            this->Config.w = set;
            break;
        case 2:
            std::cout << "Set the number of Columns:"
            << this->Config.k << "\n";
            std::cin >> set;
            this->Config.k = set;
            break;
        case 3:
            std::cout << "Set the number of Start blocks:"
            << this->Config.b << "\n";
            std::cin >> set;
            this->Config.b = set;
            break;
        case 4:
            std::cout << "Set the number of blocks adding time (r), now:"
            << this->Config.r << "\n";
            std::cin >> set;
            this->Config.r = set;
            break;
        case 5:
            std::cout << "Set the value of Random Time (n):"
            << this->Config.n << "\n";
            std::cin >> set;
            this->Config.n = set;
            break;
        case 6:
            break;
        default:
            break;
        }
        }while (c != 6);
    }
    void print_board() {
        std::vector<std::queue<Unit_class>> x_board = this->get_board();
        std::vector<std::stack<Unit_class>> board(x_board.size());
        for (size_t i = 0; i < x_board.size(); i++) {
            while (!x_board[i].empty()) {
            board[i].push(x_board[i].front());
            x_board[i].pop();
            }
        }
        for (size_t i = 0; i < this->get_config().k; i++) {
            std::cout << "-----";
        }
        std::cout << "\n";
        for (size_t i = 0; i < this->get_config().w; i++) {
            for (size_t j=0; j < this->get_config().k; j++) {
                if (!board[j].empty()) {
                std::cout << board[j].top().get_icon() << " ";
                board[j].pop();
                } else {
                std::cout << "     ";
                }
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < this->get_config().k; i++) {
            if (this->Player.get_position() == i) {
                std::cout << this->Player.get_icon() << " ";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << std::endl;
        for (size_t i = 0; i < this->get_config().k; i++) {
            std::cout << "-----";
        }
        std::cout << std::endl;
    }
    void set_Player_position(int pos) {
        this->Player.set_position(pos);
    }
    game_config get_config() {
        return this->Config;
    }
    std::vector<std::queue<Unit_class>> get_board() {
        return this->board;
    }
    Player_class get_player() {
        return this->Player;
    }
    void set_config(game_config config) {
        this->Config = config;
    }
    void set_board(std::vector<std::queue<Unit_class>> board) {
        this->board = board;
    }
    void set_player(Player_class player) {
        this->Player = player;
    }
    Game() {
        this->Config = config::DEFAULT_GAME_CONFIG;
    }
    ~Game() {}
};

#endif  //  SRC_LIB_GAME_HPP_
