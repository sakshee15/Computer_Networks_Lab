#include <iostream>
#include <iomanip>
#include <limits>

using namespace std; // Adding the namespace

const int MAX = 9999;
const int MAX_NODES = 10;
int graph[MAX_NODES][MAX_NODES];
int numNodes;

void dijkstra(int startNode) {
    int cost[MAX_NODES][MAX_NODES], distance[MAX_NODES], pred[MAX_NODES];
    bool visited[MAX_NODES];
    int count, mindistance, nextnode, i, j;

    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            if (graph[i][j] == 0)
                cost[i][j] = MAX;
            else
                cost[i][j] = graph[i][j];
        }
    }

    for (i = 0; i < numNodes; i++) {
        distance[i] = cost[startNode][i];
        pred[i] = startNode;
        visited[i] = false;
    }

    distance[startNode] = 0;
    visited[startNode] = true;
    count = 1;

    while (count < numNodes - 1) {
        mindistance = MAX;

        for (i = 0; i < numNodes; i++) {
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        visited[nextnode] = true;
        for (i = 0; i < numNodes; i++) {
            if (!visited[i]) {
                if (mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }

    cout << "Node\tDistance\tPath\n";
    for (i = 0; i < numNodes; i++) {
        if (i != startNode) {
            cout << setw(3) << i << "\t" << distance[i] << "\t\t" << i;
            j = i;
            do {
                j = pred[j];
                cout << " <- " << j;
            } while (j != startNode);
            cout << endl;
        }
    }
}

void printGraph() {
    cout << "\n\nGraph:\n";
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            cout << setw(3) << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n\n";
}

int main() {
    numNodes = 7;
    int edges[MAX_NODES][MAX_NODES] = {
        {0, 2, 0, 0, 3, 0, 0},
        {2, 0, 5, 0, 0, 0, 0},
        {0, 5, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 4, 0, 0},
        {3, 0, 0, 4, 0, 6, 0},
        {0, 0, 0, 0, 6, 0, 2},
        {0, 0, 0, 0, 0, 2, 0}
    };

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph[i][j] = edges[i][j];
        }
    }

    printGraph();

    int startNode = 4;
    dijkstra(startNode);

    return 0;
}
