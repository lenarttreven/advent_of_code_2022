#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"

using namespace std;

int main() {
    string filename = "../day_5/main.txt";
    string out = top_crates_9001(&filename, 9, 8);
    cout << out << endl;
    return 0;
}
