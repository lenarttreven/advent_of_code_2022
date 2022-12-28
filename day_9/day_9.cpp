//
// Created by Lenart Treven on 23.12.22.
//

#include "day_9.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

int distance(tuple<int, int> fst, tuple<int, int> snd) {
    return max(abs(get<0>(fst) - get<0>(snd)), abs(get<1>(fst) - get<1>(snd)));
}

tuple<int, int> move(tuple<int, int> position, char command) {
    int new_x = get<0>(position);
    int new_y = get<1>(position);
    if (command == 'R') {
        new_x += 1;
    } else if (command == 'L') {
        new_x -= 1;
    } else if (command == 'U') {
        new_y += 1;
    } else if (command == 'D') {
        new_y -= 1;
    }
    return {new_x, new_y};
}

tuple<int, int> follow(tuple<int, int> tail, tuple<int, int> head) {
    if (distance(tail, head) <= 1) {
        return tail;
    } else if (get<0>(tail) == get<0>(head) & get<1>(tail) == get<1>(head) + 2) {
        return {get<0>(tail), get<1>(tail) - 1};
    } else if (get<0>(tail) == get<0>(head) & get<1>(tail) == get<1>(head) - 2) {
        return {get<0>(tail), get<1>(tail) + 1};
    } else if (get<0>(tail) == get<0>(head) - 2 & get<1>(tail) == get<1>(head)) {
        return {get<0>(tail) + 1, get<1>(tail)};
    } else if (get<0>(tail) == get<0>(head) + 2 & get<1>(tail) == get<1>(head)) {
        return {get<0>(tail) - 1, get<1>(tail)};
    } else if (get<0>(tail) < get<0>(head) & get<1>(tail) < get<1>(head)) {
        return {get<0>(tail) + 1, get<1>(tail) + 1};
    } else if (get<0>(tail) < get<0>(head) & get<1>(tail) > get<1>(head)) {
        return {get<0>(tail) + 1, get<1>(tail) - 1};
    } else if (get<0>(tail) > get<0>(head) & get<1>(tail) > get<1>(head)) {
        return {get<0>(tail) - 1, get<1>(tail) - 1};
    } else if (get<0>(tail) > get<0>(head) & get<1>(tail) < get<1>(head)) {
        return {get<0>(tail) - 1, get<1>(tail) + 1};
    }
    return {0, 0};
}

tuple<char, int> get_command(string *line) {
    char direction = (*line)[0];
    string num_steps;
    for (int i = 2; i < (*line).size(); i++) {
        num_steps.push_back((*line)[i]);
    }
    return {direction, stoi(num_steps)};
}


int unique_places(string *filename) {
    set<tuple<int, int>> visited_places;

    tuple<int, int> tail = {0, 0};
    tuple<int, int> head = {0, 0};
    visited_places.insert(tail);

    ifstream MyReadFile(*filename);
    string line_text;

    while (getline(MyReadFile, line_text)) {
        tuple<char, int> command = get_command(&line_text);
        for (int i = 0; i < get<1>(command); i++) {
            head = move(head, get<0>(command));
            tail = follow(tail, head);
            visited_places.insert(tail);
        }
    }
    return visited_places.size();
}


int long_rope(string *filename) {
    set<tuple<int, int>> visited_places;
    vector<tuple<int, int>> knots;
    for (int i = 0; i < 9; i++) {
        knots.emplace_back(0, 0);
    }
    visited_places.insert(knots[8]);

    ifstream MyReadFile(*filename);
    string line_text;

    while (getline(MyReadFile, line_text)) {
        tuple<char, int> command = get_command(&line_text);
        for (int i = 0; i < get<1>(command); i++) {
            knots[0] = move(knots[0], get<0>(command));
            for (int j = 1; j < 10; j++) {
                knots[j] = follow(knots[j], knots[j - 1]);
            }
            visited_places.insert(knots[9]);
        }
    }
    return visited_places.size();
}