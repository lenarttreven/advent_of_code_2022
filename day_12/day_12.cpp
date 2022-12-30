//
// Created by Lenart Treven on 29.12.22.
//

#include "day_12.h"
#include <iostream>
#include <string>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <deque>
#include <queue>

using namespace std;

using node_type = tuple<int, int>;
using graph_type = map<node_type, vector<node_type>>;


vector<tuple<int, int>> prepare_neighbours(int i, int j, vector<string> *map) {
    vector<tuple<int, int>> neighbours;
    char node = (*map)[i][j];
    if (i == 0) {
        char cur_char = (*map)[i + 1][j];
        if (int(cur_char - node) <= 1) {
            neighbours.emplace_back(i + 1, j);
        }
    } else if (i == (*map).size() - 1) {
        char cur_char = (*map)[i - 1][j];
        if (int(cur_char - node) <= 1) {
            neighbours.emplace_back(i - 1, j);
        }
    } else {
        char right_char = (*map)[i + 1][j];
        if (int(right_char - node) <= 1) {
            neighbours.emplace_back(i + 1, j);
        }
        char left_char = (*map)[i - 1][j];
        if (int(left_char - node) <= 1) {
            neighbours.emplace_back(i - 1, j);
        }
    }

    if (j == 0) {
        char cur_char = (*map)[i][j + 1];
        if (int(cur_char - node) <= 1) {
            neighbours.emplace_back(i, j + 1);
        }
    } else if (j == (*map)[0].size() - 1) {
        char cur_char = (*map)[i][j - 1];
        if (int(cur_char - node) <= 1) {
            neighbours.emplace_back(i, j - 1);
        }
    } else {
        char top_char = (*map)[i][j + 1];
        if (int(top_char - node) <= 1) {
            neighbours.emplace_back(i, j + 1);
        }
        char bottom_char = (*map)[i][j - 1];
        if (int(bottom_char - node) <= 1) {
            neighbours.emplace_back(i, j - 1);
        }
    }

    return neighbours;
}

tuple<graph_type, vector<node_type>, node_type> from_map_to_graph(vector<string> *map) {
    graph_type my_graph;
    vector<node_type> start_nodes;
    node_type end_node;

    for (int i = 0; i < (*map).size(); i++) {
        for (int j = 0; j < (*map)[0].size(); j++) {
            if ((*map)[i][j] == 'S') {
                (*map)[i][j] = 'a';
                start_nodes.emplace_back(i, j);
            } else if ((*map)[i][j] == 'E') {
                (*map)[i][j] = 'z';
                end_node = {i, j};
            } else if ((*map)[i][j] == 'a') {
                start_nodes.emplace_back(i, j);
            }
        }
    }

    for (int i = 0; i < (*map).size(); i++) {
        for (int j = 0; j < (*map)[0].size(); j++) {
            my_graph.insert({{i, j}, prepare_neighbours(i, j, map)});
        }
    }
    return {my_graph, start_nodes, end_node};
}

int fewest_steps_to_reach_top(string *filename) {
    vector<string> map;

    ifstream MyReadFile(*filename);
    string line_text;

    while (getline(MyReadFile, line_text)) {
        map.push_back(line_text);
    }

    tuple<graph_type, vector<node_type>, node_type> to_parse = from_map_to_graph(&map);
    graph_type graph = get<0>(to_parse);
    vector<node_type> start_nodes = get<1>(to_parse);
    node_type end_node = get<2>(to_parse);

    vector<vector<bool>> visited;
    for (int i = 0; i < map.size(); i++) {
        vector<bool> init_visited(map[0].size(), false);
        visited.push_back(init_visited);
    }

    vector<vector<int>> distances;
    for (int i = 0; i < map.size(); i++) {
        vector<int> init_visited(map[0].size(), 0);
        distances.push_back(init_visited);
    }

    vector<node_type> current_nodes;

    for (node_type node: start_nodes) {
        current_nodes.push_back(node);
        visited[get<0>(node)][get<1>(node)] = true;
    }

    for (int distance = 0; distance < graph.size(); distance++) {
        vector<node_type> new_nodes;
        for (node_type node: current_nodes) {
            vector<node_type> potential_neighbours = graph[node];
            for (node_type potential_neighbour: potential_neighbours) {
                if (not visited[get<0>(potential_neighbour)][get<1>(potential_neighbour)]) {
                    visited[get<0>(potential_neighbour)][get<1>(potential_neighbour)] = true;
                    distances[get<0>(potential_neighbour)][get<1>(potential_neighbour)] = distance + 1;
                    new_nodes.push_back(potential_neighbour);
                }
                if (potential_neighbour == end_node) {
                    return distance + 1;
                }
            }
        }
        current_nodes = new_nodes;
    }
    return 0;
}