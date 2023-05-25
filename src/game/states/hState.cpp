#include "hState.h"


const size_t TITLE_SIZE = 50;
const float TITLE_X = 200.f;
const float TITLE_Y = 7.f;
const size_t SUBTITLE_SIZE = 30;
const size_t BODY_TEXT_SIZE = 25;
const float PLAYER_SUBT_X = 100.f;
const float PLAYER_SUBT_Y = 100.f;
const float MARGIN_TOP = 50.f;
const float MARGIN_LEFT = 550.f;


namespace HallStateStr {
    const std::string Title = "Hall of Fame";
    const std::string Player = "Name";
    const std::string Score = "Points";
    const std::string Leave = "'SPACE' - main menu";
}


HState::HState(Game *stateKeeper) : GState(stateKeeper) {
    sf::Texture *texture = game->getResManager().getTexture(BackCode::hallBack);
    sf::Font *font = game->getResManager().getFont(FontCode::pointsFont);
    backSprite.setTexture(*texture);

    title.setFont(*font);
    title.setString(HallStateStr::Title);
    title.setColor(sf::Color::Yellow);
    title.setCharacterSize(TITLE_SIZE);
    title.setPosition(sf::Vector2f(TITLE_X, TITLE_Y));

    pTitle.setFont(*font);
    pTitle.setString(HallStateStr::Player);
    pTitle.setColor(sf::Color::Cyan);
    pTitle.setCharacterSize(SUBTITLE_SIZE);
    pTitle.setPosition(sf::Vector2f(PLAYER_SUBT_X, PLAYER_SUBT_Y));

    pointsTitle.setFont(*font);
    pointsTitle.setString(HallStateStr::Score);
    pointsTitle.setColor(sf::Color::Cyan);
    pointsTitle.setCharacterSize(SUBTITLE_SIZE);
    pointsTitle.setPosition(sf::Vector2f(PLAYER_SUBT_X + MARGIN_LEFT, PLAYER_SUBT_Y));

    std::vector<TopRecord> vecTemp;
    game->loadHall(vecTemp);

    sf::Text plr;
    sf::Text pts;

    for (int i = 0; i < vecTemp.size(); i++) {
        plr.setString(vecTemp[i].name);
        plr.setCharacterSize(BODY_TEXT_SIZE);
        plr.setFont(*font);
        plr.setPosition(sf::Vector2f(PLAYER_SUBT_X, PLAYER_SUBT_Y + MARGIN_TOP * (i + 1)));

        pts.setFont(*font);
        pts.setString(std::to_string(vecTemp[i].points));
        pts.setCharacterSize(BODY_TEXT_SIZE);
        pts.setPosition(sf::Vector2f(PLAYER_SUBT_X + MARGIN_LEFT + MARGIN_TOP / 2.f,
                                     PLAYER_SUBT_Y + MARGIN_TOP * (i + 1)));

        if (vecTemp[i].name == game->getPName()) {
            plr.setColor(sf::Color::Red);
            pts.setColor(sf::Color::Red);
        } else {
            plr.setColor(sf::Color::White);
            pts.setColor(sf::Color::White);
        }
        highscores.emplace_back(plr, pts);
    }

    leave.setFont(*font);
    leave.setString(HallStateStr::Leave);
    leave.setColor(sf::Color::Cyan);
    leave.setCharacterSize(BODY_TEXT_SIZE);
    leave.setPosition(sf::Vector2f(TITLE_X - 120.f, highscores.back().first.getPosition().y + MARGIN_TOP));
}

void HState::upd() {}

void HState::render() {
    game->getWindow()->clear();
    game->getWindow()->draw(backSprite);
    game->getWindow()->draw(title);
    game->getWindow()->draw(pTitle);
    game->getWindow()->draw(pointsTitle);
    game->getWindow()->draw(leave);

    for (const std::pair<sf::Text, sf::Text> &record: highscores) {
        game->getWindow()->draw(record.first);
        game->getWindow()->draw(record.second);
    }
    game->getWindow()->display();
}

void HState::handleEvents() {
    sf::Event event;

    while (game->getWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->popState();
                return;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        game->popState();
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