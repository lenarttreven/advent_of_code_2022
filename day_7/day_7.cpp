//
// Created by Lenart Treven on 21.12.22.
//

#include "day_7.h"


#include <string>
#include <utility>
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <fstream>
#include <deque>
#include <set>


using namespace std;


class File {
public:
    File *parent;
    vector<File *> children;
    int size = -1;
    string name;
    bool is_dir = false;

    File(string file_name = "Root", int file_size = -1, bool dir = true) {
        parent = nullptr;
        name = std::move(file_name);
        size = file_size;
        is_dir = dir;
    }

    void add_size(int size);

    void add_child(File *new_child);

    void add_parent(File *new_parent);
};

void File::add_size(int new_size) {
    File::size = new_size;
}

void File::add_child(File *new_child) {
    File::children.push_back(new_child);
}

void File::add_parent(File *new_parent) {
    File::parent = new_parent;
}


class FileSystem {
public:
    File *current_file;
    File *root_file;

    explicit FileSystem(File *new_root_file) {
        current_file = new_root_file;
        root_file = new_root_file;
    }

    void move_down(string *name) {
        for (File *child: (*current_file).children) {
            if ((*child).name == *name) {
                current_file = child;
            }
        }
    }

    void move_up() {
        current_file = (*current_file).parent;
    }

    void move_to_root() {
        current_file = root_file;
    }

    void compute_sizes();

    int small_files(int max_size);

    vector<int> all_sizes();
};

vector<int> FileSystem::all_sizes() {
    vector<int> total_sizes;
    vector<File *> stack;
    File *root_file = FileSystem::root_file;
    stack.push_back(root_file);
    while (!stack.empty()) {
        File *file_to_check = stack.back();
        if ((*file_to_check).size != -1) {
            if ((*file_to_check).is_dir) {
                total_sizes.push_back((*file_to_check).size);
            }
            stack.pop_back();
            continue;
        }
        bool all_children_have_size = true;
        int size = 0;
        for (File *child: (*file_to_check).children) {
            size += (*child).size;
            if ((*child).size == -1) {
                all_children_have_size = false;
                stack.push_back(child);
            }
        }
        if (all_children_have_size) {
            (*file_to_check).size = size;
        }
    }
    return total_sizes;
}


int FileSystem::small_files(int max_size) {
    int total_size = 0;
    vector<File *> stack;
    File *root_file = FileSystem::root_file;
    stack.push_back(root_file);
    while (!stack.empty()) {
        File *file_to_check = stack.back();
        if ((*file_to_check).size != -1) {
            if ((*file_to_check).is_dir & (*file_to_check).size <= max_size) {
                total_size += (*file_to_check).size;
            }
            stack.pop_back();
            continue;
        }
        bool all_children_have_size = true;
        int size = 0;
        for (File *child: (*file_to_check).children) {
            size += (*child).size;
            if ((*child).size == -1) {
                all_children_have_size = false;
                stack.push_back(child);
            }
        }
        if (all_children_have_size) {
            (*file_to_check).size = size;
        }
    }
    return total_size;
}


void FileSystem::compute_sizes() {
    vector<File *> stack;
    File *root_file = FileSystem::root_file;
    stack.push_back(root_file);
    while (!stack.empty()) {
        File *file_to_check = stack.back();
        if ((*file_to_check).size != -1) {
            stack.pop_back();
            continue;
        }
        bool all_children_have_size = true;
        int size = 0;
        for (File *child: (*file_to_check).children) {
            size += (*child).size;
            if ((*child).size == -1) {
                all_children_have_size = false;
                stack.push_back(child);
            }
        }
        if (all_children_have_size) {
            (*file_to_check).size = size;
        }
    }
}

tuple<int, string, bool> parse_file_line(string *line) {
    vector<string> parsed_line;
    string current_str;
    for (char c: *line) {
        if (c == ' ') {
            parsed_line.push_back(current_str);
            current_str = "";
        } else {
            current_str.push_back(c);
        }

    }
    parsed_line.push_back(current_str);
    if (parsed_line[0] == "dir") {
        return {-1, parsed_line[1], true};
    } else {
        return {stoi(parsed_line[0]), parsed_line[1], false};
    }
}

string get_subfolder(string *line) {
    vector<string> parsed_line;
    string current_str;
    for (char c: *line) {
        if (c == ' ') {
            parsed_line.push_back(current_str);
            current_str = "";
        } else {
            current_str.push_back(c);
        }
    }
    parsed_line.push_back(current_str);
    return parsed_line.back();
}

int smallest_directory_for_delete(string *filename, int total_disk_space, int space_for_update) {
    ifstream MyReadFile(*filename);
    string line_text;

    getline(MyReadFile, line_text);
    list<File> files;

    auto root_file = File();
    auto file_system = FileSystem(&root_file);


    while (getline(MyReadFile, line_text)) {
        if (line_text[0] != '$') {
            tuple<int, string, bool> parsed_line = parse_file_line(&line_text);
            auto file = File(get<1>(parsed_line), get<0>(parsed_line), get<2>(parsed_line));
            files.push_back(file);
            (*file_system.current_file).add_child(&files.back());
            files.back().add_parent(file_system.current_file);
        } else if (line_text == "$ cd /") {
            file_system.move_to_root();
        } else if (line_text == "$ cd ..") {
            file_system.move_up();
        } else if (line_text == "$ ls") {
            continue;
        } else {
            string move_to = get_subfolder(&line_text);
            file_system.move_down(&move_to);
        }
    }
    file_system.move_to_root();
    vector<int> to_return = file_system.all_sizes();
    int smallest_directory = total_disk_space;
    int free_space = total_disk_space - (*file_system.root_file).size;
    for (int dir_size: to_return) {
        if (free_space + dir_size >= space_for_update & dir_size <= smallest_directory) {
            smallest_directory = dir_size;
        }
    }
    return smallest_directory;
}

int find_small_directories(string *filename, int max_size) {
    ifstream MyReadFile(*filename);
    string line_text;

    getline(MyReadFile, line_text);
    list<File> files;

    auto root_file = File();
    auto file_system = FileSystem(&root_file);


    while (getline(MyReadFile, line_text)) {
        if (line_text[0] != '$') {
            tuple<int, string, bool> parsed_line = parse_file_line(&line_text);
            auto file = File(get<1>(parsed_line), get<0>(parsed_line), get<2>(parsed_line));
            files.push_back(file);
            (*file_system.current_file).add_child(&files.back());
            files.back().add_parent(file_system.current_file);
        } else if (line_text == "$ cd /") {
            file_system.move_to_root();
        } else if (line_text == "$ cd ..") {
            file_system.move_up();
        } else if (line_text == "$ ls") {
            continue;
        } else {
            string move_to = get_subfolder(&line_text);
            file_system.move_down(&move_to);
        }
    }
    file_system.move_to_root();
    int to_return = file_system.small_files(max_size);
    int x = 7;
    return to_return;
}

