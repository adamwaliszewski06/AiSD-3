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

    bool hasValidTreeStructure() {

        vector<int> indegree(n, 0);

        // liczenie stopni wejœciowych
        for (int u = 0; u < n; u++) {

            for (int v = 0; v < n; v++) {

                if (adjacencyMatrix[u][v] == 1) {
                    indegree[v]++;
                }
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

    bool AdMatrixDFS() { 

        vector<Color> colors(n, WHITE);

        hasCycle = false;

        int connectedComponents = 0;

        for (int u = 0; u < n; u++) {

            if (colors[u] == WHITE) {

                connectedComponents++;

                DFSVisit(u, colors);
            }
        }

        if (connectedComponents != 1)
            return false; // drzewo musi byæ spójne

    
        if (hasCycle)
			return false; // drzewo nie mo¿e zawieraæ cyklu

        if (!hasValidTreeStructure())
			return false; // ka¿dy wierzcho³ek oprócz korzenia musi mieæ dok³adnie 1 krawêdŸ wchodz¹c¹

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

    int n, m;

    cin >> n >> m;

    Graph G(n);

    for (int i = 0; i < m; i++) {

        int a, b;

        cin >> a >> b;

        G.addEdge(a, b);
    }

    if (G.AdMatrixDFS())
        cout << "TAK\n";
    else
        cout << "NIE\n";

    return 0;
}