#include <iostream>
#include "day_1/day_1.h"

using namespace std;

int main() {
    string filename = "../day_1/main.txt";
    int out = top_three_elfs(&filename);
    cout << out << endl;
    return 0;
}
