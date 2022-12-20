#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"

using namespace std;

int main() {
    string filename = "../day_4/main.txt";
    int out = number_of_overlapping_elfs(&filename);
    cout << out << endl;
    return 0;
}
