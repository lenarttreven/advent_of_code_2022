//
// Created by Lenart Treven on 22.12.22.
//

#include "day_8.h"


#include <utility>
#include <vector>
#include <iostream>


using namespace std;


int scenic_score(vector<vector<int>> *tree_map, int x_pos, int y_pos) {
    int num_cols = (*tree_map)[0].size();
    int num_rows = (*tree_map).size();

    int maximal_tree = (*tree_map)[y_pos][x_pos];

    int num_above = 0;
    for (int i = y_pos - 1; i >= 0; i--) {
        num_above += 1;
        if ((*tree_map)[i][x_pos] >= maximal_tree) {
            break;
        }
    }

    int num_below = 0;
    for (int i = y_pos + 1; i < num_rows; i++) {
        num_below += 1;
        if ((*tree_map)[i][x_pos] >= maximal_tree) {
            break;
        }
    }

    int num_left = 0;
    for (int i = x_pos - 1; i >= 0; i--) {
        num_left += 1;
        if ((*tree_map)[y_pos][i] >= maximal_tree) {
            break;
        }
    }
    int num_right = 0;
    for (int i = x_pos + 1; i < num_cols; i++) {
        num_right += 1;
        if ((*tree_map)[y_pos][i] >= maximal_tree) {
            break;
        }
    }
    return num_above * num_below * num_left * num_right;
}


int find_visible_trees(vector<vector<int>> *tree_map) {
    vector<vector<bool>> is_visible_map;
    for (int i = 0; i < (*tree_map).size(); i++) {
        vector<bool> current_line;
        for (int j = 0; j < (*tree_map)[0].size(); j++) {
            current_line.push_back(false);
        }
        is_visible_map.push_back(current_line);
        current_line = {};
    }
    vector<int> maximal_height_up((*tree_map)[0].size(), -1);
    for (int i = 0; i < (*tree_map).size(); i++) {
        for (int j = 0; j < (*tree_map)[0].size(); j++) {
            if ((*tree_map)[i][j] > maximal_height_up[j]) {
                maximal_height_up[j] = (*tree_map)[i][j];
                is_visible_map[i][j] = true;
            }
        }
    }

    vector<int> maximal_height_down((*tree_map)[0].size(), -1);
    for (int i = (*tree_map).size() - 1; i >= 0; i--) {
        for (int j = 0; j < (*tree_map)[0].size(); j++) {
            if ((*tree_map)[i][j] > maximal_height_down[j]) {
                maximal_height_down[j] = (*tree_map)[i][j];
                is_visible_map[i][j] = true;
            }
        }
    }

    vector<int> maximal_height_left((*tree_map).size(), -1);
    for (int j = 0; j < (*tree_map)[0].size(); j++) {
        for (int i = 0; i < (*tree_map).size(); i++) {
            if ((*tree_map)[i][j] > maximal_height_left[i]) {
                maximal_height_left[i] = (*tree_map)[i][j];
                is_visible_map[i][j] = true;
            }
        }
    }

    vector<int> maximal_height_right((*tree_map).size(), -1);
    for (int j = (*tree_map)[0].size() - 1; j >= 0; j--) {
        for (int i = 0; i < (*tree_map).size(); i++) {
            if ((*tree_map)[i][j] > maximal_height_right[i]) {
                maximal_height_right[i] = (*tree_map)[i][j];
                is_visible_map[i][j] = true;
            }
        }
    }
    int total_visible = 0;
    for (int i = 0; i < (*tree_map).size(); i++) {
        for (int j = 0; j < (*tree_map)[0].size(); j++) {
            if (is_visible_map[i][j]) {
                total_visible += 1;
            }
        }
    }
    return total_visible;
}

int highest_scenic_score(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    vector<vector<int>> tree_map;

    while (getline(MyReadFile, line_text)) {
        vector<int> current_line;
        for (char c: line_text) {
            int cur_number = c - '0';
            current_line.push_back(cur_number);
        }
        tree_map.push_back(current_line);
        current_line = {};
    }

    int highest_score = -1;
    for (int i = 0; i < tree_map.size(); i++) {
        for (int j = 0; j < tree_map[0].size(); j++) {
            int current_score = scenic_score(&tree_map, j, i);
            if (current_score > highest_score) {
                highest_score = current_score;
            }
        }
    }
    return highest_score;
}

int num_visible_trees(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    vector<vector<int>> tree_map;

    while (getline(MyReadFile, line_text)) {
        vector<int> current_line;
        for (char c: line_text) {
            int cur_number = c - '0';
            current_line.push_back(cur_number);
        }
        tree_map.push_back(current_line);
        current_line = {};
    }
    int to_return = find_visible_trees(&tree_map);
    return to_return;
}