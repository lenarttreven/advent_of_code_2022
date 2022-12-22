#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"
#include "day_6/day_6.h"
#include "day_7/day_7.h"
#include "day_8/day_8.h"

using namespace std;

int main() {
    string filename = "../day_8/main.txt";
    int out = highest_scenic_score(&filename);
    cout << out << endl;
    return 0;
}
