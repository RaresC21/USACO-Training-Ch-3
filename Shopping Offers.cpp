/*
 ID: RaresC
 LANG: C++
 TASK: shopping
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

int S;

struct Offer {
    int code[5];
    int amnt[5];
    
    int p;
}offer[100];

Offer purchase;
int norm_price[5];
int price[6][6][6][6][6];

map<int, int> codes;

int main() {
    
    ifstream fin ("shopping.in");
    ofstream fout ("shopping.out");
    
    // input special offers
    int cur = 1;
    fin >> S;
    for (int i = 0; i < S; i++) {
        int n; fin >> n;
        for (int k = 0; k < n; k++) {
            int c; fin >> c; // this is the code of the product
            if (!codes[c])
                codes[c] = cur, cur++;
            c = codes[c]-1;
            fin >> offer[i].amnt[c];
        }
        fin >> offer[i].p;
    }
    
    // input the purchase we want to make.
    int b; fin >> b;
    for (int k = 0; k < b; k++) {
        int c; fin >> c;
        if (!codes[c])
            codes[c] = cur, cur++;
        c = codes[c]-1;
        fin >> purchase.amnt[c];
        fin >> norm_price[c];
    }
    
    // DP
    for (int t = 0; t < 2; t++)
        for (int a = 0; a < 6; a++)
            for (int b = 0; b < 6; b++)
                for (int c = 0; c < 6; c++)
                    for (int d = 0; d < 6; d++)
                        for (int e = 0; e < 6; e++) {
                            
                            if (t == 0) {
                                // calculate prices without any special offers.
                                price[a][b][c][d][e] = a*norm_price[0]+b*norm_price[1]+c*norm_price[2]+
                                d*norm_price[3]+e*norm_price[4];
                                continue;
                            }
                            // try all of the special offers
                            for (int i = 0; i < S; i++) {
                                int a1 = a-offer[i].amnt[0];
                                int b1 = b-offer[i].amnt[1];
                                int c1 = c-offer[i].amnt[2];
                                int d1 = d-offer[i].amnt[3];
                                int e1 = e-offer[i].amnt[4];
                                if (a1 < 0 || b1 < 0 || c1 < 0 || d1 < 0 || e1 < 0) continue;
                                
                                price[a][b][c][d][e] = min (price[a][b][c][d][e], price[a1][b1][c1][d1][e1] +
                                                            offer[i].p);
                            }
                            
                        }
    
    fout << price[purchase.amnt[0]][purchase.amnt[1]][purchase.amnt[2]][purchase.amnt[3]][purchase.amnt[4]] << "\n";
    
    return 0;
}