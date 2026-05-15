#include <cmath>
#include <cstdio>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

enum Color {
    WHITE,
    GRAY,
    BLACK
};

class Graph {
private:
    int n;

public:
    vector<pair<int, int>> edgeList;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> successorList;

    Graph(int vertices) {
        n = vertices;
        adjacencyMatrix.resize(n, vector<int>(n, 0));
        successorList.resize(n);
    }

    void addEdge(int u, int v) {
        if (adjacencyMatrix[u][v] == 0) {
            adjacencyMatrix[u][v] = 1;
            edgeList.push_back({ u, v });
            successorList[u].push_back(v);
        }
    }

    void printEdgeList() {
        sort(edgeList.begin(), edgeList.end());

        for (auto edge : edgeList) {
            cout << edge.first << " " << edge.second << "\n";
        }

        cout << "\n";
    }

    void printAdjacencyMatrix() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "\n";
    }

    void printSuccessorList() {
        for (int i = 0; i < n; i++) {
            sort(successorList[i].begin(), successorList[i].end());

            cout << i << ": ";

            for (int v : successorList[i]) {
                cout << v << " ";
            }

            cout << "\n";
        }

        cout << "\n";
    }

    bool hasCycle = false;

    void DFSVisit(int u, vector<Color>& colors) {
        colors[u] = GRAY;

        for (int v = 0; v < n; v++) {
            if (adjacencyMatrix[u][v] == 1) {
                if (colors[v] == GRAY) {
                    hasCycle = true;
                }

                if (colors[v] == WHITE) {
                    DFSVisit(v, colors);
                }
            }
        }

        colors[u] = BLACK;
    }

    void DFSVisitSuccessor(int u, vector<Color>& colors) {
        colors[u] = GRAY;

        for (int v : successorList[u]) {
            if (colors[v] == GRAY) {
                hasCycle = true;
            }

            if (colors[v] == WHITE) {
                DFSVisitSuccessor(v, colors);
            }
        }

        colors[u] = BLACK;
    }

    void BFSVisitMatrix(int start, vector<Color>& colors) {
        queue<int> q;
        q.push(start);
        colors[start] = GRAY;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < n; v++) {
                if (adjacencyMatrix[u][v] == 1) {
                    if (colors[v] == WHITE) {
                        colors[v] = GRAY;
                        q.push(v);
                    }
                    else {
                        hasCycle = true;
                    }
                }
            }

            colors[u] = BLACK;
        }
    }

    void BFSVisitSuccessor(int start, vector<Color>& colors) {
        queue<int> q;
        q.push(start);
        colors[start] = GRAY;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : successorList[u]) {
                if (colors[v] == WHITE) {
                    colors[v] = GRAY;
                    q.push(v);
                }
                else {
                    hasCycle = true;
                }
            }

            colors[u] = BLACK;
        }
    }

    int findRoot() {
        vector<int> indegree(n, 0);

        for (int u = 0; u < n; u++) {
            for (int v : successorList[u]) {
                indegree[v]++;
            }
        }

        int rootCount = 0;
        int root = -1;

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                rootCount++;
                root = i;
            }
            else if (indegree[i] > 1) {
                return -1;
            }
        }

        return (rootCount == 1) ? root : -1;
    }

    bool isTreeList() {
        vector<Color> colors(n, WHITE);
        hasCycle = false;

        int connectedComponents = 0;

        for (int u = 0; u < n; u++) {
            if (colors[u] == WHITE) {
                connectedComponents++;
                DFSVisitSuccessor(u, colors);
            }
        }

        if (connectedComponents != 1)
            return false;

        if (hasCycle)
            return false;

        vector<int> indegree(n, 0);

        for (int u = 0; u < n; u++) {
            for (int v : successorList[u]) {
                indegree[v]++;
            }
        }

        int roots = 0;

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                roots++;
            }
            else if (indegree[i] != 1) {
                return false;
            }
        }

        return roots == 1;
    }

    bool isTreeMatrix() {
        int root = findRoot();

        if (root == -1)
            return false;

        vector<Color> colors(n, WHITE);
        hasCycle = false;

        DFSVisit(root, colors);

        for (int i = 0; i < n; i++) {
            if (colors[i] == WHITE)
                return false;
        }

        if (hasCycle)
            return false;

        return true;
    }

    bool isTreeListBFS() {
        int root = findRoot();

        if (root == -1)
            return false;

        vector<Color> colors(n, WHITE);
        hasCycle = false;

        BFSVisitSuccessor(root, colors);

        for (int i = 0; i < n; i++) {
            if (colors[i] == WHITE)
                return false;
        }

        if (hasCycle)
            return false;

        return true;
    }

    bool isTreeMatrixBFS() {
        int root = findRoot();

        if (root == -1)
            return false;

        vector<Color> colors(n, WHITE);
        hasCycle = false;

        BFSVisitMatrix(root, colors);

        for (int i = 0; i < n; i++) {
            if (colors[i] == WHITE)
                return false;
        }

        if (hasCycle)
            return false;

        return true;
    }
};

void generateRDG(Graph& G, int n, double density) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dist(0, n - 1);

    int maxEdges = n * (n - 1);
    int m = density * maxEdges;

    int edgesAdded = 0;

    while (edgesAdded < m) {
        int u = dist(gen);
        int v = dist(gen);

        if (u != v) {
            if (G.adjacencyMatrix[u][v] == 0) {
                G.addEdge(u, v);
                edgesAdded++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const vector<int> sizes = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
    const double density = 7.0 / 8.0;
    const int REPS = 100;

    for (int n : sizes) {
        Graph G(n);
        generateRDG(G, n, density);

        clock_t start = clock();
        for (int i = 0; i < REPS; ++i) {
            G.isTreeMatrixBFS();
        }
        double duration_matrix = double(clock() - start) / CLOCKS_PER_SEC / REPS;

        start = clock();
        for (int i = 0; i < REPS; ++i) {
            G.isTreeListBFS();
        }
        double duration_list = double(clock() - start) / CLOCKS_PER_SEC / REPS;

        cout << "n=" << n
            << " | matrix BFS: " << duration_matrix << " s"
            << " | list BFS: " << duration_list << " s\n";
    }

    return 0;
}