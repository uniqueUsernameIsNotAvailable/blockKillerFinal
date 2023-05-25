#include "rManager.h"


namespace RFiles {
    std::string MenuFont = "Media/fonts/pixFont.ttf";
    std::string MenuTexture = "Media/images/mainBckgrnd.png";

    std::string ScoresFont = "Media/fonts/pixFont.ttf";
    std::string ScoresTexture = "Media/images/mainBckgrnd.png";

    std::string HighscoresData = "Media/data.playerinfo";
    std::string GameTexture = "Media/images/bckgrnd.jpg";
}

sf::Texture *rManager::getTexture(BackCode code) { return texManager.getTexture(code); }

sf::Font *rManager::getFont(FontCode code) { return fManager.getFont(code); }


TextureManager::~TextureManager() {
    std::map<BackCode, sf::Texture *>::iterator it;
    for (it = textures.begin(); it != textures.end(); ++it)
        delete it->second;
}

sf::Texture *TextureManager::getTexture(BackCode code) {
    sf::Texture *txtr = nullptr;
    if (textures.find(code) != textures.end())
        return textures[code];

    txtr = new sf::Texture();

    switch (code) {
        case BackCode::menuBack:
            txtr->loadFromFile(RFiles::MenuTexture);
            break;

        case BackCode::hallBack:
            txtr->loadFromFile(RFiles::ScoresTexture);
            break;

        case BackCode::mainBack:
            txtr->loadFromFile(RFiles::GameTexture);
            break;

        default:
            break;
    }
    textures[code] = txtr;
    return txtr;
}


FontManager::~FontManager() {
    std::map<FontCode, sf::Font *>::iterator it;
    for (it = fonts.begin(); it != fonts.end(); ++it)
        delete it->second;
}

sf::Font *FontManager::getFont(FontCode code) {
    sf::Font *font = nullptr;
    if (fonts.find(code) != fonts.end())
        return fonts[code];
    font = new sf::Font();

    switch (code) {
        case FontCode::menuFont:
            font->loadFromFile(RFiles::MenuFont);
            break;
        case FontCode::pointsFont:
            font->loadFromFile(RFiles::ScoresFont);
            break;
        default:
            break;
    }
    fonts[code] = font;
    return font;
}