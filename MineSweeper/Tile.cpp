//
// Created by anshil on 4/18/2023.
//

#include "Tile.h"
// tile class and board class (2d vector in it) and
Tile::Tile(string file, sf::Vector2f pos) {
    this -> texture = texture;
    sprite = sf::Sprite(texture);
    background = sf::Sprite(texture);


    sprite.setPosition(pos.x, pos.y);
    position = pos;
    flagged = false;
    mine = false;
    found = false;


}


void Tile::setSprite(sf::Texture& Texture) {

    sprite.setTexture( Texture);

}

void Tile::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos.x, pos.y);
}

Tile::Tile() {
    texture.loadFromFile("files\\images\\tile_hidden.png");
    sprite = sf::Sprite(texture);
    background = sf::Sprite(texture);
    neigh= 0;
    flagged = false;
    mine = false;
    found = false;
    num = 0;

}

void Tile::setMines() {
    mine = true;
}

void Tile::Found() {
    found = true;
}

void Tile::setBackground(sf::Texture& Texture) {


    background.setTexture(Texture);

}

void Tile::Flagged() {
    flagged = true;
}





