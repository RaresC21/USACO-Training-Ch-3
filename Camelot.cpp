/*
 ID: RaresC
 LANG: C++
 TASK: camelot
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;
#define INF 10000000

int moves[16] = {-2,-1, -2,1, -1,2, -1,-2, 1,2, 1,-2, 2,1, 2,-1};

#define RMAX 30
#define CMAX 26
int R, C;
int grid[RMAX][CMAX];
int distances[RMAX][CMAX]; // the overall dist for everything.
int weights[RMAX][CMAX][RMAX][CMAX]; // dist from point 1 to point 2
bool met[RMAX][CMAX];
vector<pair<int, int> > knights;
vector<pair<int, int> > queue;
pair<int, int> king;

void knight_bfs (int y, int x, int kn) {
    
    for (int i = 0; i < queue.size(); i++)
    {
        int r = queue[i].first;
        int c = queue[i].second;
        
        // there are 8 ways a knight can move.
        for (int i = 0; i < 8; i++) {
            int r1 = r+moves[2*i+1];
            int c1 = c+moves[2*i];
            
            if (r1 < R && c1 < C && r1 >= 0 && c1 >= 0 && !met[r1][c1]) {
                if (weights[y][x][r1][c1] >= weights[y][x][r][c] + 1) {
                    weights[y][x][r1][c1] = weights[r1][c1][y][x] = weights[y][x][r][c] + 1;
                    met[r1][c1] = true;
                    queue.push_back(make_pair(r1, c1));
                }
            }
        }
    }
}

int king_move(int r, int c) {
    int kr = king.first;
    int kc = king.second;
    
    if (abs(kr-r) > abs(kc-c))
        return abs(kr-r);
    return abs(kc-c);
}

int main() {
    
    ifstream fin ("camelot.in");
    ofstream fout ("camelot.out");
    
    // INPUT
    fin >> R >> C;
    
    // initialize
    for (int i = 0; i < R; i++) for (int k = 0; k < C; k++)
        for (int j = 0; j < R; j++) for (int l = 0; l < C; l++) {
            if (i == j && k == l) continue;
            weights[i][k][j][l] = INF;
        }
    
    char c; int r; fin >> c >> r;
    grid[r-1][c-'A'] = -1; king.first = r-1; king.second = c-'A';
    int cur = 1;
    while (fin >> c >> r) {
        grid[r-1][c-'A'] = cur;
        knights.push_back(make_pair(r-1, c-'A'));
        cur++;
    }
    
    // BFS to find min distance from any point to each spot in the grid.
    for (int i = 0; i < R; i++)
        for (int k = 0; k < C; k++) {
            queue.clear();
            for (int a = 0; a < RMAX; a++) for (int j = 0; j < CMAX; j++) met[a][j] = false;
            queue.push_back(make_pair(i, k));
            knight_bfs(i, k, grid[i][k]-1);
        }
    
    // distance traveled to point (i,k) if we can't pick up the king.
    int dist = INF;
    for (int i = 0; i < R; i++)
        for (int k = 0; k < C; k++) {
            cur = 0;
            for (int j = 0; j < knights.size(); j++)
                cur += weights[knights[j].first][knights[j].second][i][k];
            distances[i][k] = cur + king_move(i, k);
            if (dist > distances[i][k])
                dist = distances[i][k];
            //dist = min (dist, distances[i][k]);
        }
    
    cur = 0;
    // we pick up the king at (p1r, p1c) and the congregation point is (p2r, p2c).
    // (p1r, p1c) only needs to directly be around the king since it would otherwise be faster to make a knight moves to reach the king.
    for (int p1r = king.first-2; p1r <= king.first+2 && p1r < R; p1r++) {
        if (p1r < 0) continue;
        for (int p1c = king.second-2; p1c <= king.second+2 && p1c < C; p1c++) {
            if (p1c < 0) continue;
            
            for (int p2r = 0; p2r < R; p2r++)
                for (int p2c = 0; p2c < C; p2c++) {
                    
                    //if (p1r == p2r && p1c == p2c) continue;
                    int k_dist = king_move(p1r, p1c);
                    for (int j = 0; j < knights.size(); j++) {
                        dist = min (dist, distances[p2r][p2c] - king_move(p2r, p2c) + k_dist +
                                    weights[knights[j].first][knights[j].second][p1r][p1c] -
                                    weights[knights[j].first][knights[j].second][p2r][p2c] +
                                    weights[p1r][p1c][p2r][p2c]);
                    }
                    
                }
        }
    }
    
    fout << dist << "\n";
    
    return 0;
}