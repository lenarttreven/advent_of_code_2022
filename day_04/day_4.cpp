//
// Created by Lenart Treven on 20.12.22.
//

#include "day_4.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Pair {
public:
    tuple<int, int> section_1;
    tuple<int, int> section_2;

    Pair(tuple<int, int> fst, tuple<int, int> snd) {
        section_1 = std::move(fst);
        section_2 = std::move(snd);
    }

    bool redundant();

    bool overlap();
};

bool Pair::redundant() {
    if (get<0>(Pair::section_1) <= get<0>(Pair::section_2) &
        get<1>(Pair::section_1) >= get<1>(Pair::section_2)) {
        return true;
    } else if (get<0>(Pair::section_2) <= get<0>(Pair::section_1) &
               get<1>(Pair::section_2) >= get<1>(Pair::section_1)) {
        return true;
    }
    return false;
}

bool Pair::overlap() {
    if (get<0>(Pair::section_1) <= get<0>(Pair::section_2) &
        get<0>(Pair::section_2) <= get<1>(Pair::section_1)) {
        return true;
    } else if (get<0>(Pair::section_2) <= get<0>(Pair::section_1) &
               get<0>(Pair::section_1) <= get<1>(Pair::section_2)) {
        return true;
    }
    return false;
}


Pair parse_line(string *linetext) {
    vector<int> nums;
    string current_num;
    for (char c: *linetext) {
        if (isdigit(c)) {
            current_num.push_back(c);
        } else {
            nums.push_back(stoi(current_num));
            current_num = "";
        }
    }
    nums.push_back(stoi(current_num));
    tuple<int, int> first_range = {nums[0], nums[1]};
    tuple<int, int> second_range = {nums[2], nums[3]};
    return {first_range, second_range};
}


int number_of_contained_pairs(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    int num_pairs = 0;
    while (getline(MyReadFile, line_text)) {
        Pair parsed_line = parse_line(&line_text);
        if (parsed_line.redundant()) {
            num_pairs += 1;
        }
    }
    return num_pairs;
}

int number_of_overlapping_elfs(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    int num_pairs = 0;
    while (getline(MyReadFile, line_text)) {
        Pair parsed_line = parse_line(&line_text);
        if (parsed_line.overlap()) {
            num_pairs += 1;
        }
    }
    return num_pairs;
}