#ifndef GAME_H
#define GAME_H

#include "rManager.h"
#include <stack>
#include <iostream>
#include <fstream>

const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const sf::String TITLE = "OOP_CW";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const int HSCORE_COUNT = 8;

class GState;

namespace States {
    enum Code {
        Menu,
        Game,
        Points,
        Pause,
        Outro
    };
}

struct TopRecord {
    std::string name;
    unsigned points;
};

class Game {
public:
    Game();

    ~Game();

    void run();

    void pushState(States::Code state);

    void popState();

    void editState(States::Code state);

    GState *getState() const;

    sf::RenderWindow *getWindow();

    rManager &getResManager();

    void loadHall(std::vector<TopRecord> &scores) const;

    void savePoints();

    void setGPoints(unsigned score);

    unsigned getPPoints() const;

    std::string getPName() const;

    void changePauseState();

    bool getPauseState() const;

    void setWin(bool isWon);

    bool isWon() const;

private:
    sf::RenderWindow window;
    const sf::Time timeForFrame;

    std::stack<GState *> screens;
    rManager rManager;
    TopRecord pPoints;
    bool isPaused;
    bool isWinner;
};


#endif
