/*
1. zaimplementuj reprezentacje grafu:  lista krawedzi, macierz sasiedztwa,lista nastepnikow
2. Zaimplementuj generowanie w pelni losowego, skierowanego grafu
3. Zaimplementuj algorytm DFS dla macierzy sasiedztwa i dla list nastêpnikow
4. Wykonaj eksperymenty obliczeniowe dla liczby wierzcholkow 100, 200, …, 1000 i dla gestosci 1/8, 2/8, …, 7/8
5. Przedstaw wyniki w sprawozdaniu (po jednym wykresie na reprezentacje grafu) i porownaj zmierzone czasy dzialania

I. Przygotuj implementacje i eksperymenty obliczeniowe jak poprzednio, ale rowniez dla algorytmu BFS

*/

/* zad 1 hackerrank

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Graph {
private:
    int n;

public:
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> successorList;

    Graph(int vertices) {
        n = vertices;

        adjacencyMatrix.resize(n, vector<int>(n, 0));
        successorList.resize(n);
    }

    void addEdge(int u, int v) {

        adjacencyMatrix[u][v] = 1;
        successorList[u].push_back(v);
    }

    void printSuccessorList() {

        for (int i = 0; i < n; i++) {

            sort(successorList[i].begin(),
                 successorList[i].end());

            cout << i << ":";

            for (int v : successorList[i]) {
                cout << " " << v;
            }

            cout << "\n";
        }
    }

    void printAdjacencyMatrix() {

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                cout << adjacencyMatrix[i][j];

                if (j < n - 1)
                    cout << " ";
            }

            cout << "\n";
        }
    }
};

int main() {

    int n, m;

    cin >> n >> m;

    Graph G(n);

    for (int i = 0; i < m; i++) {

        int a, b;

        cin >> a >> b;

        G.addEdge(a, b);
    }

    G.printSuccessorList();

    cout << "\n";

    G.printAdjacencyMatrix();

    return 0;
}

*/

/* zad 2 hackerrank


#include <vector>
#include <iostream>

using namespace std;

class Graph {
private:
    int n;

public:
    vector<vector<int>> adj;
    bool hasCycle = false;

    Graph(int vertices) {
        n = vertices;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(int u, int parent, vector<bool>& visited) {

        visited[u] = true;

        for (int v : adj[u]) {

            if (!visited[v]) {
                DFS(v, u, visited);
            }
            else if (v != parent) {
                hasCycle = true;
            }
        }
    }

    bool isTree(int m) {

        if (m != n - 1)
            return false;

        vector<bool> visited(n, false);

        DFS(0, -1, visited);

        if (hasCycle)
            return false;

        for (int i = 0; i < n; i++) {

            if (!visited[i])
                return false;
        }

        return true;
    }
};

int main() {

    int n, m;

    cin >> n >> m;

    Graph G(n);

    for (int i = 0; i < m; i++) {

        int a, b;

        cin >> a >> b;

        a--;
        b--;

        G.addEdge(a, b);
    }

    if (G.isTree(m))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}

*/

/* zad 3 hackerrank

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class Graph {
private:
    int n;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        n = vertices;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findShortestPath() {
        // dist przechowuje liczbê krawêdzi od startu (wêze³ 0)
        // Inicjalizacja -1 oznacza wêze³ nieodwiedzony
        vector<int> dist(n, -1);
        queue<int> q;

        // Startujemy od pierwszego komputera (indeks 0)
        dist[0] = 0;
        q.push(0);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Jeœli dotarliœmy do celu, mo¿emy przestaæ szukaæ
            if (u == n - 1) break;

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        // Sprawdzenie czy cel (indeks n-1) zosta³ odwiedzony
        if (dist[n - 1] == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            // Wynik to liczba komputerów w œcie¿ce:
            // Liczba krawêdzi (dist) + 1
            cout << dist[n - 1] + 1 << endl;
        }
    }
};

int main() {
    // Szybkie I/O - niezbêdne przy n=10^5 i m=2*10^5
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    Graph G(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        // Mapowanie numeracji 1..n na indeksy 0..n-1
        if (a >= 1 && a <= n && b >= 1 && b <= n) {
            G.addEdge(a - 1, b - 1);
        }
    }

    G.findShortestPath();

    return 0;
}

*/

#include <cmath>
#include <cstdio>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

enum Color { //do oznaczania stanu odwiedzenia wierzcho³ków podczas DFS/BFS
    WHITE,
    GRAY,
    BLACK
};

class Graph {
private:
    int n; // liczba wierzcho³ków

public:
    vector<pair<int, int>> edgeList;

    vector<vector<int>> adjacencyMatrix;

    vector<vector<int>> successorList;

    Graph(int vertices) {
        n = vertices;

        adjacencyMatrix.resize(n, vector<int>(n, 0));
        successorList.resize(n);
    }

    // Dodawanie ³uku u -> v
    void addEdge(int u, int v) {
        if (adjacencyMatrix[u][v] == 0) {

            adjacencyMatrix[u][v] = 1;

            edgeList.push_back({ u, v }); //dodaje u,v na koniec listy krawêdzi

            successorList[u].push_back(v); // dodaje v na koniec listy nastêpników wierzcho³ka u
        }
    }
    void printEdgeList() {

        sort(edgeList.begin(), edgeList.end());

      //  cout << "LISTA KRAWEDZI:\n";

        for (auto edge : edgeList) {
            cout << edge.first << " " << edge.second << "\n";
        }

        cout << "\n";
    }

    void printAdjacencyMatrix() {
        //  cout << "MACIERZ SASIEDZTWA:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "\n";
    }

    void printSuccessorList() {

        //cout << "LISTA NASTEPNIKOW:\n";

        for (int i = 0; i < n; i++) {

            // sortowanie listy nastêpników wierzcho³ka i
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

            // istnieje krawêdŸ u -> v
            if (adjacencyMatrix[u][v] == 1) {

                // jeœli trafimy na GRAY -> cykl
                if (colors[v] == GRAY) {
                    hasCycle = true;
                }

                // odwiedzamy nieodwiedzonego s¹siada
                if (colors[v] == WHITE) {
                    DFSVisit(v, colors);
                }
            }
        }

        colors[u] = BLACK;
    }

    // DFSVisit using successorList representation
    void DFSVisitSuccessor(int u, vector<Color>& colors) {

        colors[u] = GRAY;

        for (int v : successorList[u]) {

            // jeœli trafimy na GRAY -> cykl
            if (colors[v] == GRAY) {
                hasCycle = true;
            }

            // odwiedzamy nieodwiedzonego s¹siada
            if (colors[v] == WHITE) {
                DFSVisitSuccessor(v, colors);
            }
        }

        colors[u] = BLACK;
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
                return -1; // wierzcho³ek z wiêcej ni¿ jednym rodzicem
            }
        }
        return (rootCount == 1) ? root : -1; // musi byæ dok³adnie jeden korzeñ
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
            return false; // drzewo musi byæ spójne

        if (hasCycle)
            return false; // drzewo nie mo¿e zawieraæ cyklu

        // sprawdzenie struktury drzewa (stopnie wejœciowe) korzystaj¹c z listy nastêpników
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
};


void generateRDG(Graph& G, int n, double density) { //RDG - Random Directed Graph

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dist(0, n - 1);

    int maxEdges = n * (n - 1);  // maksymalna liczba ³uków w grafie skierowanym
   
    int m = density * maxEdges;  // liczba ³uków do wygenerowania

    int edgesAdded = 0;

    while (edgesAdded < m) {

        int u = dist(gen);
        int v = dist(gen);

        // brak pêtli w³asnych
        if (u != v) {

            // brak wielokrotnych krawêdzi
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

    int n, m;

    if (!(cin >> n >> m)) return 0;

    Graph G(n);

    for (int i = 0; i < m; i++) {

        int a, b;

        cin >> a >> b;

        a--; b--;

        G.addEdge(a, b);
    }

    if (G.isTreeList())
        cout << "YES\n";
    else
        cout << "NO\n";


    return 0;
}