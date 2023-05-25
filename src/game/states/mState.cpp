#include "mState.h"

const size_t CHAR_SIZE = 75;
const float MENU_X = 100.f;
const float MENU_Y = 100.f;


namespace Choices {
    const std::string Play = "Play";
    const std::string Points = "Hall of Fame";
    const std::string Leave = "Leave";
}

MenuState::MenuState(Game *stateKeeper) : GState(stateKeeper), chosen(0) {
    sf::Texture *texture = game->getResManager().getTexture(BackCode::menuBack);
    sf::Font *font = game->getResManager().getFont(FontCode::menuFont);
    backSprite.setTexture(*texture);

    sf::Text playItem;
    playItem.setFont(*font);
    playItem.setString(Choices::Play);
    playItem.setCharacterSize(CHAR_SIZE);
    playItem.setPosition(sf::Vector2f(MENU_X, MENU_Y));
    choices.push_back(playItem);


    sf::Text pointsItem;
    pointsItem.setFont(*font);
    pointsItem.setString(Choices::Points);
    pointsItem.setCharacterSize(CHAR_SIZE);
    pointsItem.setPosition(playItem.getPosition() + sf::Vector2f(0.f, CHAR_SIZE));
    choices.push_back(pointsItem);

    sf::Text leaveItem;
    leaveItem.setFont(*font);
    leaveItem.setCharacterSize(CHAR_SIZE);
    leaveItem.setString(Choices::Leave);
    leaveItem.setPosition(pointsItem.getPosition() + sf::Vector2f(0.f, CHAR_SIZE));
    choices.push_back(leaveItem);

    updChoices();
}

MenuState::~MenuState() {
    delete choices[0].getFont();
    delete backSprite.getTexture();
}

void MenuState::updChoices() {
    for (sf::Text &item: choices)
        item.setColor(sf::Color::White);
    choices[chosen].setColor(sf::Color::Yellow);
}

void MenuState::upd() {}

void MenuState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backSprite);

    for (sf::Text &item: choices)
        game->getWindow()->draw(item);

    game->getWindow()->display();
}

void MenuState::handleEvents() {
    sf::Event event;

    while (game->getWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->popState();
                return;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        chosen = chosen > 0 ? chosen - 1 : choices.size() - 1;
                        updChoices();
                        break;

                    case sf::Keyboard::Down:
                        chosen = (chosen + 1) % choices.size();
                        updChoices();
                        break;

                    case sf::Keyboard::Return:
                        switch (chosen) {
                            case Play:
                                game->editState(States::Game);
                                return;
                            case Scores:
                                game->pushState(States::Points);
                                break;
                            case Exit:
                                game->popState();
                                return;
                            default:
                                break;
                        }
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}