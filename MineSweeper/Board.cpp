//
// Created by anshil on 4/18/2023.
//

#include "Board.h"
#include <random>

mt19937 random_mt;

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

Board::Board(int row, int col, int mines, TextureManager &textureManager) {
    this->row = row;
    this->col = col;
    this->mines = mines;
    this -> tiles = tiles;
    this -> textureManager = textureManager;
    tiles.resize(col);
    for (int i = 0; i < col; i++){
        tiles[i].resize(row);
    }
    int mineNum = 0;
    while(mineNum < mines){
        int x = Random(0, col-1);
        int y = Random(0, row-1);
        if(!tiles[x][y].mine){
            tiles[x][y].setMines();
            tiles[x][y].num = 1;

            mineNum++;

        }
    }



}

void Board::Debug() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].num == 1) {
                tiles[i][j].setBackground(textureManager.getTexture("hidden"));
                tiles[i][j].setSprite(textureManager.getTexture("mines"));

            }
        }
    }
}
void Board::unDebug() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].num == 1) {
                tiles[i][j].setBackground(textureManager.getTexture("hidden"));
                tiles[i][j].setSprite(textureManager.getTexture("hidden"));

            }
        }
    }
}
void Board::Lost() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].num == 1) {
                tiles[i][j].setBackground(textureManager.getTexture("revealed"));
                tiles[i][j].setSprite(textureManager.getTexture("mines"));

            }
        }
    }
}



void Board::reset() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {

                tiles[i][j].num = 0;
                tiles[i][j].neigh = 0;
                tiles[i][j].mine = false;
                tiles[i][j].found = false;
                tiles[i][j].flagged = false;

                tiles[i][j].setSprite(textureManager.getTexture("hidden"));


        }
    }
    covered = 0;
    int mineNum = 0;
    while (mineNum < mines) {
        int x = Random(0, col - 1);
        int y = Random(0, row - 1);
        if (!tiles[x][y].mine) {
            tiles[x][y].setMines();
            tiles[x][y].num = 1;

            mineNum++;

        }
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].num == 1) {
                tiles[i][j].setSprite(textureManager.getTexture("hidden"));

            }
            if (tiles[i][j].found){
                tiles[i][j].setSprite(textureManager.getTexture("hidden"));
                tiles[i][j].found = false;
            }
        }
    }
}

void Board::adjacentMines() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].mine) {
                for (int a = -1; a <= 1; a++) {
                    for (int b = -1; b <= 1; b++) {
                        if (i == 0 && j == 0) continue;
                        int c = a + i;
                        int r = b + j;
                        if (r >= 0 && r < row && c >= 0 && c < col){
                            tiles[c][r].neigh++;

                        }
                    }
                }
            }
        }
    }
}

int Board::Counter() {

    int counter = mines;
    counter = counter - covered;
    return counter;


}

void Board::clearAdjacentTiles(int x, int y) {
    if (tiles[x][y].mine) return; // stop recursion if tile contains mine
    if (tiles[x][y].neigh > 0) {
        tiles[x][y].background.setTexture(textureManager.getTexture("revealed"));
        tiles[x][y].setSprite(textureManager.getTexture(to_string(tiles[x][y].neigh)));
        tiles[x][y].found = true; // reveal tile if it has adjacent mines
        return;
    }
    tiles[x][y].setSprite(textureManager.getTexture("revealed"));
    tiles[x][y].found = true; // reveal tile if it has no adjacent mines
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {

            int c = a + x;
            int r = b + y;
            if (r >= 0 && r < row && c >= 0 && c < col && !tiles[c][r].found && !tiles[c][r].flagged) {
                clearAdjacentTiles(c, r);

            }
        }
    }

}

void Board::clear() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {

            tiles[i][j].setSprite(textureManager.getTexture("revealed"));

        }

    }
}
int Board::allRevealed(){
    int normal = (col * row) - mines;
    int revealed = 0;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].found){
                revealed++;
            }

        }
    }
    int winCondition = normal - revealed;
    return winCondition;
//    if (winCondition == 0){
//        return true;
//    }
}

void Board::placeFlag(){
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (tiles[i][j].num == 1){
                tiles[i][j].setSprite(textureManager.getTexture("flagged"));
            }


        }

    }
}

void Board::unclear(){
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if(tiles[i][j].found && tiles[i][j].neigh == 0) {
                tiles[i][j].setSprite(textureManager.getTexture("revealed"));
            }
            else if (tiles[i][j].flagged){
                tiles[i][j].setSprite(textureManager.getTexture("flagged"));

            }
            else if (tiles[i][j].neigh <= 8 && tiles[i][j].found){
                tiles[i][j].setSprite(textureManager.getTexture(to_string(tiles[i][j].neigh)));

            }
            else{
                tiles[i][j].setSprite(textureManager.getTexture("hidden"));
            }


        }

    }
}


