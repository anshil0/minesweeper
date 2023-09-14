#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "TextureMananger.h"
using namespace std;
class Tile {
private:

public:
    sf::Texture texture;
    sf::Vector2f position;
    string filename;
    sf::Sprite sprite;
    sf::Sprite background;

    bool flagged;
    bool mine;
    bool found;
    int neigh;
    int num;

    Tile();
    Tile(string file, sf::Vector2f pos);
    void setSprite(sf::Texture& Texture);
    void setPosition(sf::Vector2f pos);
    void setBackground(sf::Texture& Texture);
    void Flagged();
    void setMines();
    void Found();

};

