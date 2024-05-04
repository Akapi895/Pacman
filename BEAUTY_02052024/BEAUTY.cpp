#include <bits/stdc++.h>

using namespace std;

#define int long long

const int oo = 1e18;
const int MAXN = 1e5 * 3 + 115;
int N, A[MAXN];
int dp[MAXN][10][2];
/*
i: vi tri dang xet
check: chan le
num: so luong da lay
test: check xem da lay baoh ch
*/
int solve(int i, int num, bool check, bool ) {

    if (dp[i][num][check] != -1) return dp[i][num][check];

    int cur = -oo;
    if (num == 0) cur = max(cur, solve(i + 1, num, check));
    else {
        if (num + 1 > 4) cur = max(cur, solve(i + 1, 4, (check + 1) % 2) + A[i]);
    }
    if (check == 1) cur = max(cur, solve(i + 1, (num + 1 >= 4)? 4 : num + 1, 0) + A[i]);
    else {
        cur = max(cur, solve(i + 1, (num + 1 >= 4)? 4 : num + 1, 0) + A[i]);
    }
}
main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> A[i];

    memset(dp, -1, sizeof(dp));


    return 0;
}
