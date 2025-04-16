//Kamaaksha Rajendra Kharul
//123B1B047
//Assignment 4
#include <iostream>
#include <vector>
#include <queue>
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

void displayMST(vector<pair<int, int>>& mst){
    for (auto it : mst){
        cout << it.first << " -> " << it.second << endl;
    }
    return;
}

int Prims(vector<vector<int>> &graph, int n, int source){
    vector<bool> visited(n, 0);
    //vector<int> parent(n, -1);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    // this is a min heap i.e., a priority queue which has wt and node
    // initialize 0 as the start node
    int sum = 0;
    vector<pair<int, int>> mst;
    pq.push({0, {source, -1}});
    //parent[source] = -1;
    
    while (!pq.empty()){
        auto ele = pq.top();
        pq.pop();
        int node = ele.second.first; 

        if (visited[node]) 
            continue; 

        // if parent is -1 then it's the start node
        // don't add it to mst or sum
        if (ele.second.second != -1){
            sum += ele.first;
            // mst madhe we will add this edge
            // mst madhe : (parent, node)
            mst.push_back({ele.second.second, node});
        }
        // mark the node as visited
        visited[node] = 1;
        
        // stand at the node
        // take all its adjacent nodes into pq
        for (int i = 0; i < n; i++){
            if (!visited[i] && graph[node][i] != 0){
                // add it to the priority queue
                pq.push({graph[node][i], {i, node}});
            }
        }
    }
    displayMST(mst);
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
    int sum = Prims(graph, n, src);
    cout << "MST cost = " << sum << endl;
    return 0;
}