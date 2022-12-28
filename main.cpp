#include <iostream>
#include "day_01/day_1.h"
#include "day_02/day_2.h"
#include "day_03/day_3.h"
#include "day_04/day_4.h"
#include "day_05/day_5.h"
#include "day_06/day_6.h"
#include "day_07/day_7.h"
#include "day_08/day_8.h"
#include "day_09/day_9.h"
#include "day_10/day_10.h"

using namespace std;

int main() {
    string filename = "../day_10/main.txt";
    vector<string> out = draw_code(&filename);
    for (string line: out){
        cout << line << endl;
    }
    return 0;
}
