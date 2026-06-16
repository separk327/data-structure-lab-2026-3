#include "PrimeMST.h"

int getMinVertex(const WGraph& g, bool* selected, int* dist) {
	int minv = 0;
	int mindist = INF;
	for (int v = 0; v < g.getSize(); v++)
		if (!selected[v] && dist[v] < mindist) {
			mindist = dist[v];
			minv = v;
		}
	return minv;
}

void Prime(const WGraph& g, int s) {
	bool selected[MAX_VTXS];
	int dist[MAX_VTXS];
	int graphSize = g.getSize();
	for (int i = 0; i < graphSize; i++) {
		dist[i] = INF;
		selected[i] = false;
	}
	dist[s] = 0;
	for (int i = 0; i < graphSize; i++) {
		int u = getMinVertex(g, selected, dist);
		selected[u] = true;
		if (dist[u] == INF) return;
		printf("%c", g.getVertex(u));
		for (int v = 0; v < graphSize; v++)
			if (g.getEdge(u, v) != INF)
				dist[v] = g.getEdge(u, v);
	}
	printf("\n");
}

void main()
{
	WGraphDijkstra g;
	g.load("graph_sp.txt");
	printf("Shortest Path By Dijkstra Algorithm\n");
	g.ShortPath(0);
}