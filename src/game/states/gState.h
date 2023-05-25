#ifndef G_STATE_H
#define G_STATE_H

#include "../game.h"

class GState {
public:
    GState(Game *stateKeeper) : game(stateKeeper) {}

    virtual void render() = 0;

    virtual void upd() = 0;

    virtual void handleEvents() = 0;

protected:
    Game *game;
};

#endif
