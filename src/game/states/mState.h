#ifndef M_STATE_H
#define M_STATE_H

#include "gState.h"

extern const size_t CHAR_SIZE;
extern const float MENU_X;
extern const float MENU_Y;

namespace Choices {
    extern const std::string Play;
    extern const std::string Points;
    extern const std::string Leave;
}


class MenuState : public GState {
public:
    MenuState(Game *stateKeeper);

    ~MenuState();

    void render();

    void upd();

    void handleEvents();

private:
    enum Choice {
        Play,
        Scores,
        Exit
    };

    std::size_t chosen;
    sf::Sprite backSprite;

    std::vector<sf::Text> choices;

    void updChoices();
};


#endif
