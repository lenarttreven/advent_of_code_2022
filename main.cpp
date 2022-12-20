#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"

using namespace std;

int main() {
    string filename = "../day_2/main.txt";
    int out = smart_strategy(&filename);
    cout << out << endl;
    return 0;
}
