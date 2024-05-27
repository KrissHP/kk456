#include <iostream>
#include <chrono>
#include <vector>
#include "filters.h"
using namespace std;

#define F_ERROR "File is not opening!\n"
typedef vector<vector<float> > vvf;

int main() {
    const char *fname = "C:/Users/TECNO/Desktop/HW_2/hw2_data.dat";
    const char *file = "C:/Users/TECNO/Desktop/HW_2/test.txt";
    const int columns[] = {1, 2, 3, 4};
    const int period = 350, win = 5;
    const char *filter = "synchro";
    fstream f(fname);
    ofstream out(file);
    vvf data;
    vector<float>element;
    string line;
    float el;
    if(!f.is_open()){
        cout << F_ERROR;
        return 0;
    }

    while(getline(f, line)){
        istringstream ss(line);
        element.clear();
        while(ss >> el){
            element.push_back(el);
        }data.push_back(element);
    }

    auto start_time = chrono::steady_clock::now();
    for(int i = 0; i < data.size(); i++){
        for(int j : columns) {

            if (filter == "move_aver")
                saf(data, win, i, j);
            else if(filter == "synchro"){
                for(int col : columns)
                    synchro_f(data, period, col);
            }
        }
    }
    auto end_time = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[i].size(); j++)
            out << data[i][j] << '\t';
        out << '\n';
    }


    f.close();
    return 0;
}
