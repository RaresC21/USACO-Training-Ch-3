/*
 ID: RaresC
 LANG: C++
 TASK: game1
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;
#define INF 10000000

#define MAX 100
int cards[MAX];
int P1[MAX][MAX];
int P2[MAX][MAX];
int p_sums[MAX]; // prefix sum of cards

int main() {
    
    ifstream fin ("game1.in");
    ofstream fout ("game1.out");
    
    int N,total=0; fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> cards[i];
        total += cards[i];
        if (i > 0) p_sums[i] = p_sums[i-1] + cards[i];
        else p_sums[0] = cards[0];
    }
    for (int i = 0; i < N; i++)
        if (N % 2 == 1)
            P1[i][i] = cards[i]; //determine whose turn it is. They will take the last card no matter what.
        else
            P2[i][i] = cards[i];
    
    
    
    for (int s = 1; s < N; s++)
        for (int i = 0; i < N-1; i++) {
            int k = i + s;
            int moves_made = N - (k-i); // determing whose move it is.
            if (moves_made % 2 == 1) {
                P1[i][k] = max (P1[i+1][k] + cards[i], P1[i][k-1] + cards[k]);
                if (i > 0)
                    P2[i][k] = p_sums[k] - p_sums[i-1] - P1[i][k];
                else
                    P2[i][k] = p_sums[k] - P1[i][k];
            }
            else {
                P2[i][k] = max (P2[i+1][k] + cards[i], P2[i][k-1] + cards[k]);
                if (i > 0)
                    P1[i][k] = p_sums[k] - p_sums[i-1] - P2[i][k];
                else
                    P1[i][k] = p_sums[k] - P2[i][k];
            }
        }
    
    fout << P1[0][N-1] << " " << P2[0][N-1] << "\n";
    
    return 0;
}