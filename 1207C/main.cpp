#include <cstdio>
#include <cstdlib>
#include <climits>

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <set>
#include <bitset>
#include <algorithm>

using namespace std;

#define INVALID_COST -1
#define int64 int64_t
#define oo LLONG_MAX;

void dp(vector<vector<int64>> &costs, const string &pillars, int a, int b);
bool before_is_high(const string &pillars, int pos);
bool after_is_high(const string &pillars, int pos);
bool check_valid(vector<vector<int64>> &costs, int i, int vertical);


int main(int argc, char *argv[]) {
    if (argc > 1) {
        freopen("data_in.txt", "r", stdin);
        //freopen("data_out.txt", "w", STDOUT);
    }
    
    int T;
    cin >> T;
    while (T--) {
        int n, a, b;
        cin >> n >> a >> b;
        string pillars;
        vector<vector<int64>> costs(n+1, vector<int64>(2, 0));
        cin >> pillars;
        dp(costs, pillars, a, b);
        cout << costs.back()[0] << endl;
    }

    return 0;
}

void dp(vector<vector<int64>> &costs, const string &pillars, int a, int b) {
    costs[0][1] = INVALID_COST;
    costs[0][0] = b;
    for (int i = 1; i < costs.size(); i++) {
        if (before_is_high(pillars, i)) {
            costs[i][0] = INVALID_COST;
            costs[i][1] = costs[i-1][1] + a + b*2;
        } else {
            // before is low
            if (after_is_high(pillars, i)) {
                // current must be high
                costs[i][0] = INVALID_COST;
                costs[i][1] = oo;
                if (check_valid(costs, i-1, 0)) {
                    // calculate from low
                    costs[i][1] = min(costs[i][1], costs[i-1][0] + 2*a + 2*b);
                }
                if (check_valid(costs, i-1, 1)) {
                    // calculate from high
                    costs[i][1] = min(costs[i][1], costs[i-1][1] + a + 2*b);
                }
            } else {
                // current could be high or low
                costs[i][0] = costs[i][1] = oo;
                if (check_valid(costs, i-1, 0)) {
                    // calculate from low
                    costs[i][0] = min(costs[i][0], costs[i-1][0]+a+b);
                    costs[i][1] = min(costs[i][1], costs[i-1][0] + 2*a + 2*b);
                }
                if (check_valid(costs, i-1, 1)) {
                    // calculate from high
                    costs[i][0] = min(costs[i][0], costs[i-1][1]+ 2*a + b);
                    costs[i][1] = min(costs[i][1], costs[i-1][1] + a + 2*b);
                }
            }
        }
    }
}

bool before_is_high(const string &pillars, int pos) {
    return pillars[pos-1] == '1';
}

bool after_is_high(const string &pillars, int pos) {
    if (pos >= pillars.length())
        return false;
    return pillars[pos] == '1';
}

bool check_valid(vector<vector<int64>> &costs, int i, int vertical) {
    return costs[i][vertical] != INVALID_COST;
}