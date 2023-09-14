#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "Tile.h"


class Board {
public:
    int row;
    int mines;
    vector<vector<Tile>> tiles;
    TextureManager textureManager;
    int col;
    int covered =0;
    Board(int row, int col, int mines, TextureManager &textureManager);
    void Debug();
    void reset();
    void adjacentMines();
    int Counter();

    void clear();
    void clearAdjacentTiles(int x, int y);

    void unclear();

    void Lost();

    void unDebug();

    void placeFlag();

    int allRevealed();
};



