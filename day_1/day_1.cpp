//
// Created by Lenart Treven on 20.12.22.
//

#include "day_1.h"
#include <string>
#include <vector>
#include <iostream>


using namespace std;


int largest_elf(string *filename) {
    int maximal_elf_size = -1;
    ifstream MyReadFile(*filename);
    string line_text;
    int current_sum = 0;
    while (getline(MyReadFile, line_text)) {
        if (line_text.empty()) {
            if (current_sum >= maximal_elf_size) {
                maximal_elf_size = current_sum;
            }
            current_sum = 0;
        } else {
            current_sum += stoi(line_text);
        }
    }
    if (current_sum >= maximal_elf_size) {
        maximal_elf_size = current_sum;
    }
    return maximal_elf_size;
}

int top_three_elfs(string *filename) {
    vector<int> elfs;
    ifstream MyReadFile(*filename);
    string line_text;
    int current_sum = 0;
    while (getline(MyReadFile, line_text)) {
        if (line_text.empty()) {
            elfs.push_back(current_sum);
            current_sum = 0;
        } else {
            current_sum += stoi(line_text);
        }
    }
    elfs.push_back(current_sum);
    sort(elfs.begin(), elfs.end(), greater<int>());
    return elfs[0] + elfs[1] + elfs[2];
}