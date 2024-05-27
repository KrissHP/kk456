#include "filters.h"


void saf(vvf&data, int win, int i, int num){
    float av = 0;
    for(int j = 0; j < min(win, int(data.size() - i)); j++){
        av+=data[i + j][num];
    }av/=min(win, int(data.size() - i));
    data[i][num] = av;
}

void synchro_f(vvf&data, int period, int col){
    int start_pos, end_pos, amount;
    float value;
    for (int i = 0; i < period; i++) {
        value = 0;
        amount = 0;
        start_pos = i;
        end_pos = ((i > data.size() % period - 1) ? ((data.size() / period - 1) * period + i) :
                   ((data.size() / period) * period + i));
        for (int j = start_pos; j <= end_pos; j += period) {
            value += data[j][col];
            amount++;
        }
        value /= amount;
        for (int j = start_pos; j <= end_pos; j += period)
            data[j][col] = value;
    }
}