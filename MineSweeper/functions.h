#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
using namespace std;


vector<float> read(string filename) {
    ifstream file(filename, ios_base::in);
    float num;
    vector<float> config;
    while (file >> num) {
        config.push_back(num);
    }
    return config;
}


