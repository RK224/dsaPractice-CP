#include <bits/stdc++.h>

using namespace std;

int pathGridRec(int r_s, int c_s, vector<vector<int>> grid, vector<pair<int,int>> &path){
	int r_e = grid.size()-1, c_e = grid[0].size()-1;
	if(r_s > r_e || c_s > c_e) return INT_MIN;
	else if( r_s == r_e && c_s == c_e) {
		path.push_back({r_s,c_s});
		return grid[r_s][c_s] ;
	}else{
		vector<pair<int,int>> path_down, path_right;
		int down = pathGridRec(r_s + 1, c_s, grid,path_down), right = pathGridRec(r_s, c_s + 1, grid,path_right);
		if(down > right) path.insert(path.begin(), path_down.begin(), path_down.end());
		else path.insert(path.begin(), path_right.begin(), path_right.end());
		path.push_back({r_s,c_s});
		return grid[r_s][c_s] + max(down,right);
	}
}

int pathGridDP(vector<vector<int>> grid){
	int n_r = grid.size(), n_c = grid[0].size();
	vector<vector<int>> points(n_r,vector<int>(n_c,0));
	stack<int> path;
	points[0][0] = grid[0][0];
	for(int r = 1 ; r < n_r ; r++) points[r][0] = grid[r][0] + points[r-1][0];
	for(int c = 1 ; c < n_c ; c++) points[0][c] = grid[0][c] + points[0][c-1];
	for(int r = 1 ; r < n_r ; r++){
		for(int c = 1; c < n_c; c++){
			points[r][c] = grid[r][c] + max(points[r-1][c], points[r][c-1]);
		}
	}

	int r = n_r-1 , c = n_c -1 ;
	while(r >= 0 && c >= 0){
		path.push(grid[r][c]);
		if(r == 0) {
			c--;
		}else if(c == 0){
			r--;
		}else{
			int down = points[r-1][c], right = points[r][c-1];
			if(down > right){
				r--;
			}else{
				c--;
			}
		}
	}

	while(!path.empty()){
		cout << path.top() << " " ; path.pop();
	}
	cout << endl;
	return points[n_r-1][n_c-1];
}

void printPath(vector<vector<int>> grid, vector<pair<int,int>> path){
	reverse(path.begin(), path.end());
	for(pair<int,int> r_c : path){
		int r = r_c.first, c = r_c.second;
		cout << grid[r][c] << " ";
	}
	cout << endl;
}

int main(void){
	vector<pair<int,int>> path;
	vector<vector<int>> grid = {{3,7,9,2,7}, {9,8,3,5,5}, {1,7,9,8,5}, {3,8,6,4,10}, {6,3,9,7,8}};
	cout << pathGridRec(0,0,grid,path) << endl;
	printPath(grid,path);
	cout << pathGridDP(grid) << endl;
}
