/*
 ID: RaresC
 LANG: C++
 TASK: stamps
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

#define MAX 50
#define MAX_M 2000000
int total, amnts;
int stamps[MAX];

int stamps_used[MAX_M];

int main() {
    
    // DP Problem
 
    ifstream fin ("stamps.in");
    ofstream fout ("stamps.out");
    
    fin >> total >> amnts;
    for (int i = 0; i < amnts; i++)
        fin >> stamps[i];
    sort(stamps, stamps+amnts);
    
    for (int i = 1; i < MAX_M; i++) {
        
        for (int k = 0; k <= amnts; k++) {
            if (i-stamps[k] < 0) break;
            
            if (stamps_used[i] == 0 || stamps_used[i-stamps[k]] + 1 < stamps_used[i])
                stamps_used[i] = stamps_used[i-stamps[k]] + 1;
        }
    }
    
    int i = 0;
    for (i = 1; i < MAX_M; i++)
        if (stamps_used[i] > total)
            break;
    
    fout << i-1 << "\n";
    
    return 0;
}