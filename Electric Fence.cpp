/*
 ID: RaresC
 LANG: C++
 TASK: fence9
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
#define INF 10000000


int main() {
    
    ifstream fin ("input.txt");
    ofstream fout ("fence9.out");
    
    double x, y, p;
    fin >> x >> y >> p;
    
    int s1 = 0;
    for (int i = 1; i < x; i++)  {
        if (i == p && x == p) break;
        double num = i*1.0 * y/x;
        if (num == (int) num) num = (int) (num-1);
        else num = (int) num;
        s1 += num;
    }
    
    int s2 = 0;
    if (p > x)
        for (int i = x+1; i < p; i++) {
            double num = (-y / (p-x)) * (i*1.0 - x) + y;
            if (num == (int) num) num = (int) num-1;
            else num = (int) num;
            s2 += num;
        }
    else if (p < x)
        for (int i = x-1; i > p; i--) {
            double num = (-y / (p-x)) * (i*1.0 - x) + y;
            num = (int) num;
            s2 += num;
        }
    
    int ans = 0;
    if (p > x) {
        if (x!=0) ans = s1 + s2 + y-1;
        else ans = s2;
    }
    else if (p == x) ans = s1;
    else if (p < x) ans = s1 - s2;
    
    cout << ans << "\n";
    
    return 0;
}