#include <iostream>
#include <limits.h>

const unsigned int MAX_VERTEX =       4004;
const unsigned int MAX_EDGE   =      20004;
const unsigned int MAX_WEIGHT =  UINT_MAX - 1;
unsigned int numOfVertex, numOfEdge, sourceVertex, destinationVertex, edgeCount;
unsigned int capacity[MAX_EDGE], onEnd[MAX_EDGE], nextEdge[MAX_EDGE], firstEdge[MAX_VERTEX], visited[MAX_VERTEX];

void addEdge(unsigned int u, unsigned int v, unsigned int cap) {
    onEnd[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount;
    capacity[edgeCount++] = cap;
    onEnd[edgeCount] = u;
    nextEdge[edgeCount] = firstEdge[v];
    firstEdge[v] = edgeCount;
    capacity[edgeCount++] = 0;
}

unsigned int findFlow(unsigned int u, unsigned int flow) {
    if (u == destinationVertex) return flow;
    visited[u] = 1;
    for (unsigned int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        unsigned int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            unsigned int minResult = findFlow(to, std::min(flow, capacity[edge]));
            if (minResult > 0) {
                capacity[edge]      -= minResult;
                capacity[edge + 1]  += minResult;
                return minResult;
            }
        }
    }
    return 0;
}

int main() {
    std::fill(firstEdge, firstEdge + MAX_VERTEX, -1);
    std::cin >> numOfVertex >> numOfEdge;
	if (!numOfEdge || !numOfVertex) return 0;
	sourceVertex = 1;
	destinationVertex = numOfVertex;
    for (unsigned int i = 0, u, v, weight; i < numOfEdge; i++) {
        std::cin >> u >> v >> weight;
        addEdge(u, v, weight);
    }
    unsigned int maxFlow = 0;
    unsigned int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, MAX_WEIGHT)) > 0) {
        std::fill(visited, visited + MAX_VERTEX, 0);
        maxFlow += iterationResult;
    }
    std::cout << maxFlow << std::endl;
    return 0;
}