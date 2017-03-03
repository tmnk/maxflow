#include <iostream>
using namespace std;

const int MAX_EDGE = 10000;
const int MAX_VERTEX = 2000;
const int MAX_WEIGHT   = 1000000000;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_EDGE], onEnd[MAX_EDGE], nextEdge[MAX_EDGE], edgeCount;
int firstEdge[MAX_VERTEX], visited[MAX_VERTEX];

void addEdge(int u, int v, int cap) {
    // ������ �����
    onEnd[edgeCount] = v;                   // �� ����� ������� v
    nextEdge[edgeCount] = firstEdge[u];     // ��������� � ������ ������ ��� u
    firstEdge[u] = edgeCount;               // ������ ������ ������ - ����� �����
    capacity[edgeCount++] = cap;            // ������������� ���������� �����������
    // �������� �����
    onEnd[edgeCount] = u;                   // �� ����� ��������� u
    nextEdge[edgeCount] = firstEdge[v];     // ��������� � ������ ������ ��� v
    firstEdge[v] = edgeCount;               // ������ ������ ������ - ����� �����
    capacity[edgeCount++] = 0;              // ������������� ���������� �����������
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; // ���������� ���������� ������� �� ����
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, min(flow, capacity[edge])); // ���� ����� � ���������
            if (minResult > 0) {                    // ���� �����
                capacity[edge]      -= minResult;   // � ������ ����� �������� �����
                capacity[edge ^ 1]  += minResult;   // � �������� ����������
                return minResult;
            }
        }
    }
    return 0; // ���� �� ����� ����� �� ���� ������� ������ 0
}

int main() {
    fill(firstEdge, firstEdge + MAX_VERTEX, -1);     // -1 �������� ����� ���
    cin >> numOfVertex >> numOfEdge;            // ��������� ���������� ������ � �����
	sourceVertex = 1;
	destinationVertex = numOfVertex;
    for (int i = 0, u, v, cap; i < numOfEdge; i++) {
        cin >> u >> v >> cap;
        addEdge(u, v, cap);
    }
    // ���������� ������������� ������
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, MAX_WEIGHT)) > 0) {
        fill(visited, visited + MAX_VERTEX, false);
        maxFlow += iterationResult;
    }
    // ������� ������������ �����
    cout << maxFlow << endl;
    return 0;
}