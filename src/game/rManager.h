#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

enum BackCode {
    menuBack,
    hallBack,
    mainBack
};

enum FontCode {
    menuFont,
    pointsFont
};

namespace RFiles {
    extern std::string MenuFont;
    extern std::string MenuTexture;

    extern std::string ScoresFont;
    extern std::string ScoresTexture;

    extern std::string HighscoresData;
    extern std::string GameTexture;
}


class TextureManager {
public:
    ~TextureManager();

    sf::Texture *getTexture(BackCode code);

private:
    std::map<BackCode, sf::Texture *> textures;
};


class FontManager {
public:
    ~FontManager();

    sf::Font *getFont(FontCode code);

private:
    std::map<FontCode, sf::Font *> fonts;
};


class rManager {
public:
    sf::Texture *getTexture(BackCode code);

    sf::Font *getFont(FontCode code);

private:
    TextureManager texManager;
    FontManager fManager;
};


#endif
