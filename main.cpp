#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"

using namespace std;

int main() {
    string filename = "../day_3/main.txt";
    int out = badges_for_grouping(&filename);
    cout << out << endl;
    return 0;
}
