#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
class TextureManager
{
private:
    map<string, sf::Texture> textures;
    map <int, sf::Texture> numbers;
public:
    // Load a texture from a file and give it a name
    void loadTexture(string name, string filename)
    {
        sf::Texture texture;
        texture.loadFromFile(filename);
        textures[name] = texture;
    }
    void digit(int name, string filename, int left, int top, int width, int height)
    {
        sf::Texture texture;
        texture.loadFromFile(filename, sf::IntRect(left, top, width, height));
        numbers[name] = texture;
    }
    // Get a texture by name
    sf::Texture& getTexture(const string& name)
    {
        return textures.at(name);
    }
    sf::Texture& getDigit(const int name)
    {
//        cout << numbers.at(name);
        return numbers.at(name);
    }

};

