#ifndef COMMAND_H
#define COMMAND_H

#include "gameObjects/reflector.h"


class Command {
public:
    virtual void Execute(Reflector &paddle) = 0;
};


class MoveLeftCommand : public Command {
public:
    void Execute(Reflector &paddle) {
        paddle.moveL();
    }
};


class MoveRightCommand : public Command {
public:
    void Execute(Reflector &paddle) {
        paddle.moveR();
    }
};


class DefaultCommand : public Command {
public:
    void Execute(Reflector &paddle) {
        paddle.stay();
    }
};


#endif