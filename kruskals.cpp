//Kamaaksha Rajendra Kharul
//123B1B047
//Assignment 4
//Kruskal
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

void displayMST(vector<vector<int>>&path){
    for(int i = 0; i < path.size(); i++){
        cout << path[i][0] << " -> " << path[i][1] << " (" << path[i][2] << ") " << endl;
    }
    return;
}

int findParent(vector<int>&parent, int val){
    if(parent[val] == val){
        return val;
    }
    //path compression
    return parent[val] = findParent(parent, parent[val]);
}

void unionSet(int u, int v, vector<int>&parent, vector<int>&rank){
    int pu = findParent(parent, u);
    int pv = findParent(parent, v);
    //less rank la join kara
    //more rank wala is parent
    if(rank[pu] < rank[pv]){
        parent[pu] = pv;
        rank[pv]++;
    }
    else{
        parent[pv] = pu;
        rank[pu]++;
    }
}

int Kruskals(vector<vector<int>> &graph, int n){
    //assuming that nodes are from 0 to n-1
    vector<int>parent(n);
    vector<int>rank(n, 0);
    vector<vector<int>>path;
    //setting each node as a parent of itself
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }
    //w, u, v
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    //making the pq
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if(graph[i][j] != 0){
                pq.push({graph[i][j], {i, j}});
            }
        }
    }
    int sum = 0;
    while (!pq.empty()){
        auto ele = pq.top();
        pq.pop();
        int w = ele.first;
        int u = ele.second.first;
        int v = ele.second.second;
        int pu = findParent(parent, u);
        int pv = findParent(parent, v);
        if(pu != pv){
            //add that path to our mst
            unionSet(u, v, parent, rank);
            sum += w;
            path.push_back({u, v, w});
        }
    }
    displayMST(path);
    return sum;
}

int main(){
    int n;
    cout << "Enter number of vertices of your graph: ";
    cin >> n;
    vector<vector<int>> graph = createGraph(n);
    display(graph, n);
    int sum = Kruskals(graph, n);
    cout << "MST cost = " << sum << endl;
    return 0;
}