#ifndef P_STATE_H
#define P_STATE_H

#include "../gameObjects/reflector.h"
#include "../command.h"
#include "../gameObjects/target.h"
#include "gState.h"


extern const float BALL_SPEED;
extern const float BALL_RADIUS;
extern const float BALL_X0;
extern const float BALL_Y0;

extern const float REF_SPEED;
extern const float REF_WIDTH;
extern const float REF_HEIGHT;
extern const float REF_X0;
extern const float REF_Y0;

extern const float TARGET_WIDTH;
extern const float TARGET_HEIGHT;
extern const int TARGET_COLS_NUM;
extern const int TARGET_ROWS_NUM;

extern const sf::Keyboard::Key BUTTON_LEFT;
extern const sf::Keyboard::Key BUTTON_RIGHT;


class PState : public GState {
public:
    PState(Game *stateKeeper);

    ~PState();

    void render();

    void upd();

    void handleEvents();

private:
    Bouncer bncr;
    Reflector refl;
    std::vector<Target *> targets;

    Command *curAction;
    Command *btnL;
    Command *btnR;
    Command *defAction;

    bool isOver;

    sf::Sprite backSprite;
    sf::Text pointsText;
    sf::Text pauseText;
};

#endif
