/*
 ID: RaresC
 LANG: C++
 TASK: range
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;
#define INF 10000000

#define MAX 250
int grid[MAX][MAX];
bool squares[MAX][MAX];

bool full_square (int l, int i, int k) {
    if ((!squares[i][k] || !squares[i+1][k] || !squares[i][k+1]) && l != 0) return false;
    if (grid[i+l][k+l] == 0) return false;
    return true;
}

int main() {
    
    ifstream fin ("range.in");
    ofstream fout ("range.out");
    
    int N; fin >> N;
    for (int i = 0; i < N; i++) {
        string s; fin >> s;
        for (int k = 0; k < N; k++)
            grid[i][k] = s[k]-'0';
    }
    
    int ans = 0;
    for (int s = 0; s < N; s++) {
        for (int i = 0; i < N-s; i++)
            for (int k = 0; k < N-s; k++)
                if (full_square(s, i, k)) {
                    ans++;
                    squares[i][k] = true;
                } else squares[i][k] = false;
        if (ans > 0 && s >= 1) fout << s+1 << " " << ans << "\n";
        ans = 0;
    }
    
    return 0;
}