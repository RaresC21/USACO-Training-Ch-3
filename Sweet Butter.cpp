/*
 ID: RaresC
 LANG: C++
 TASK: butter
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

#define MAX_N 1000
#define V 1000
#define LARGE 10000000

int N, P, C, total=LARGE, ans;
int start[MAX_N];
int weight[MAX_N][MAX_N];

int length[MAX_N];
int distance_[MAX_N];
map<int, int> cur_r;
map<int, int> repeats;

map<int, int> heap_d;
vector<int> paths[MAX_N];

void insert_distance (int i, int d) {
    length[i] = d;
    int n_d = d * V + repeats[d];
    heap_d[n_d] = i;
    cur_r[i] = repeats[d];
    repeats[d]++;
}

void delete_distance (int i) {
    int d = length[i] * V + cur_r[i];
    heap_d.erase(d);
}

int main() {
    
    ifstream fin ("input.txt");
    ofstream fout ("butter.out");
    
    fin >> N >> P >> C;
    for (int i = 0; i < N; i++)
        fin >> start[i];
    for (int i = 0; i < C; i++) {
        int a, b, d;
        fin >> a >> b >> d;
        paths[a].push_back(b);
        paths[b].push_back(a);
        weight[a][b] = weight[b][a] = d;
    }
    
    // test every possible pasture.
    for (int source = 1; source < P; source++) {
        heap_d.clear();
        repeats.clear();
        cur_r.clear();
        memset(distance_, -1, sizeof(distance_));
        memset(length, 0, sizeof(length));
        
        distance_[source] = 0;
        
        int nodes_visited = 1;
        while (nodes_visited < P) {
            // find unvisited vertex with minimum distance to source. call it i.
            int i=source;
            if (heap_d.size()) {
                i = heap_d.begin()->second;
                nodes_visited++;
                delete_distance(i);
            }
            
            // update distance to neighboors of i.
            for (int j = 0; j < paths[i].size(); j++) {
                int n = paths[i][j];
                
                if (distance_[n] == -1 || distance_[i] + weight[i][n] < distance_[n]) {
                    if (distance_[n] != -1)
                        delete_distance(n);
                    distance_[n] = distance_[i] + weight[i][n];
                    insert_distance(n, distance_[n]);
                }
            }
        }
        
        // find distance cows must travel to get to sugar.
        int cur=0;
        for (int j = 0; j < N; j++)
            cur += distance_[start[j]];
        if (cur < total)
            total = cur;
    }
    
    cout << total << "\n";
    
    return 0;
}