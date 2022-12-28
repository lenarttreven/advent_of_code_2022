//
// Created by Lenart Treven on 24.12.22.
//

#include "day_10.h"
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <deque>
#include <queue>

using namespace std;

vector<int> parse_signal_line(string *line) {
    vector<string> command;
    vector<int> int_command;
    string cur_string;
    for (char c: *line) {
        if (c == ' ') {
            command.push_back(cur_string);
            cur_string = "";
        } else {
            cur_string.push_back(c);
        }
    }
    command.push_back(cur_string);
    if (command[0] == "noop") {
        int_command = {1, 0};
    } else if (command[0] == "addx") {
        int_command = {2, stoi(command[1])};
    }
    return int_command;
}


int decode_signal_strength(string *filename) {
    queue<vector<int>> commands;

    ifstream MyReadFile(*filename);
    string line_text;

    while (getline(MyReadFile, line_text)) {
        vector<int> command = parse_signal_line(&line_text);
        commands.push(command);
    }

    int time = 1;
    int x = 1;
    int my_sum = 0;
    while (!commands.empty()) {
        vector<int> current_command = commands.front();
        for (int i = 0; i < current_command[0]; i++) {
            if (time % 40 == 20) {
                my_sum += time * x;
            }
            time += 1;
        }
        x += current_command[1];
        commands.pop();
    }

    return my_sum;
}

vector<string> draw_code(string *filename) {
    queue<vector<int>> commands;

    ifstream MyReadFile(*filename);
    string line_text;
    // Parse commands
    while (getline(MyReadFile, line_text)) {
        vector<int> command = parse_signal_line(&line_text);
        commands.push(command);
    }
    // Execute commands
    vector<string> drawing;
    int time = 0;
    int x_pos = 1;
    string current_line;
    while (!commands.empty()) {
        vector<int> current_command = commands.front();
        for (int i = 0; i < current_command[0]; i++) {
            //  Do the calculations
            if (abs(time - x_pos) <= 1) {
                current_line.push_back('#');
            } else {
                current_line.push_back('.');
            }
            time += 1;
            if (time == 40) {
                time = 0;
                drawing.push_back(current_line);
                current_line = "";
            }
        }
        x_pos += current_command[1];
        commands.pop();
    }
    return drawing;
}