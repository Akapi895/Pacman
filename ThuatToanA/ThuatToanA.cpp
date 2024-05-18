#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Cấu trúc để lưu trữ thông tin về một ô vuông trong mê cung
struct Node {
    int x, y; // Tọa độ (hàng, cột)
    int g; // Khoảng cách từ nút bắt đầu
    int h; // Ước tính khoảng cách đến nút đích
    Node* parent; // Nút cha trong đường đi
//    Node() : x(0), y(0), g(0), parent(nullptr) {;}
};

// Hàm kiểm tra xem một ô vuông có hợp lệ hay không
bool isValid(vector<vector<int>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && (maze[x][y] == 0 || maze[x][y] == 8);
}

// Hàm tính toán heuristic (ước tính khoảng cách đến nút đích)
int heuristic(Node* current, Node* goal) {
    return abs(current->x - goal->x) + abs(current->y - goal->y);
}

// Thuật toán A* để tìm đường đi ngắn nhất
vector<Node*> AStar(vector<vector<int>>& maze, Node* start, Node* goal) {
    // Danh sách mở (open list) để lưu trữ các nút đang được xem xét
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openList;

    // Danh sách đóng (closed list) để lưu trữ các nút đã được khám phá
    vector<vector<bool>> closedList(maze.size(), vector<bool>(maze[0].size(), false));

    // Khởi tạo nút bắt đầu
    start->g = 0;
    start->h = heuristic(start, goal);
    start->parent = nullptr;
    openList.push({start->g + start->h, start});

    while (!openList.empty()) {
        // Lấy nút có f(n) thấp nhất (f(n) = g(n) + h(n))
        Node* current = openList.top().second;
        openList.pop();

        // Kiểm tra xem đã đến nút đích hay chưa
        if (current == goal) {
            vector<Node*> path;
            Node* node = current;
            while (node != nullptr) {
                path.push_back(node);
                node = node->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Đánh dấu nút hiện tại là đã khám phá
        closedList[current->x][current->y] = true;

        // Xét tất cả các nút lân cận của nút hiện tại
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Bỏ qua nút hiện tại

                int newX = current->x + dx;
                int newY = current->y + dy;

                // Kiểm tra xem nút lân cận có hợp lệ hay không
                if (!isValid(maze, newX, newY) || closedList[newX][newY]) continue;

                // Tạo nút lân cận
                Node* neighbor = new Node{newX, newY, 0, 0, nullptr};

                // Tính toán g(m) (khoảng cách từ nút bắt đầu đến nút lân cận)
                neighbor->g = current->g + 1;

                // Tính toán h(m) (ước tính khoảng cách đến nút đích)
                neighbor->h = heuristic(neighbor, goal);

                // Cập nhật f(m) và cha của nút lân cận nếu cần thiết
                int fNew = neighbor->g + neighbor->h;
                if (!openList.empty() && openList.top().first <= fNew) continue;

                // Thêm nút lân cận vào danh sách mở
                openList.push({fNew, neighbor});
                neighbor->parent = current;
            }
        }
    }

    // Không tìm thấy đường đi
    return {};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("ThuatToanA.inp", "r", stdin);
    freopen("ThuatToanA.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> maze;
    for (int i = 0 ; i < m; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            int a; cin >> a;
            row.push_back(a);
        }
        maze.push_back(row);
    }
//    for (int i = 0; i < m; ++i) {
//        for (int j = 0; j < n; ++j) cout << maze[i][j] << ' ';
//        cout << '\n';
//    }
    Node* start = new Node{4, 2, 0, 0, nullptr};
    Node* goal  = new Node{9, 8, 0, 0, nullptr};


    vector<Node*> ans = AStar(maze, start, goal);

    for (int i = 0; i < ans.size(); ++i) {
        Node* current = ans[i];
        cout << current->x << ' ' << current->y << '\n';
    }
    return 0;
}
