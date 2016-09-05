/*
 ID: RaresC
 LANG: C++
 TASK: agrinet
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
#define MAX 100
#define INF 10000000

int cost[MAX][MAX];
int dist[MAX];
bool intree[MAX];
int N;

int main() {
    
    ifstream fin ("agrinet.in");
    ofstream fout ("agrinet.out");
    
    fin >> N;
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++) {
            fin >> cost[i][k];
        }
    
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        intree[i] = false;
    }
    
    int size = 1;
    int tcost = 0;
    intree[0] = true;
    dist[0] = INF;
    
    // for all nodes j of 1, update the distances to the tree.
    for (int j = 0; j < N; j++)
        dist[j] = cost[0][j];
    
    while (size < N) {
        
        
        // node i is closest to the tree.
        int i=0;
        for (int d = 1; d < N; d++)
            if (!intree[d] && (dist[d] < dist[i] || i == 0))
                i = d;
        
        size++;
        tcost += dist[i];
        intree[i] = true;
        
        // update all dist once node i is added
        for (int k = 0; k < N; k++)
            if (dist[k] > cost[i][k] && !intree[k])
                dist[k] = cost[i][k];
    }
    
    fout << tcost << "\n";
    
    return 0;
}