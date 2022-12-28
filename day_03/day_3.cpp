//
// Created by Lenart Treven on 20.12.22.
//

#include "day_3.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;


int convert_to_num(char c) {
    if (islower(c)) {
        int ic = (c - 'a') + 1;
        return ic;
    } else {
        int ic = (c - 'A') + 1 + 26;
        return ic;
    }
}

char find_char_in_both(string *string_1, string *string_2) {
    for (char c: *string_1) {
        if ((*string_2).contains(c)) {
            return c;
        }
    }
    return 'a';
}

char find_char_in_all(string *string_1, string *string_2, string *string_3) {
    for (char c: *string_1) {
        if ((*string_2).contains(c) & (*string_3).contains(c)) {
            return c;
        }
    }
    return 'a';
}

int priorities_of_repeated_items(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    int total_points = 0;

    while (getline(MyReadFile, line_text)) {
        int num_items = line_text.size();
        string first_part = line_text.substr(0, num_items / 2);
        string second_part = line_text.substr(num_items / 2, num_items);
        char common_item = find_char_in_both(&first_part, &second_part);
        total_points += convert_to_num(common_item);
    }

    return total_points;
}

int badges_for_grouping(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    int total_points = 0;
    vector<string> elf_badges = {};
    int counter = 0;
    while (getline(MyReadFile, line_text)) {
        counter += 1;
        elf_badges.push_back(line_text);
        if (counter % 3 == 0) {
            char common_badge = find_char_in_all(&elf_badges[0], &elf_badges[1], &elf_badges[2]);
            total_points += convert_to_num(common_badge);
            elf_badges = {};
        }
    }
    return total_points;
}

