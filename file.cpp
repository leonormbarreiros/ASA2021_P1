#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector <vector <int> > graph;
vector<int> in_degree;
vector<int> colors;
vector<int> deepest_path_from;

void initGraph(int V) {
    
    in_degree = vector<int>(V);
    colors = vector<int>(V);
    deepest_path_from = vector<int>(V);

    for (int i = 0; i < V; i++) {
        colors[i] = 0;
        deepest_path_from[i] = 0;
        in_degree[i] = 0;
    }
}

void readGraph(int E) {
    for (int i = 0; i < E; i++) {
        int u,v;
        scanf("%d %d", &u, &v);
        graph[u-1].push_back(v-1);
        in_degree[v-1]++;
    }
}

int calculateK() {
    int min = 0;
    for (int i = 0; i < (int) graph.size(); i++) {
        if (in_degree[i] == 0) {
            min++;
        }
    }
    return min;
}

void topSort(int vertex) {
    stack<int> vertexes;
    vertexes = stack<int>();

    vertexes.push(vertex);

    while (!vertexes.empty()) {
        int u = vertexes.top();

        if (colors[u] == 1) {
            colors[u] = 2;
            vertexes.pop();
        } else if (colors[u] == 0) {
            colors[u] = 1;
        } else {
            vertexes.pop();
        }

        for (int i = 0; i < (int) graph[u].size(); i++) {
            int v = graph[u][i];
            if (colors[v] == 0) {
                vertexes.push(v);
            }
            if (deepest_path_from[v] + 1 > deepest_path_from[u]) {
                deepest_path_from[u] = deepest_path_from[v] + 1;
            }
        }
    }  
}

int calculateL() {
    
    for (int i = 0; i < (int) graph.size(); i++) {
        if (colors[i] == 0) {
            topSort(i);
        }
    }
    int max = 0;
    for (int i = 0; i < (int) graph.size(); i++) {
        if (deepest_path_from[i] > max) {
            max = deepest_path_from[i];
        }
    }
    return max;
}

int main() {
    int V, E;
    int k, l;

    scanf("%d %d", &V, &E);
    graph = vector<vector <int> >(V, vector<int>());

    initGraph(V);
    readGraph(E);

    k = calculateK();
    l = calculateL() + 1;
    
    printf("%d %d\n", k, l);
}
