#include <unordered_map>
#include "Tile.h"
#include "UI.h"
#include "Board.h"
#include "functions.h"
#include "TextureMananger.h"
#include <chrono>
#include <fstream>


using namespace std;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int main() {
    vector<float> config;
    config = read(R"(C:\Users\13214\Desktop\MineSweeper\cmake-build-debug\files\board_config.cfg)");
    int row = config[1];
    int col = config[0];
    int numMines = config[2];
    int width = col * 32;
    int height = row * 32 + 100;

    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper");

    sf::Font font;
    font.loadFromFile(R"(files\font.ttf)");

    // Welcome Text
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcomeText, width / 2.0f, height / 2.0f - 150);

    // Prompt
    sf::Text promptText("Enter your name:", font, 20);
    promptText.setStyle(sf::Text::Bold);
    setText(promptText, width / 2.0f, height / 2.0f - 75);

    string name;
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(18);
    nameText.setStyle(sf::Text::Bold);
    nameText.setFillColor(sf::Color::Yellow);
    setText(nameText, width / 2.0f, height / 2.0f - 45);

    TextureManager textures;
    textures.loadTexture("cool", "files/images/face_win.png");
    textures.loadTexture("happy", "files/images/face_happy.png");
    textures.loadTexture("sad", "files/images/face_lose.png");
    textures.loadTexture("leader", "files/images/leaderboard.png");
    textures.loadTexture("pause", "files/images/pause.png");
    textures.loadTexture("debug", "files/images/debug.png");
    textures.loadTexture("play", "files/images/play.png");

    textures.loadTexture("revealed", "files/images/tile_revealed.png");
    textures.loadTexture("hidden", "files/images/tile_hidden.png");
    textures.loadTexture("mines", "files/images/mine.png");
    textures.loadTexture("flagged", "files/images/flag.png");


    textures.loadTexture("1", "files/images/number_1.png");
    textures.loadTexture("2", "files/images/number_2.png");
    textures.loadTexture("3", "files/images/number_3.png");
    textures.loadTexture("4", "files/images/number_4.png");
    textures.loadTexture("5", "files/images/number_5.png");
    textures.loadTexture("6", "files/images/number_6.png");
    textures.loadTexture("7", "files/images/number_7.png");
    textures.loadTexture("8", "files/images/number_8.png");
    TextureManager numbers;

    numbers.digit(0, "files/images/digits.png", 0, 0, 21, 32);
    numbers.digit(1, "files/images/digits.png", 21, 0, 21, 32);
    numbers.digit(2, "files/images/digits.png", 42, 0, 21, 32);
    numbers.digit(3, "files/images/digits.png", 63, 0, 21, 32);
    numbers.digit(4, "files/images/digits.png", 84, 0, 21, 32);
    numbers.digit(5, "files/images/digits.png", 105, 0, 21, 32);
    numbers.digit(6, "files/images/digits.png", 126, 0, 21, 32);
    numbers.digit(7, "files/images/digits.png", 147, 0, 21, 32);
    numbers.digit(8, "files/images/digits.png", 168, 0, 21, 32);
    numbers.digit(9, "files/images/digits.png", 189, 0, 21, 32);
    numbers.digit(10, "files/images/digits.png", 210, 0, 21, 32);

    UI cool(textures.getTexture("cool"), (((col) / 2.0) * 32) - 32, 32 * ((row) + 0.5f));
    UI sad(textures.getTexture("sad"), (((col) / 2.0) * 32) - 32, 32 * ((row) + 0.5f));
    UI happy(textures.getTexture("happy"), (((col) / 2.0) * 32) - 32, 32 * ((row) + 0.5f));
    UI debug(textures.getTexture("debug"), ((col) * 32) - 304, 32 * ((row) + 0.5f));
    UI pause(textures.getTexture("pause"), ((col) * 32) - 240, 32 * ((row) + 0.5f));
    UI play(textures.getTexture("play"), ((col) * 32) - 240, 32 * ((row) + 0.5f));
    UI leaderboard(textures.getTexture("leader"), ((col) * 32) - 176, 32 * ((row) + 0.5f));

    Tile tile;
    Board board(row, col, numMines, textures);
    board.adjacentMines();

    ifstream file("files/leaderboard.txt", ios::in);
    map<string, string> players;
    string line;

    while (getline(file, line)) {
        line.erase(remove(line.begin(), line.end(), '*'), line.end());
        string time = line.substr(0, line.find(','));
        string playerName = line.substr(line.find(',') + 1); // extract the name as the value
        players[time] = playerName; // add the key-value pair to the map
    }
    vector<string> times;
    vector<string> names;
    string placement;
    for (auto it = players.begin(); it != players.end(); ++it) {

        times.push_back(it->first);
        names.push_back(it->second);
    }


    placement = string("1.") + "\t" + times[0] + "\t" + names[0] + "\n\n" + "2." + "\t" + times[1] + "\t" + names[1] +
                "\n\n" +
                "3." + "\t" + times[2] + "\t" + names[2] + "\n\n" + "4." + "\t" + times[3] + "\t" + names[3] + "\n\n" +
                "5." + "\t" + times[4] + "\t" + names[4];

    while (welcomeWindow.isOpen()) {
        sf::Event event;
        while (welcomeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {


                welcomeWindow.close();
                return 0;
            } else if (event.type == sf::Event::TextEntered) {
                char c = static_cast <char>(event.text.unicode);
                if (isalpha(c) && name.size() < 10) {
                    name += c;
                    name[0] = toupper(name[0]);

                    for (int i = 1; i < name.size(); i++) {
                        name[i] = tolower(name[i]);
                    }
                    nameText.setString(string(name));
                    sf::FloatRect bound = nameText.getLocalBounds();
                    nameText.setOrigin(bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f);
                    nameText.setPosition(width / 2.0f, height / 2.0f - 45);
                } else if (event.text.unicode == '\b' && !name.empty()) // Backspace
                {
                    name.pop_back();
                }

                nameText.setString(string(name));
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !name.empty()) {

                    welcomeWindow.close();


                }
            }
            nameText.setString(name + "|");
            welcomeWindow.clear(sf::Color::Blue);
            welcomeWindow.draw(promptText);
            welcomeWindow.draw(welcomeText);
            welcomeWindow.draw(nameText);
            welcomeWindow.display();

        }


    }

    name = name + "*";
    bool lost = false;
    bool won = false;
    bool negCounter = false;
    bool leader_open = false;
    bool reset = false;
    bool debugON = false;
    bool temp_bool = false;

    sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper!");
    int temp = board.Counter();
    int ten = board.Counter() / 10;
    int one = board.Counter() % 10;
    temp /= 100;
    int hundred = temp % 10;


    UI negative(numbers.getDigit(10), 12, 32 * ((row) + 0.5f) + 16);
    UI counter(numbers.getDigit(hundred), 33, 32 * ((row) + 0.5f) + 16);
    UI counter2(numbers.getDigit(ten), 54, 32 * ((row) + 0.5f) + 16);
    UI counter3(numbers.getDigit(one), 75, 32 * ((row) + 0.5f) + 16);

    UI tenth_min(numbers.getDigit(0), col * 32 - 97, 32 * (row + 0.5f) + 16);
    UI min(numbers.getDigit(0), col * 32 - 97 + 21, 32 * (row + 0.5f) + 16);
    UI tenth_sec(numbers.getDigit(0), col * 32 - 54, 32 * (row + 0.5f) + 16);
    UI sec(numbers.getDigit(0), col * 32 - 54 + 21, 32 * (row + 0.5f) + 16);


    bool paused = false;
    auto start_time = chrono::high_resolution_clock::now();

    auto pause_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::seconds>(
            chrono::high_resolution_clock::now() - pause_time).count();
    int totalTime;
//    auto gameTime = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
    while (gameWindow.isOpen()) {

        sf::Event game;
        while (gameWindow.pollEvent(game)) {
            if (game.type == sf::Event::Closed)
                gameWindow.close();
            else if (game.type == sf::Event::MouseButtonPressed) {

                sf::Mouse mouse;
                auto coordinate = mouse.getPosition(gameWindow);
                auto debugPos = debug.sprite.getGlobalBounds();
                auto happyPos = happy.sprite.getGlobalBounds();
                auto pausePos = pause.sprite.getGlobalBounds();
                auto leaderPos = leaderboard.sprite.getGlobalBounds();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    if (debugPos.contains(coordinate.x, coordinate.y)) {
                        if (!debugON) {
                            board.Debug();
                            debugON = true;
                        } else {
                            board.unDebug();
                            debugON = false;
                        }

                    } else if (happyPos.contains(coordinate.x, coordinate.y)) {
                        board.reset();
                        reset = true;
//                        totalTime = chrono::duration_cast<chrono::seconds>(gameTime).count() - chrono::duration_cast<chrono::seconds>(gameTime).count();
                        ten = board.Counter() / 10;
                        one = board.Counter() % 10;

                        start_time = chrono::high_resolution_clock::now();
                        negCounter = false;
                        counter2.changeSprite(numbers.getDigit(ten));
                        counter3.changeSprite(numbers.getDigit(one));
                        gameWindow.draw(counter2.open());
                        gameWindow.draw(counter3.open());
                        board.adjacentMines();
                        totalTime = 0;
                        paused = false;
                        lost = false;
                        won = false;
                    } else if (pausePos.contains(coordinate.x, coordinate.y) and !lost and !won) {
                        if (!paused) {
                            paused = true;
                            board.clear();
                            pause_time = chrono::high_resolution_clock::now();
                        } else {
                            paused = false;
                            board.unclear();
                            auto play_time = chrono::high_resolution_clock::now();
                            elapsed_time = elapsed_time += chrono::duration_cast<chrono::seconds>(play_time - pause_time).count();
                        }

                    } else if (leaderPos.contains(coordinate.x, coordinate.y)) {
                        leader_open = false;


                        if (!leader_open) {
                            board.clear();
                            pause_time = chrono::high_resolution_clock::now();


                            leader_open = true;

                            sf::RenderWindow leaderWindow(sf::VideoMode(16 * col, (16 * row) + 50), "Leaderboard");
                            sf::Text leaderTitle("LEADERBOARD", font, 20);
                            leaderTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
                            setText(leaderTitle, (16 * col) / 2.0f, ((row * 16) + 50) / 2.0f - 120);

                            sf::Text leaderText(placement, font, 20);
                            leaderText.setCharacterSize(18);
                            leaderText.setStyle(sf::Text::Bold);
                            setText(leaderText, (16 * col) / 2.0f, ((row * 16) + 50) / 2.0f + 20);
                            while (leaderWindow.isOpen()) {
                                sf::Event event;
                                while (leaderWindow.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        leaderWindow.close();
                                        leader_open = false;
                                        auto resume = chrono::high_resolution_clock::now();
                                        elapsed_time = elapsed_time += chrono::duration_cast<chrono::seconds>(resume - pause_time).count();
                                        board.unclear();
                                    }
                                }



                                leaderWindow.clear(sf::Color::Blue);
                                leaderWindow.draw(leaderTitle);
                                leaderWindow.draw(leaderText);
                                leaderWindow.display();
                            }
                        }
                    } else {
                        for (int i = 0; i < board.col; i++) {
                            for (int j = 0; j < board.row; j++) {
                                auto tilePos = board.tiles[i][j].sprite.getGlobalBounds();
                                if (tilePos.contains(coordinate.x, coordinate.y)) {
                                    if (!paused) {

                                        if (board.tiles[i][j].num == 1 and !board.tiles[i][j].flagged) {
                                            board.Lost();
                                            lost = true;
                                            paused = true;


                                        } else {
                                            if (!board.tiles[i][j].flagged and !lost and !won and !leader_open) {
                                                if (board.tiles[i][j].neigh > 0) {
                                                    board.tiles[i][j].background.setTexture(
                                                            textures.getTexture("revealed"));
                                                    board.tiles[i][j].setSprite(textures.getTexture(
                                                            to_string(board.tiles[i][j].neigh)));
                                                    board.tiles[i][j].found = true;
                                                    if (board.allRevealed() == 0){
                                                        board.placeFlag();
                                                        won = true;
                                                        temp_bool = true;
                                                    }

                                                } else {
                                                    board.clearAdjacentTiles(i, j);
                                                    board.tiles[i][j].Found();
                                                    if (board.allRevealed() == 0){
                                                        board.placeFlag();
                                                        won = true;
                                                        temp_bool = true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    for (int i = 0; i < board.col; i++) {
                        for (int j = 0; j < board.row; j++) {
                            auto tilePos = board.tiles[i][j].sprite.getGlobalBounds();
                            if (tilePos.contains(coordinate.x, coordinate.y)) {
                                if (!paused) {

                                    if (!board.tiles[i][j].flagged and !board.tiles[i][j].found and !lost and
                                        !won) {
                                        board.tiles[i][j].setBackground(textures.getTexture("hidden"));
                                        board.tiles[i][j].setSprite(textures.getTexture("flagged"));
                                        board.tiles[i][j].Flagged();
                                        board.covered++;

                                        if (board.Counter() < 0) {
                                            negCounter = true;
                                            ten = board.Counter() / 10;
                                            one = board.Counter() % 10;
                                            counter2.changeSprite(numbers.getDigit(ten * -1));
                                            counter3.changeSprite(numbers.getDigit(one * -1));
                                            gameWindow.draw(counter2.open());
                                            gameWindow.draw(counter3.open());


                                        } else {
                                            negCounter = false;
                                            ten = board.Counter() / 10;
                                            one = board.Counter() % 10;
                                            counter2.changeSprite(numbers.getDigit(ten));
                                            counter3.changeSprite(numbers.getDigit(one));
                                            gameWindow.draw(counter2.open());
                                            gameWindow.draw(counter3.open());
                                            if (board.tiles[i][j].flagged && board.tiles[i][j].mine &&
                                                board.Counter() == 0) {
                                                paused = true;
                                                won = true;
                                                temp_bool = true;

                                            }

                                        }
                                    } else {
                                        if (!board.tiles[i][j].found and !lost and !won) {
                                            board.tiles[i][j].setSprite(textures.getTexture("hidden"));
                                            board.tiles[i][j].flagged = false;
                                            board.covered--;

                                            if (board.Counter() < 0) {
                                                negCounter = true;
                                                ten = board.Counter() / 10;
                                                one = board.Counter() % 10;

                                                counter2.changeSprite(numbers.getDigit(ten * -1));
                                                counter3.changeSprite(numbers.getDigit(one * -1));
                                                negative.changeSprite(numbers.getDigit(10));
                                                gameWindow.draw(counter2.open());
                                                gameWindow.draw(counter3.open());
                                                gameWindow.draw(negative.open());
                                            } else {
                                                negCounter = false;
                                                ten = board.Counter() / 10;
                                                one = board.Counter() % 10;
                                                counter2.changeSprite(numbers.getDigit(ten));
                                                counter3.changeSprite(numbers.getDigit(one));
                                                gameWindow.draw(counter2.open());
                                                gameWindow.draw(counter3.open());
                                            }
                                        }


                                    }
                                }

                            }
                        }
                    }
                }
            }
        }

        gameWindow.clear(sf::Color::White);
        for (int i = 0; i < board.col; i++) {
            for (int j = 0; j < board.row; j++) {
                board.tiles[i][j].background.setPosition(32 * i, 32 * j);
                board.tiles[i][j].sprite.setPosition(32 * i, 32 * j);
                gameWindow.draw(board.tiles[i][j].background);
                gameWindow.draw(board.tiles[i][j].sprite);

            }

        }

        auto gameTime = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
        int minutes;
        int seconds;
        totalTime = gameTime.count();

        if (!paused) {
            totalTime -= elapsed_time;
            minutes = totalTime / 60;
            seconds = totalTime % 60;
        }


        int min0 = minutes / 10 % 10;
        int min1 = minutes % 10;
        int sec0 = seconds / 10 % 10;
        int sec1 = seconds % 10;
        if (won and temp_bool) {
            board.placeFlag();
            string time_min0 = to_string(min0);
            string time_min1 = to_string(min1);
            string time_sec0 = to_string(sec0);
            string time_sec1 = to_string(sec1);
            string winnerTime = time_min0 + time_min1 + ":" + time_sec0 + time_sec1;

            players[winnerTime] = name;
            times.clear();
            names.clear();
            for (auto it = players.begin(); it != players.end(); ++it) {

                times.push_back(it->first);
                names.push_back(it->second);
            }
            placement = string("1.") + "\t" + times[0] + "\t" + names[0] + "\n\n" + "2." + "\t" + times[1] + "\t" +
                        names[1] + "\n\n" +
                        "3." + "\t" + times[2] + "\t" + names[2] + "\n\n" + "4." + "\t" + times[3] + "\t" + names[3] +
                        "\n\n" +
                        "5." + "\t" + times[4] + "\t" + names[4];
            sf::RenderWindow leaderWindow(sf::VideoMode(16 * col, (16 * row) + 50), "Leaderboard");
            while (leaderWindow.isOpen()) {

                sf::Event event;
                while (leaderWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        leaderWindow.close();
                        leader_open = false;
                        temp_bool = false;
                    }

                    sf::Text leaderTitle("LEADERBOARD", font, 20);
                    leaderTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
                    setText(leaderTitle, (16 * col) / 2.0f, ((row * 16) + 50) / 2.0f - 120);

                    sf::Text leaderText(placement, font, 20);
                    leaderText.setCharacterSize(18);
                    leaderText.setStyle(sf::Text::Bold);
                    setText(leaderText, (16 * col) / 2.0f, ((row * 16) + 50) / 2.0f + 20);

                    leaderWindow.clear(sf::Color::Blue);
                    leaderWindow.draw(leaderTitle);
                    leaderWindow.draw(leaderText);
                    leaderWindow.display();
                }

            }
            }
        int totalMin = min0+min1+sec1+sec0;
        if (totalMin >= 0 or 36 >= totalMin) {
            tenth_min.sprite.setTexture(numbers.getDigit(min0));
            min.sprite.setTexture(numbers.getDigit(min1));
            tenth_sec.sprite.setTexture(numbers.getDigit(sec0));
            sec.sprite.setTexture(numbers.getDigit(sec1));
            gameWindow.draw(tenth_min.returnSprite());
            gameWindow.draw(min.returnSprite());
            gameWindow.draw(tenth_sec.returnSprite());
            gameWindow.draw(sec.returnSprite());
        }


        if (!paused) {

                gameWindow.draw(pause.open());


            } else {
                gameWindow.draw(play.open());
            }


            if (negCounter) {
                gameWindow.draw(negative.open());

            }


            gameWindow.draw(debug.open());
            gameWindow.draw(leaderboard.open());
            gameWindow.draw(counter.open());
            gameWindow.draw(counter2.open());
            gameWindow.draw(counter3.open());

        if (!lost and !won) {
            gameWindow.draw(happy.open());

        }
        else if (won) {
            gameWindow.draw(cool.open());
            board.placeFlag();
        }
        else {
            gameWindow.draw(sad.open());

        }


            gameWindow.display();

        }
        ofstream outfile("files/leaderboard.txt");
        if (outfile.is_open()) {
            for (auto &it: players) {
                outfile << it.first << "," << it.second << endl;
            }
            outfile.close();

        }

        return 0;
}

