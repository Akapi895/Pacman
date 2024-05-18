#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 105;
const int oo = 1e18 + 7;

int N, M, K;
int dist[MAXN][MAXN], trace[MAXN][MAXN];

void Floyd() {
    for (int k = 1; k <= N; ++k) {
        for (int u = 1; u <= N; ++u) {
            for (int v = 1; v <= N; ++v) {
                if (dist[u][v] > dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                    trace[u][v] = trace[u][k];
                }
            }
        }
    }
}

vector <int> TRACE(int u, int v) {
    vector <int> ANS;
    ANS.push_back(u);
    while (u != v) {
        u = trace[u][v];
        ANS.push_back(u);
    }
    return ANS;
}

main() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            dist[i][j] = +oo;
        dist[i][i] = 0;
    }

    // Gọi dist[i][j] là đường đi ngắn nhất từ i đến j

    for (int i = 1; i <= M; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        dist[u][v] = min(dist[u][v], c);
        dist[v][u] = min(dist[v][u], c);
        trace[u][v] = v;
        trace[v][u] = u;
    }

    Floyd();

    for (int i = 1; i <= K; ++i) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 0) cout << dist[u][v] << '\n';
        else {
            vector <int> path = TRACE(u, v);
            cout << path.size() << ' ';
            for (auto &v: path) cout << v << ' ';
            cout << '\n';
        }
    }
    return 0;
}
