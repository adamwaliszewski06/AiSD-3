/*
1. zaimplementuj reprezentacje grafu:  lista krawedzi, macierz sasiedztwa,lista nastepnikow
2. Zaimplementuj generowanie w pelni losowego, skierowanego grafu
3. Zaimplementuj algorytm DFS dla macierzy sasiedztwa i dla list nastêpnikow
4. Wykonaj eksperymenty obliczeniowe dla liczby wierzcholkow 100, 200, …, 1000 i dla gestosci 1/8, 2/8, …, 7/8
5. Przedstaw wyniki w sprawozdaniu (po jednym wykresie na reprezentacje grafu) i porownaj zmierzone czasy dzialania

I. Przygotuj implementacje i eksperymenty obliczeniowe jak poprzednio, ale rowniez dla algorytmu BFS

*/

#include <cmath>
#include <cstdio>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

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
        //  cout << "LISTA KRAWEDZI:\n";

        sort(edgeList.begin(), edgeList.end());

        for (auto edge : edgeList) {
            cout << edge.first << " -> " << edge.second << "\n";
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

    int n = 6;
    double density = 0.3;

    Graph G(n);

    generateRDG(G, n, density);

    G.printEdgeList();

    G.printAdjacencyMatrix();

    G.printSuccessorList();

    return 0;
}