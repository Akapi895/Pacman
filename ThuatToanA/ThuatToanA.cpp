#include <bits/stdc++.h>


using namespace std;

// Cấu trúc để lưu trữ thông tin về một ô vuông trong mê cung
struct Node {
    int x, y; // Tọa độ (hàng, cột)
    int g; // Khoảng cách từ nút bắt đầu
    int h; // Ước tính khoảng cách đến nút đích
    Node* parent; // Nút cha trong đường đi
};

// Hàm kiểm tra xem một ô vuông có hợp lệ hay không
bool isValid(vector<vector<int>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == 8;
}

// Hàm tính toán heuristic (ước tính khoảng cách đến nút đích)
int informedHeuristic(Node* current, Node* goal, vector<vector<int>>& maze) {
    // Calculate the Manhattan distance (basic heuristic)
    int manhattanDistance = abs(current->x - goal->x) + abs(current->y - goal->y);

    // Apply additional informed heuristic based on problem domain information
    // For example, in a maze with obstacles, consider the distance to the nearest obstacle:
    int nearestObstacleDistance = INT_MAX; // Initialize to a large value
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Skip current node
            int newX = current->x + dx;
            int newY = current->y + dy;
            if (isValid(maze, newX, newY) && maze[newX][newY] == 1) {
                nearestObstacleDistance = min(nearestObstacleDistance, abs(newX - goal->x) + abs(newY - goal->y));
            }
        }
    }

    // Combine the basic heuristic with the informed heuristic
    int informedHeuristicValue = manhattanDistance + nearestObstacleDistance;

    return informedHeuristicValue;
}

// Thuật toán A* để tìm đường đi ngắn nhất
vector<Node*> AStar(vector<vector<int>>& maze, Node* start, Node* goal) {
    // Danh sách mở (open list) để lưu trữ các nút đang được xem xét
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openList;

    // Danh sách đóng (closed list) để lưu trữ các nút đã được khám phá
    vector<vector<bool>> closedList(maze.size(), vector<bool>(maze[0].size(), false));

    // Khởi tạo nút bắt đầu
    start->g = 0;
    start->h = informedHeuristic(start, goal, maze);
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
                neighbor->h = informedHeuristic(neighbor, goal, maze);

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
    // Mở file đầu vào
    freopen("ThuatToanA.inp", "r", stdin);
    freopen("ThuatToanA.out", "w", stdout);

    // Đọc số hàng và số cột của mê cung
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

    // Đọc tọa độ nút bắt đầu
    int startX(1), startY(1);
    // Đọc tọa độ nút đích
    int goalX(2), goalY(3);

    // Tạo nút bắt đầu và nút đích
    Node start{startX, startY, 0, 0, nullptr};
    Node goal{goalX, goalY, 0, 0, nullptr};

    // Tìm đường đi ngắn nhất
    vector<Node*> path = AStar(maze, &start, &goal);

    // Kiểm tra xem có tìm thấy đường đi hay không
    if (path.empty()) {
        cout << "Không tìm thấy đường đi!" << endl;
    } else {
        // In ra đường đi
        cout << "Đường đi ngắn nhất:" << endl;
        for (Node* node : path) {
            cout << node->x << " " << node->y << endl;
        }
    }

    return 0;
}
