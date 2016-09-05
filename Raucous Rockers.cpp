/*
 ID: RaresC
 LANG: C++
 TASK: rockers
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
#define INF 10000000

#define MAX 20
int length[MAX];
int DP[MAX][MAX*MAX];
int cd[MAX*MAX];

int main() {
    
    ifstream fin ("rockers.in");
    ofstream fout ("rockers.out");
    
    int N, T, M; fin >> N >> T >> M;
    for (int i = 0; i < N; i++) fin >> length[i];
    
    for (int i = 0; i < M; i++)
        for (int k = i*T+1; k < (i+1)*T+1; k++)
            cd[k] = i;
    
    for (int i = 0; i < N; i++) {
        for (int k = 1; k <= M*T; k++) {
            if (i == 0) {
                if (k >= length[0]) DP[i][k] = 1;
                continue;
            }
            DP[i][k] = DP[i][k-1];
            DP[i][k] = max (DP[i][k], DP[i-1][k]);
            if (k - length[i] >= 0 && cd[k] == cd[k-length[i]+1]) // make sure the song can fit into the cd.
                DP[i][k] = max (DP[i][k], DP[i-1][k-length[i]] + 1);
        }
    }
    
    fout << DP[N-1][M*T] << "\n";
    
    return 0;
}