#include "UI.h"


UI::UI(sf::Texture texture, int xpos, int ypos) {
    this -> texture = texture;
    this ->xpos = xpos;
    this ->ypos = ypos;
    this -> sprite = sprite;
//    texture.loadFromFile(filename);



}

sf::Sprite UI::open() {
    sprite.setTexture(texture);
    sprite.setPosition(xpos, ypos);
    return sprite;

}

void UI::changeSprite(sf::Texture asdf) {
    texture = asdf;

}

sf::Sprite UI::returnSprite() {
    sprite.setPosition(xpos, ypos);
    return sprite;
}


