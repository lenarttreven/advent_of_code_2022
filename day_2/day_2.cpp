//
// Created by Lenart Treven on 20.12.22.
//

#include "day_2.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;


int score_of_strategy(string *filename){
    map<string, int> point_decoder;
    point_decoder["A X"] = 1 + 3;
    point_decoder["A Y"] = 2 + 6;
    point_decoder["A Z"] = 3 + 0;
    point_decoder["B X"] = 1 + 0;
    point_decoder["B Y"] = 2 + 3;
    point_decoder["B Z"] = 3 + 6;
    point_decoder["C X"] = 1 + 6;
    point_decoder["C Y"] = 2 + 0;
    point_decoder["C Z"] = 3 + 3;

    ifstream MyReadFile(*filename);
    string line_text;
    int total_points = 0;

    while (getline(MyReadFile, line_text)) {
        total_points += point_decoder[line_text];
    }
    return total_points;
}


int smart_strategy(string *filename){
    map<string, int> point_decoder;
    point_decoder["A X"] = 3 + 0;
    point_decoder["A Y"] = 1 + 3;
    point_decoder["A Z"] = 2 + 6;

    point_decoder["B X"] = 1 + 0;
    point_decoder["B Y"] = 2 + 3;
    point_decoder["B Z"] = 3 + 6;

    point_decoder["C X"] = 2 + 0;
    point_decoder["C Y"] = 3 + 3;
    point_decoder["C Z"] = 1 + 6;

    ifstream MyReadFile(*filename);
    string line_text;
    int total_points = 0;

    while (getline(MyReadFile, line_text)) {
        total_points += point_decoder[line_text];
    }
    return total_points;
}