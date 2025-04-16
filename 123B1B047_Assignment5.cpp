//Kamaaksha Rajendra Kharul
//123B1B047
//Assignment 1
#include <iostream>
#include <vector>
#include <queue>
#include<climits>
using namespace std;

vector<vector<int>> createGraph(int n){
    vector<vector<int>> graph(n, vector<int>(n, 0));   
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            int cost;
            cout << "Enter the cost of edge between " << i  << " and " << j  << " (Enter 0 if no edge): ";
            cin >> cost;
            graph[i][j] = cost;
            graph[j][i] = cost;
        }
    }
    return graph;
}

void display(vector<vector<int>> &graph, int n){
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }
}

void displayArr(vector<int>&arr){
    for (auto it : arr){
        cout << it << "\t";
    }
    cout << endl;
    return;
}

int Dijikstra(vector<vector<int>> &graph, int n, int source){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // this is a min heap i.e., a priority queue which has wt and node
    // initialize 0 as the start node
    int sum = 0;
    vector<int>dist(n, INT_MAX);
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()){
        pair<int, int> ele = pq.top();
        pq.pop();
        int u = ele.second; 
        int wt = ele.first;
        //d(u) + wt[u][v] < d(v) update d(v)
        sum = wt;
        for(int v = 0; v < n; v++){
            if(graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }
    displayArr(dist);
    return sum;
}

int main(){
    int n;
    cout << "Enter number of vertices of your graph: ";
    cin >> n;
    vector<vector<int>> graph = createGraph(n);
    display(graph, n);
    int src;
    cout << "Enter source node (0 to " << n-1 << ") : ";
    cin >> src;
    int sum = Dijikstra(graph, n, src);
    cout << "Total cost = " << sum << endl;
    return 0;
}