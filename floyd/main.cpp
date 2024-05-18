#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct Node {
    int x;
    int y;
};

bool isValid(int rows, int cols, int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

vector<Node> findShortestPathBFS(vector<vector<int>>& matrix,
                                 int start_node_x, int start_node_y) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Create a dictionary to store visited nodes and their parents
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Node>> parents(rows, vector<Node>(cols, {-1, -1}));

    // Initialize the queue for BFS
    queue<Node> q;
    q.push({start_node_x, start_node_y});
    visited[start_node_x][start_node_y] = true;

    // BFS loop to explore neighbors
    while (!q.empty()) {
        Node current_node = q.front();
        q.pop();

        int current_x = current_node.x;
        int current_y = current_node.y;

        // Check if the current node is the goal (another node with value 00)
        if (matrix[current_x][current_y] == 00 && (current_x, current_y) != (start_node_x, start_node_y)) {
            // Reconstruct the path from the goal node to the starting node
            vector<Node> path;
            Node node = current_node;
            while (node != (start_node_x, start_node_y)) {
                path.push_back(node);
                node = parents[node.x][node.y];
            }
            path.push_back(start_node_x, start_node_y); // Add the starting node
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors in all directions (up, down, left, right)
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int new_x = current_x + dx;
                int new_y = current_y + dy;

                if (isValid(rows, cols, new_x, new_y) && !visited[new_x][new_y] && matrix[new_x][new_y] == 00) {
                    visited[new_x][new_y] = true;
                    parents[new_x][new_y] = {current_x, current_y};
                    q.push({new_x, new_y});
                }
            }
        }
    }

    // No path found between nodes with value 00
    return {};
}

int main() {
    freopen("floyd.inp", "r", stdin);
    freopen("floyd.out", "w", stdout);


    return 0;
}
