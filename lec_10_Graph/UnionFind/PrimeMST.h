#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_VTXS = 100;
const int INF = 9999;
const int MAX_HEAP_NODE = MAX_VTXS * MAX_VTXS;

class AdjMatGraph {
protected:
    int size;                         // 정점 개수
    char vertices[MAX_VTXS];          // 정점 이름
    int adj[MAX_VTXS][MAX_VTXS];      // 인접 행렬

public:
    AdjMatGraph() {
        reset();
    }
    int getSize() const { return size; }
    void reset() {
        size = 0;

        for (int i = 0; i < MAX_VTXS; i++) {
            for (int j = 0; j < MAX_VTXS; j++) {
                if (i == j)
                    adj[i][j] = 0;
                else
                    adj[i][j] = INF;
            }
        }
    }

    bool isFull() const {
        return size >= MAX_VTXS;
    }

    void insertVertex(char name) {
        if (isFull()) {
            cout << "정점 개수 초과" << endl;
            return;
        }

        vertices[size++] = name;
    }

    char getVertex(int i) const {
        return vertices[i];
    }

    int getEdge(int i, int j) const {
        return adj[i][j];
    }

    void setEdge(int i, int j, int value) {
        adj[i][j] = value;
    }

    void display(const char* msg = "Graph") const {
        cout << msg << endl << endl;

        cout << "     ";
        for (int i = 0; i < size; i++) {
            cout << setw(5) << vertices[i];
        }
        cout << endl;

        for (int i = 0; i < size; i++) {
            cout << setw(5) << vertices[i];

            for (int j = 0; j < size; j++) {
                if (adj[i][j] >= INF)
                    cout << setw(5) << "INF";
                else
                    cout << setw(5) << adj[i][j];
            }

            cout << endl;
        }

        cout << endl;
    }
};

class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF)
            weight = INF;

        setEdge(u, v, weight);
    }

    bool hasEdge(int i, int j) const {
        return getEdge(i, j) < INF;
    }

    void load(const char* filename) {
        ifstream fin(filename);

        if (!fin) {
            cout << "파일을 열 수 없습니다: " << filename << endl;
            return;
        }

        reset();

        int n;
        fin >> n;

        if (n > MAX_VTXS) {
            cout << "정점 개수가 너무 많습니다." << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            char name;
            fin >> name;

            insertVertex(name);

            for (int j = 0; j < n; j++) {
                int value;
                fin >> value;

                insertEdge(i, j, value);
            }
        }

        fin.close();
    }
};

class WGraphDijkstra : public WGraph {
    int dist[MAX_VTXS];
    bool found[MAX_VTXS];
public: 
    int chooseVertex() {
        int min = INF;
        int minpos = -1;
        for(int i = 0; i<size; i++)
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        return minpos;
    }
    void printDistance() {
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }
    void ShortPath(int start) {
        for (int i = 0; i < size; i++) {
            dist[i] = getEdge(start, i);
            found[i] = false;
        }
        found[start] = true;
        dist[start] = 0;
        for (int i = 0; i < size; i++) {
            printf("Step%2d", i + 1);
            printDistance();
            int u = chooseVertex();
            found[u] = true;
            for (int w = 0; w < size; w++) {
                if (found[w] == false)
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
            }
        }
    }
};