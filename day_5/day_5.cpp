//
// Created by Lenart Treven on 20.12.22.
//

#include "day_5.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;


vector<char> parse_cargo_line(string *line) {
    vector<char> parsed_line;
    for (int i = 0; i < (*line).size(); i++) {
        if (i % 4 == 1) {
            parsed_line.push_back((*line)[i]);
        }
    }
    return parsed_line;
}

vector<int> parse_instructions(string *line) {
    vector<int> instruction;
    string current_int;
    bool in_num = false;
    for (char c: *line) {
        if (isdigit(c) & in_num) {
            current_int.push_back(c);
        } else if (isdigit(c) & !in_num) {
            current_int.push_back(c);
            in_num = true;
        } else if (!isdigit(c) & in_num) {
            instruction.push_back(stoi(current_int));
            in_num = false;
            current_int = "";
        }
    }
    instruction.push_back(stoi(current_int));
    return instruction;
}


void apply_instruction(map<int, vector<char>> *cargo_map, vector<int> *instruction) {
    int num_pieces_to_move = (*instruction)[0];
    int move_from = (*instruction)[1] - 1;
    int move_to = (*instruction)[2] - 1;
    for (int i = 0; i < num_pieces_to_move; i++) {
        char cur_elem = (*cargo_map)[move_from].back();
        (*cargo_map)[move_to].push_back(cur_elem);
        (*cargo_map)[move_from].pop_back();
    }
}


string top_crates(string *filename, int num_stacks, int highest_stack) {
    ifstream MyReadFile(*filename);
    string line_text;
    map<int, vector<char>> cargo_map;
    for (int i = 0; i < highest_stack; i++) {
        getline(MyReadFile, line_text);
        vector<char> parsed_line = parse_cargo_line(&line_text);
        for (int j = 0; j < num_stacks; j++) {
            if (parsed_line[j] != ' ') {
                cargo_map[j].push_back(parsed_line[j]);
            }
        }
    }
    for (int j = 0; j < num_stacks; j++) {
        reverse(cargo_map[j].begin(), cargo_map[j].end());
    }
    getline(MyReadFile, line_text);
    getline(MyReadFile, line_text);
    while (getline(MyReadFile, line_text)) {
        vector<int> instruction = parse_instructions(&line_text);
        apply_instruction(&cargo_map, &instruction);
    }
    string to_elements;
    for (int i = 0; i < num_stacks; i++) {
        to_elements.push_back(cargo_map[i].back());
    }
    return to_elements;
}

void apply_instruction_9001(map<int, vector<char>> *cargo_map, vector<int> *instruction) {
    int num_pieces_to_move = (*instruction)[0];
    int move_from = (*instruction)[1] - 1;
    int move_to = (*instruction)[2] - 1;
    vector<char> intermediate_layer;
    for (int i = 0; i < num_pieces_to_move; i++) {
        char cur_elem = (*cargo_map)[move_from].back();
        intermediate_layer.push_back(cur_elem);
        (*cargo_map)[move_from].pop_back();
    }
    for (int i = 0; i < num_pieces_to_move; i++) {
        char cur_elem = intermediate_layer.back();
        (*cargo_map)[move_to].push_back(cur_elem);
        intermediate_layer.pop_back();
    }

}

string top_crates_9001(string *filename, int num_stacks, int highest_stack) {
    ifstream MyReadFile(*filename);
    string line_text;
    map<int, vector<char>> cargo_map;
    for (int i = 0; i < highest_stack; i++) {
        getline(MyReadFile, line_text);
        vector<char> parsed_line = parse_cargo_line(&line_text);
        for (int j = 0; j < num_stacks; j++) {
            if (parsed_line[j] != ' ') {
                cargo_map[j].push_back(parsed_line[j]);
            }
        }
    }
    for (int j = 0; j < num_stacks; j++) {
        reverse(cargo_map[j].begin(), cargo_map[j].end());
    }
    getline(MyReadFile, line_text);
    getline(MyReadFile, line_text);
    while (getline(MyReadFile, line_text)) {
        vector<int> instruction = parse_instructions(&line_text);
        apply_instruction_9001(&cargo_map, &instruction);
    }
    string to_elements;
    for (int i = 0; i < num_stacks; i++) {
        to_elements.push_back(cargo_map[i].back());
    }
    return to_elements;
}