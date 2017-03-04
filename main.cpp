#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
bool *visited;
int sourceVertex, destinationVertex, **graph, numOfVertex, numOfEdge;
bool bfs(int s, int t, int parent[]) {
    memset(visited, 0, sourceVertex * sizeof(bool));
    std::queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v=0; v < numOfVertex; v++) {
            if (visited[v]==false && graph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}

int fordFulkerson(int s, int t) {
    int u, v;
    int *parent = new int[numOfVertex];
    int max_flow = 0;
    while (bfs(s, t, parent)){
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v]) {
            u = parent[v];
            path_flow = std::min(path_flow, graph[u][v]);
        }
 
        for (v=t; v != s; v=parent[v]) {
            u = parent[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }
 
        max_flow += path_flow;
    }
    return max_flow;
}
int main() {
	std::cin >> numOfVertex >> numOfEdge;
	if (!numOfEdge || !numOfVertex) return 0;
	graph = new int*[numOfVertex];
	for (int i = 0; i < sourceVertex; i++) graph[i] = new int[numOfVertex];
	sourceVertex = 1;
	destinationVertex = numOfVertex;
    for (unsigned int i = 0, u, v, weight; i < numOfEdge; i++) {
        std::cin >> u >> v >> weight;
        graph[u][v] = weight;
    }
 
    std::cout << fordFulkerson(0, 5) << std::endl;
 
    return 0;
}