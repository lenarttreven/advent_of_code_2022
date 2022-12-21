//
// Created by Lenart Treven on 21.12.22.
//

#include "day_6.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <deque>
#include <set>


using namespace std;


int decode_position(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    getline(MyReadFile, line_text);
    deque<char> last_four;
    int position = 0;
    for (char c: line_text) {
        position += 1;
        last_four.push_back(c);
        if (last_four.size() > 14) {
            last_four.pop_front();
        }
        set<char> cur_set;
        for (char i: last_four) {
            cur_set.insert(i);
        }
        if (cur_set.size() >= 14) {
            return position;
        }
    }
    return 0;
}