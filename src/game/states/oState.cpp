#include "oState.h"


OutroState::OutroState(Game *stateKeeper) : GState(stateKeeper) {
    sf::Texture *texture = game->getResManager().getTexture(BackCode::mainBack);
    sf::Font *font = game->getResManager().getFont(FontCode::menuFont);

    backSprite.setTexture(*texture);

    std::string result = outroConst::RESULT + std::to_string(game->getPPoints()) + " points!";

    if (game->isWon())
        gOver.setString(outroConst::GG);
    else
        gOver.setString(outroConst::GO);

    gOver.setFont(*font);
    gOver.setColor(sf::Color::Red);
    gOver.setCharacterSize(outroConst::LOSS_TITLE_SIZE);
    gOver.setPosition(sf::Vector2f(outroConst::LOSS_TITLE_X, outroConst::LOSS_TITLE_Y));

    gResults.setFont(*font);
    gResults.setString(result);
    gResults.setColor(sf::Color::Yellow);
    gResults.setCharacterSize(outroConst::TITLE_SIZE);
    gResults.setPosition(sf::Vector2f(outroConst::TITLE_X, outroConst::TITLE_Y));

    leave.setFont(*font);
    leave.setString(outroConst::BACK);
    leave.setColor(sf::Color::White);
    leave.setCharacterSize(outroConst::FOOTER_SIZE);
    leave.setPosition(sf::Vector2f(outroConst::FOOTER_X, outroConst::FOOTER_Y));

    tryAgain.setFont(*font);
    tryAgain.setString(outroConst::AGAIN);
    tryAgain.setColor(sf::Color::White);
    tryAgain.setCharacterSize(outroConst::FOOTER_SIZE);
    tryAgain.setPosition(sf::Vector2f(outroConst::FOOTER_X, outroConst::FOOTER_Y + outroConst::MARGIN_UP));
}

void OutroState::upd() {}

void OutroState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backSprite);

    game->getWindow()->draw(gOver);
    game->getWindow()->draw(gResults);
    game->getWindow()->draw(leave);
    game->getWindow()->draw(tryAgain);

    game->getWindow()->display();
}

void OutroState::handleEvents() {
    sf::Event evnt;

    while (game->getWindow()->pollEvent(evnt)) {
        switch (evnt.type) {
            case sf::Event::Closed:
                game->popState();
                return;

            case sf::Event::KeyPressed:
                switch (evnt.key.code) {
                    case sf::Keyboard::Space:
                        game->editState(States::Game);
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
}