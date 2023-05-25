#ifndef O_STATE_H
#define O_STATE_H

#include "gState.h"


namespace outroConst {
    const size_t LOSS_TITLE_SIZE = 50;
    const float LOSS_TITLE_X = 200.f;
    const float LOSS_TITLE_Y = 50.f;

    const size_t TITLE_SIZE = 50;
    const float TITLE_X = 100.f;
    const float TITLE_Y = 200.f;

    const size_t FOOTER_SIZE = 25;
    const float FOOTER_X = 100.f;
    const float FOOTER_Y = 400.f;

    const float MARGIN_UP = 80.f;

    const std::string RESULT = "You've got ";
    const std::string BACK = "'ESC' - Main menu";
    const std::string AGAIN = "'SPACE' - Try Again";
    const std::string GG = "YOU DID IT!";
    const std::string GO = "IT WAS GREAT...";
}


class OutroState : public GState {
public:
    OutroState(Game *stateKeeper);

    void render();

    void upd();

    void handleEvents();

private:
    sf::Sprite backSprite;
    sf::Text gResults;
    sf::Text gOver;
    sf::Text leave;
    sf::Text tryAgain;
};


#endif
