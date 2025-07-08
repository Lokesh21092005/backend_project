#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second << 1);
    }
};
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<pair<int , int>>> parent(n , vector<pair<int , int>>(n , {-1 , -1}));
        vector<vector<bool>> visited(n , vector<bool> ( n , false));
        // unordered_map<pair<int , int> , int> umap;
        int max_size = 0;
        vector<int> x{0 , 1 , -1 , 0};
        vector<int> y{-1 , 0 , 0 , 1};
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(grid[i][j] == 1 && !visited[i][j]){
                    visited[i][j] = true;
                    vector<pair<int , int>> cur_island_neighs;
                    int island_size = 1;
                    queue<pair<int , int>> q;
                    q.push({i , j});
                    while(!q.empty()){
                        pair<int , int> top = q.front();
                        q.pop();
                        for(int k = 0 ; k < 4 ; k++){
                            int x1 = top.first + x[k];
                            int y1 = top.second + y[k];
                            if(x1 >=0 && y1 >= 0 && x1 < n && y1 < n){
                                if(!visited[x1][y1] && grid[x1][y1]==1){
                                    visited[x1][y1] = true;
                                    cur_island_neighs.push_back({x1 , y1});
                                    parent[x1][y1] = {i , j};
                                    q.push({x1 , y1});
                                    island_size++;
                                }
                            }
                        }
                    }
                    max_size = max(max_size , island_size);
                    for(auto is : cur_island_neighs){
                        grid[is.first][is.second] = island_size;
                    }
                }
            }
        }
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(grid[i][j] == 0){
                    int cur_max = 1;
                    unordered_set<pair<int , int> , pair_hash> neigh_check;
                    for(int k = 0 ; k < 4 ; k++){
                        int x1 = i+x[k];
                        int y1 = j+y[k];
                        if(x1 >=0 && y1 >= 0 && x1 < n && y1 < n && neigh_check.find(parent[x1][y1]) == neigh_check.end()){
                            cur_max+=grid[x1][y1];
                            cout<<x1<<" "<<y1<<" "<<cur_max<<endl;
                            neigh_check.insert(parent[x1][y1]);
                        }
                    }
                    max_size = max(max_size , cur_max);
                    cout<<max_size<<endl;
                }
            }
        }
        return max_size;
    }

    int main(){
        vector<vector<int>> grid;
        grid = {{1 , 0} , {0 , 1}};
        largestIsland(grid);

        for(int i = 0 ; i < grid.size() ; i++){
            for(int j = 0 ; j < grid.size() ; j++){
                cout<<grid[i][j]<<" ";
            }
            cout<<endl;
        }
    }






















