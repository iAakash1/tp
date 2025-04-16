// Kamaaksha Rajendra Kharul
// 123B1B047
// Assignment 3

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

vector<vector<int>> createMaze(int n){
    vector<vector<int>> maze(n, vector<int>(n, 0));   
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            int cost;
            cout << "Enter connection between " << i << " and " << j << " : ";
            cin >> cost;
            maze[i][j] = cost;
            maze[j][i] = cost;
        }
    }
    return maze;
}

void display(vector<vector<int>> &maze, int n){
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cout << maze[i][j] << "\t";
        }
        cout << endl;
    }
}

void bfsMain(vector<vector<int>>&maze, vector<bool>&visited, int src, vector<int>&bfs){
    queue<int> q;
    visited[src] = 1;
    q.push(src);
    
    while(!q.empty()){
        int ele = q.front();
        q.pop();
        bfs.push_back(ele);
        
        for(int i = 0; i < maze[ele].size(); i++){ 
            if(maze[ele][i] == 1 && !visited[i]){
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

vector<int> BFS(vector<vector<int>>&maze, int n){
    vector<bool> visited(n, false);
    vector<int> bfs;
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            bfsMain(maze, visited, i, bfs);
        }
    }
    return bfs;
}

void DFSMain(vector<vector<int>>&maze, int src, vector<bool>&visited, vector<int>&dfs){
    stack<int> st;
    st.push(src);

    while(!st.empty()){
        int ele = st.top();
        st.pop();
        if(!visited[ele]){
            dfs.push_back(ele);
            visited[ele] = 1;
        }
        for(int i = 0; i < maze.size(); i++){
            if(maze[ele][i] == 1 && !visited[i]){
                st.push(i);
            }
        }
    }
}

vector<int> DFS(vector<vector<int>>&maze, int n){
    vector<int> dfs;
    vector<bool> visited(n, false);
    
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            DFSMain(maze, i, visited, dfs);
        }
    }
    return dfs;
}

void displayArr(vector<int>&arr){
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i];
        if(i != arr.size()-1)
            cout << " -> ";
    }
    cout << endl;
}

int main(){
    int n;
    cout << "Enter number of vertices present in maze: ";
    cin >> n;
    cout << "Enter 1 for connected and 0 for not connected" << endl;
    
    vector<vector<int>> maze = createMaze(n);
    display(maze, n);

    vector<int> bfs = BFS(maze, n);
    cout << "BFS Path of the maze: " << endl;
    displayArr(bfs);

    vector<int> dfs = DFS(maze, n); 
    cout << "DFS Path of the maze: " << endl;
    displayArr(dfs);
    
    return 0;
}
