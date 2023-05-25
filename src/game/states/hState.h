#ifndef H_STATE_H
#define H_STATE_H

#include "gState.h"


extern const size_t TITLE_SIZE;
extern const size_t SUBTITLE_SIZE;
extern const size_t BODY_TEXT_SIZE;
extern const float TITLE_X;
extern const float TITLE_Y;
extern const float PLAYER_SUBT_X;
extern const float PLAYER_SUBT_Y;
extern const float MARGIN_TOP;
extern const float MARGIN_LEFT;

namespace HallStateStr {
    extern const std::string Title;
    extern const std::string Player;
    extern const std::string Score;
    extern const std::string Leave;
}

class HState : public GState {
public:
    HState(Game *stateKeeper);

    void render();

    void upd();

    void handleEvents();

private:
    sf::Sprite backSprite;

    sf::Text title;
    sf::Text pTitle;
    sf::Text pointsTitle;
    sf::Text leave;

    std::vector<std::pair<sf::Text, sf::Text>> highscores;
};


#endif
