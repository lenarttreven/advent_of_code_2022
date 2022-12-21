//
// Created by Lenart Treven on 21.12.22.
//

#ifndef ADVENT_OF_CODE_2022_DAY_7_H
#define ADVENT_OF_CODE_2022_DAY_7_H

#endif //ADVENT_OF_CODE_2022_DAY_7_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <deque>
#include <set>

using namespace std;

int small_file_system(string *filename);
int find_small_directories(string *filename, int max_size);
int smallest_directory_for_delete(string *filename, int total_disk_space, int space_for_update);