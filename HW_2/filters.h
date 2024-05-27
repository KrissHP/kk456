//
// Created by d0nttouchme on 19.05.2024.
//

#ifndef HW_2_FILTERS_H
#define HW_2_FILTERS_H

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>
using namespace std;
typedef vector<vector<float> > vvf;


void saf(vvf&data, int win, int i, int num);

void synchro_f(vvf&data, int period, int col);


#endif //HW_2_FILTERS_H
