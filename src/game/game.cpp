#include "game.h"
#include "states/pState.h"
#include "states/mState.h"
#include "states/hState.h"
#include "states/oState.h"


Game::Game() :
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
        timeForFrame(TIME_PER_FRAME), isPaused(false), isWinner(false) {
    pushState(States::Code::Menu);
    pPoints.points = 0;
    pPoints.name = "ThePlayer";
}

Game::~Game() { while (!screens.empty()) popState(); }


GState *Game::getState() const {
    if (screens.empty()) return nullptr;
    return screens.top();
}

void Game::pushState(States::Code state) {
    switch (state) {
        case States::Code::Game:
            screens.push(new PState(this));
            break;
        case States::Code::Menu:
            screens.push(new MenuState(this));
            break;
        case States::Code::Pause:
            break;
        case States::Code::Points:
            screens.push(new HState(this));
            break;
        case States::Code::Outro:
            screens.push(new OutroState(this));
        default:
            break;
    }
}

void Game::editState(States::Code state) {
    if (!screens.empty())
        popState();
    pushState(state);
}

void Game::popState() {
    delete screens.top();
    screens.pop();
}


sf::RenderWindow *Game::getWindow() { return &window; }

rManager &Game::getResManager() { return rManager; }


void Game::changePauseState() { isPaused = !isPaused; }

bool Game::getPauseState() const { return isPaused; }

void Game::run() {
    sf::Clock clck;
    sf::Time updTime = sf::Time::Zero;

    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        updTime += clck.restart();

        if (getState() == nullptr)
            return;

        while (updTime > timeForFrame) {
            if (!isPaused)
                getState()->upd();
            updTime -= timeForFrame;
        }

        getState()->render();
        getState()->handleEvents();
    }
}


void Game::loadHall(std::vector<TopRecord> &scores) const {
    std::ifstream hScores(RFiles::HighscoresData);

    if (!hScores.is_open())
        std::cout << "Error to open: " + RFiles::HighscoresData;

    TopRecord record;
    while (hScores >> record.name >> record.points)
        scores.push_back(record);

    hScores.close();
}

void Game::savePoints() {
    std::vector<TopRecord> records;
    loadHall(records);

    if (pPoints.points <= records.back().points)
        return;

    records.push_back(pPoints);
    std::sort(records.begin(), records.end(), [](const TopRecord &l, const TopRecord &r) {
        return l.points > r.points;
    });

    std::ofstream hScores(RFiles::HighscoresData);
    for (int i = 0; i < HSCORE_COUNT; i++)
        hScores << (records[i].name + " " + std::to_string(records[i].points) + " ");

    hScores.close();
}

void Game::setGPoints(unsigned score) { pPoints.points = score; }

unsigned Game::getPPoints() const { return pPoints.points; }

std::string Game::getPName() const { return pPoints.name; }

void Game::setWin(bool isWon) { isWinner = isWon; }

bool Game::isWon() const { return isWinner; }