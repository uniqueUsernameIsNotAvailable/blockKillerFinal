#include "pState.h"


const float REF_SPEED = 6.f;
const float REF_WIDTH = 60.f;
const float REF_HEIGHT = 15.f;
const float REF_X0 = WINDOW_WIDTH / 2.f;
const float REF_Y0 = WINDOW_HEIGHT - 30.f;

const float BALL_SPEED = 5.f;
const float BALL_RADIUS = 9.f;
const float BALL_X0 = REF_X0;
const float BALL_Y0 = REF_Y0 + BALL_RADIUS;

const float TARGET_WIDTH = 50.f;
const float TARGET_HEIGHT = 20.f;
const int TARGET_ROWS_NUM = 4;
const int TARGET_COLS_NUM = 11;

const sf::Keyboard::Key BUTTON_LEFT = sf::Keyboard::Key::Left;
const sf::Keyboard::Key BUTTON_RIGHT = sf::Keyboard::Key::Right;


PState::PState(Game *stateKeeper) : GState(stateKeeper),
                                    bncr(BALL_X0, BALL_Y0, BALL_RADIUS, BALL_SPEED),
                                    refl(REF_X0, REF_Y0, REF_WIDTH, REF_HEIGHT, REF_SPEED),
                                    isOver(false) {
    Target::clearPoints();

    defAction = new DefaultCommand();
    btnL = new MoveLeftCommand();
    btnR = new MoveRightCommand();
    curAction = defAction;

    sf::Texture *texture = game->getResManager().getTexture(BackCode::mainBack);
    backSprite.setTexture(*texture);

    TargetMaker maker(TARGET_WIDTH, TARGET_HEIGHT);
    Target *curr = nullptr;

    bncr.attach(&refl);

    for (int i = 0; i < TARGET_COLS_NUM; i++)
        for (int j = 0; j < TARGET_ROWS_NUM; j++) {
            curr = maker.getTarget(j % 3 + 1);
            curr->setPosition(sf::Vector2f((i + 1) * (TARGET_WIDTH + 2) + 75,
                                           (j + 1) * (TARGET_HEIGHT + 2) + 50));
            targets.push_back(curr);
            bncr.attach(curr);
        }

    sf::Font *font = game->getResManager().getFont(pointsFont);

    pointsText.setColor(sf::Color::Green);
    pointsText.setCharacterSize(25);
    pointsText.setPosition(WINDOW_WIDTH - 150.f, 0.f);
    pointsText.setFont(*font);


    pauseText.setColor(sf::Color(255, 255, 255));
    pauseText.setCharacterSize(35);
    pauseText.setPosition(WINDOW_WIDTH / 2.f - 50.f, WINDOW_HEIGHT / 2.f - 50.f);
    pauseText.setFont(*font);
    pauseText.setString("PAUSED");
}

PState::~PState() {
    if (btnL != nullptr)delete btnL;

    if (btnR != nullptr) delete btnR;

    if (defAction != nullptr) delete defAction;

    for (Target *block: targets) delete block;

    targets.clear();
}


void PState::handleEvents() {
    sf::Event event;

    if (isOver) {
        game->setGPoints(Target::getPoints());
        game->savePoints();
        game->editState(States::Outro);
        return;
    }

    while (game->getWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->setGPoints(Target::getPoints());
                game->popState();
                return;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::P:
                        game->changePauseState();
                        return;
                    case sf::Keyboard::Escape:
                        game->editState(States::Menu);
                        return;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    if (sf::Keyboard::isKeyPressed(BUTTON_LEFT) && refl.getL() > 0)
        curAction = btnL;
    else if (sf::Keyboard::isKeyPressed(BUTTON_RIGHT) && refl.getR() < WINDOW_WIDTH)
        curAction = btnR;
    else
        curAction = defAction;
}


void PState::upd() {
    if (bncr.getL() < 0)
        bncr.setSpeedX(BALL_SPEED);
    else if (bncr.getR() > WINDOW_WIDTH)
        bncr.setSpeedX(-BALL_SPEED);

    if (bncr.getU() < 0)
        bncr.setSpeedY(BALL_SPEED);
    else if (bncr.getD() > WINDOW_HEIGHT) {
        isOver = true;
        return;
    }

    if (curAction != nullptr)
        curAction->Execute(refl);

    if (targets.size() == 0) {
        game->setWin(true);
        isOver = true;
        return;
    }

    bncr.upd();
    refl.upd();

    for (int i = 0; i < targets.size(); i++)
        if (!targets[i]->isHealth()) {
            bncr.detach(targets[i]);
            delete targets[i];
            targets.erase(targets.begin() + i);
            i--;
        }

    sf::String pointsStr = sf::String("POINTS: ") + sf::String(std::to_string(Target::getPoints()));
    pointsText.setString(pointsStr);
}


void PState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backSprite);
    game->getWindow()->draw(bncr);
    game->getWindow()->draw(refl);
    game->getWindow()->draw(pointsText);

    for (Target *block: targets) game->getWindow()->draw(*block);

    if (game->getPauseState()) game->getWindow()->draw(pauseText);

    game->getWindow()->display();
}
