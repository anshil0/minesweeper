#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;

class UI{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    int xpos;
    int ypos;
    UI( sf::Texture texture, int xpos, int ypos);
    sf::Sprite open();
    void changeSprite(sf::Texture texture);
    sf::Sprite returnSprite();

    string filename;
};