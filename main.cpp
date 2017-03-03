#include <iostream>
using namespace std;

const int MAX_EDGE = 10000;
const int MAX_VERTEX = 2000;
const int MAX_WEIGHT   = 1000000000;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_EDGE], onEnd[MAX_EDGE], nextEdge[MAX_EDGE], edgeCount;
int firstEdge[MAX_VERTEX], visited[MAX_VERTEX];

void addEdge(int u, int v, int cap) {
    // Прямое ребро
    onEnd[edgeCount] = v;                   // на конце прямого v
    nextEdge[edgeCount] = firstEdge[u];     // добавляем в начало списка для u
    firstEdge[u] = edgeCount;               // теперь начало списка - новое ребро
    capacity[edgeCount++] = cap;            // устанавливаем пропускную способность
    // Обратное ребро
    onEnd[edgeCount] = u;                   // на конце обратного u
    nextEdge[edgeCount] = firstEdge[v];     // добавляем в начало списка для v
    firstEdge[v] = edgeCount;               // теперь начало списка - новое ребро
    capacity[edgeCount++] = 0;              // устанавливаем пропускную способность
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; // возвращяем полученный минимум на пути
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, min(flow, capacity[edge])); // ищем поток в поддереве
            if (minResult > 0) {                    // если нашли
                capacity[edge]      -= minResult;   // у прямых ребер вычетаем поток
                capacity[edge ^ 1]  += minResult;   // к обратным прибавляем
                return minResult;
            }
        }
    }
    return 0; // если не нашли поток из этой вершины вернем 0
}

int main() {
    fill(firstEdge, firstEdge + MAX_VERTEX, -1);     // -1 означает ребра нет
    cin >> numOfVertex >> numOfEdge;            // считываем количество вершин и ребер
	sourceVertex = 1;
	destinationVertex = numOfVertex;
    for (int i = 0, u, v, cap; i < numOfEdge; i++) {
        cin >> u >> v >> cap;
        addEdge(u, v, cap);
    }
    // Нахождение максимального потока
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, MAX_WEIGHT)) > 0) {
        fill(visited, visited + MAX_VERTEX, false);
        maxFlow += iterationResult;
    }
    // Выводим максимальный поток
    cout << maxFlow << endl;
    return 0;
}