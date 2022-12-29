//
// Created by Lenart Treven on 28.12.22.
//

#include "day_11.h"
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

class Monkey {
public:
    vector<int> starting_items;
    int id;

    string operation_string;

    int divisible_by;
    int num_inspected_items = 0;
    int if_true;
    int if_false;
    vector<int> modulus;
    vector<vector<int>> starting_items_remainders;

    static vector<int> parse_starting_times(const string &line);


    Monkey(int monkey_id, string raw_starting_items, string operation, int dvs_by, int if_tr, int if_fls) {
        starting_items = parse_starting_times(std::move(raw_starting_items));
        operation_string = std::move(operation);
        id = monkey_id;
        divisible_by = dvs_by;
        if_true = if_tr;
        if_false = if_fls;
    }

    int apply_operation(int old) const;

};

int Monkey::apply_operation(int old) const {
    if (Monkey::operation_string == "new = old * old") {
        return old * old;
    } else if (Monkey::operation_string.rfind("new = old *", 0) == 0) {
        const string &string_to_parse = Monkey::operation_string;
        regex rgx(R"((\d+))");
        smatch match;
        string::const_iterator searchStart(string_to_parse.cbegin());
        regex_search(searchStart, string_to_parse.cend(), match, rgx);
        return old * stoi(match[1]);
    } else if (Monkey::operation_string.rfind("new = old +", 0) == 0) {
        const string &string_to_parse = Monkey::operation_string;
        regex rgx(R"((\d+))");
        smatch match;
        string::const_iterator searchStart(string_to_parse.cbegin());
        regex_search(searchStart, string_to_parse.cend(), match, rgx);
        return old + stoi(match[1]);
    } else {
        return old;
    }
}

vector<int> Monkey::parse_starting_times(const string &line) {
    vector<int> starting_times;
    const string &string_to_parse = line;
    regex rgx(R"((\d+))");
    smatch match;
    string::const_iterator searchStart(string_to_parse.cbegin());

    while (regex_search(searchStart, string_to_parse.cend(), match, rgx)) {
        starting_times.push_back(stoi(match[1]));
        searchStart = match.suffix().first;
    }
    return starting_times;
}


void perform_turn(int monkey_id, map<int, Monkey> *monkeys) {
    Monkey *monkey = &(*monkeys).at(monkey_id);
    vector<vector<int>> new_reminders;
    for (vector<int> reminders: (*monkey).starting_items_remainders) {
        (*monkey).num_inspected_items += 1;
        vector<int> new_reminder;
        for (int i = 0; i < reminders.size(); i++) {
            int new_item = (*monkey).apply_operation(reminders[i]);
            new_item = new_item % (*monkey).modulus[i];
            new_reminder.push_back(new_item);
        }
        if (new_reminder[monkey_id] % (*monkey).divisible_by == 0) {
            (*monkeys).at((*monkey).if_true).starting_items_remainders.push_back(new_reminder);
        } else {
            (*monkeys).at((*monkey).if_false).starting_items_remainders.push_back(new_reminder);
        }
    }
    (*monkey).starting_items_remainders = new_reminders;
}

void perform_turn_old(int monkey_id, map<int, Monkey> *monkeys) {
    Monkey *monkey = &(*monkeys).at(monkey_id);
    vector<int> new_items;
    for (int item: (*monkey).starting_items) {
        (*monkey).num_inspected_items += 1;
        int new_item = (*monkey).apply_operation(item);
//        new_item = new_item / 3;
        if (new_item % (*monkey).divisible_by == 0) {
            (*monkeys).at((*monkey).if_true).starting_items.push_back(new_item);
        } else {
            (*monkeys).at((*monkey).if_false).starting_items.push_back(new_item);
        }
    }
    (*monkey).starting_items = new_items;
}

void perform_round(map<int, Monkey> *monkeys) {
    for (const auto &myPair: *monkeys) {
        perform_turn(myPair.first, monkeys);
    }
}

long monkey_business_level(string *filename) {
    int num_rounds = 10000;
    string whole_text;

    ifstream MyReadFile(*filename);
    string line_text;
    map<int, Monkey> monkeys;

    while (getline(MyReadFile, line_text)) {
        whole_text += line_text + "\n";
    }

    const string string_to_parse = whole_text;

    regex rgx(R"(Monkey (\d+):
  Starting items: ([\d+, ]*)
  Operation: ([\w =*+]+)
  Test: divisible by (\d+)
    If true: throw to monkey (\d+)
    If false: throw to monkey (\d+))");
    smatch match;

    string::const_iterator searchStart(string_to_parse.cbegin());

    while (regex_search(searchStart, string_to_parse.cend(), match, rgx)) {
        Monkey my_monkey = Monkey(stoi(match[1]), match[2], match[3], stoi(match[4]), stoi(match[5]),
                                  stoi(match[6]));
        monkeys.insert(pair<int, Monkey>(my_monkey.id, my_monkey));
        searchStart = match.suffix().first;
    }
    for (auto & [key, val] : monkeys){
        for (int item:val.starting_items){
            vector<int> remainders(monkeys.size(), item);
            val.starting_items_remainders.push_back(remainders);
        }

        for (auto & [key_inner, val_inner] : monkeys){
            val.modulus.push_back(val_inner.divisible_by);
        }
    }

    for (int i = 0; i < num_rounds; i++) {
        perform_round(&monkeys);
    }
    vector<int> visitation_times;
    for (auto const& [key, val] : monkeys){
        visitation_times.push_back(val.num_inspected_items);
    }
    sort(visitation_times.begin(), visitation_times.end(), greater<>());
    return visitation_times[0] * visitation_times[1];
}
