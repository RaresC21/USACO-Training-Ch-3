/*
 ID: RaresC
 LANG: C++
 TASK: inflate
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <vector>
using namespace std;
typedef long long ll;
#define MAX 10001

int Time, N;
int length[MAX];
int amnt[MAX];
long points[MAX];

int main() {
    
    ifstream fin ("inflate.in");
    ofstream fout ("inflate.out");
    
    fin >> Time >> N;
    for (int i = 0; i < N; i++)
        fin >> amnt[i] >> length[i];
    
    for (int i = 0; i < MAX; i++) {
        long curP=0;
        for (int k = 0; k < N; k++) {
            if (i - length[k] < 0) continue;
            if (points[i-length[k]] + amnt[k] > curP)
                curP = points[i-length[k]] + amnt[k];
        }
        points[i] = curP;
    }
    
    fout << points[Time] << "\n";
    
    return 0;
}