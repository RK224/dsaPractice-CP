#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

void printPath(vector<pair<int,int>> path){
	for(pair<int,int> point : path) cout << "--( " << point.first << " , " << point.second << " ) " ;
	cout << endl;
}

bool visitedPoint(int r, int c, int r_end, int c_end, vector<vector<bool>> visited){
	if( r >= 0 && r <= r_end && c >=0 && c <= c_end) return visited[r][c];
	else return true;
}

void noOfPathHelp(int r, int c, int r_end, int c_end, vector<pair<int,int>> &curr_path, vector<vector<bool>> &visited, int visited_count, vector<vector<pair<int,int>>> &paths){
	visited[r][c] = true;
	visited_count++;
	int total = (r_end+1)*(c_end+1);
	curr_path.push_back(make_pair(r,c));
	if( r == r_end && c == c_end && visited_count == total){
		paths.push_back(curr_path);
	}else{
		if(!visitedPoint(r+1,c,r_end,c_end,visited)) noOfPathHelp(r+1, c, r_end, c_end, curr_path, visited, visited_count, paths);
		if(!visitedPoint(r,c+1,r_end,c_end,visited)) noOfPathHelp(r, c+1, r_end, c_end, curr_path, visited, visited_count, paths);
		if(!visitedPoint(r-1,c,r_end,c_end,visited)) noOfPathHelp(r-1, c, r_end, c_end, curr_path, visited, visited_count, paths);
		if(!visitedPoint(r,c-1,r_end,c_end,visited)) noOfPathHelp(r, c-1, r_end, c_end, curr_path, visited, visited_count, paths);
	}
	visited[r][c] = false;
	visited_count--;
	curr_path.pop_back();
}

void noOfPathHelpOpt2(int r, int c, int r_end, int c_end, vector<pair<int,int>> &curr_path, vector<vector<bool>> &visited, int visited_count, vector<vector<pair<int,int>>> &paths){
	visited[r][c] = true;
	visited_count++;
	int total = (r_end+1)*(c_end+1);
	curr_path.push_back(make_pair(r,c));
	if( r == r_end && c == c_end){
		if(visited_count == total) paths.push_back(curr_path);
	}else{
		if(!visitedPoint(r+1,c,r_end,c_end,visited)) noOfPathHelpOpt2(r+1, c, r_end, c_end, curr_path, visited, visited_count, paths);
		if(!visitedPoint(r,c+1,r_end,c_end,visited)) noOfPathHelpOpt2(r, c+1, r_end, c_end, curr_path, visited, visited_count, paths);
		if(!visitedPoint(r-1,c,r_end,c_end,visited)) noOfPathHelpOpt2(r-1, c, r_end, c_end, curr_path, visited, visited_count, paths);
		if(!visitedPoint(r,c-1,r_end,c_end,visited)) noOfPathHelpOpt2(r, c-1, r_end, c_end, curr_path, visited, visited_count, paths);
	}
	visited[r][c] = false;
	visited_count--;
	curr_path.pop_back();
}

void noOfPathHelpOpt3(int r, int c, int r_end, int c_end, vector<pair<int,int>> &curr_path, vector<vector<bool>> &visited, int visited_count, vector<vector<pair<int,int>>> &paths){
	visited[r][c] = true;
	visited_count++;
	int total = (r_end+1)*(c_end+1);
	curr_path.push_back(make_pair(r,c));
	if( r == r_end && c == c_end){
		if(visited_count == total) {
			paths.push_back(curr_path);
		}
	}else{
		if( (!visitedPoint(r,c+1,r_end,c_end,visited) && !visitedPoint(r,c-1,r_end,c_end,visited) && ( r == 0 || r == r_end) )
 || ( !visitedPoint(r+1,c,r_end,c_end,visited) && !visitedPoint(r-1,c,r_end,c_end,visited) && ( c == 0 || c == c_end) ) ){
		}else{
			if(!visitedPoint(r+1,c,r_end,c_end,visited)) noOfPathHelpOpt3(r+1, c, r_end, c_end, curr_path, visited, visited_count, paths);
			if(!visitedPoint(r,c+1,r_end,c_end,visited)) noOfPathHelpOpt3(r, c+1, r_end, c_end, curr_path, visited, visited_count, paths);
			if(!visitedPoint(r-1,c,r_end,c_end,visited)) noOfPathHelpOpt3(r-1, c, r_end, c_end, curr_path, visited, visited_count, paths);
			if(!visitedPoint(r,c-1,r_end,c_end,visited)) noOfPathHelpOpt3(r, c-1, r_end, c_end, curr_path, visited, visited_count, paths);
		}
	}
	visited[r][c] = false;
	visited_count--;
	curr_path.pop_back();
}


void noOfPathHelpOpt4(int r, int c, int r_end, int c_end, vector<pair<int,int>> &curr_path, vector<vector<bool>> &visited, int visited_count, vector<vector<pair<int,int>>> &paths){
	visited[r][c] = true;
	visited_count++;
	int total = (r_end+1)*(c_end+1);
	curr_path.push_back(make_pair(r,c));
	if( r == r_end && c == c_end){
		if(visited_count == total) {
			paths.push_back(curr_path);
		}
	}else{
		if( (!visitedPoint(r,c+1,r_end,c_end,visited) && !visitedPoint(r,c-1,r_end,c_end,visited) && visitedPoint(r-1,c,r_end,c_end,visited) && visitedPoint(r+1,c,r_end,c_end,visited)) 
|| ( !visitedPoint(r+1,c,r_end,c_end,visited) && !visitedPoint(r-1,c,r_end,c_end,visited) && visitedPoint(r,c-1,r_end,c_end,visited) && visitedPoint(r,c+1,r_end,c_end,visited) ) ){
		}else{
			if(!visitedPoint(r+1,c,r_end,c_end,visited)) noOfPathHelpOpt4(r+1, c, r_end, c_end, curr_path, visited, visited_count, paths);
			if(!visitedPoint(r,c+1,r_end,c_end,visited)) noOfPathHelpOpt4(r, c+1, r_end, c_end, curr_path, visited, visited_count, paths);
			if(!visitedPoint(r-1,c,r_end,c_end,visited)) noOfPathHelpOpt4(r-1, c, r_end, c_end, curr_path, visited, visited_count, paths);
			if(!visitedPoint(r,c-1,r_end,c_end,visited)) noOfPathHelpOpt4(r, c-1, r_end, c_end, curr_path, visited, visited_count, paths);
		}
	}
	visited[r][c] = false;
	visited_count--;
	curr_path.pop_back();
}

void noOfPathHelpOpt4Count(int r, int c, int r_end, int c_end, vector<vector<bool>> &visited, int visited_count, int &noPaths){
	visited[r][c] = true;
	visited_count++;
	int total = (r_end+1)*(c_end+1);
	if( r == r_end && c == c_end){
		if(visited_count == total) {
			noPaths = noPaths + 1;
		}
	}else{
		if( (!visitedPoint(r,c+1,r_end,c_end,visited) && !visitedPoint(r,c-1,r_end,c_end,visited) && visitedPoint(r-1,c,r_end,c_end,visited) && visitedPoint(r+1,c,r_end,c_end,visited)) 
|| ( !visitedPoint(r+1,c,r_end,c_end,visited) && !visitedPoint(r-1,c,r_end,c_end,visited) && visitedPoint(r,c-1,r_end,c_end,visited) && visitedPoint(r,c+1,r_end,c_end,visited) ) ){
		}else{
			if(!visitedPoint(r+1,c,r_end,c_end,visited)) noOfPathHelpOpt4Count(r+1, c, r_end, c_end, visited, visited_count,noPaths);
			if(!visitedPoint(r,c+1,r_end,c_end,visited)) noOfPathHelpOpt4Count(r, c+1, r_end, c_end, visited, visited_count,noPaths);
			if(!visitedPoint(r-1,c,r_end,c_end,visited)) noOfPathHelpOpt4Count(r-1, c, r_end, c_end, visited, visited_count,noPaths);
			if(!visitedPoint(r,c-1,r_end,c_end,visited)) noOfPathHelpOpt4Count(r, c-1, r_end, c_end, visited, visited_count,noPaths);
		}
	}
	visited[r][c] = false;
}

int countPaths(int r_start, int c_start, int r_end, int c_end){
	int noPaths = 0;
	vector<vector<bool>> visited(r_end+1,vector<bool>(c_end+1,false));
	noOfPathHelpOpt4Count(r_start, c_start+1, r_end, c_end, visited, 0, noPaths);
	return 2*noPaths;
}

vector<vector<pair<int,int>>> noOfPaths(int r_start, int c_start, int r_end, int c_end,void (*noOfPathHelp)(int, int, int, int, vector<pair<int,int>> &, vector<vector<bool>> &, int, vector<vector<pair<int,int>>> &)){
	vector<vector<pair<int,int>>> paths;
	vector<pair<int,int>> curr_path ;
	vector<vector<bool>> visited(r_end+1,vector<bool>(c_end+1,false));
	noOfPathHelp(r_start, c_start, r_end, c_end, curr_path, visited,0, paths);
	return paths;
}

vector<vector<pair<int,int>>> mirrorPaths(vector<vector<pair<int,int>>> paths){
	vector<vector<pair<int,int>>> mirror_paths;
	for(vector<pair<int,int>> path : paths){
		vector<pair<int,int>> mirroredPath;
		for(pair<int,int> point : path){
			pair<int,int> mirroredPoint = make_pair(point.second,point.first);
			mirroredPath.push_back(mirroredPoint);
		}
		mirror_paths.push_back(path); mirror_paths.push_back(mirroredPath);
	}
	return mirror_paths;
}

vector<vector<pair<int,int>>> noOfPathsOpt1(int r_start, int c_start, int r_end, int c_end,void (*noOfPathHelp)(int, int, int, int, vector<pair<int,int>> &, vector<vector<bool>> &, int, vector<vector<pair<int,int>>> &)){
	vector<vector<pair<int,int>>> paths;
	vector<pair<int,int>> curr_path;
	vector<vector<bool>> visited(r_end+1, vector<bool>(c_end+1, false));
	curr_path.push_back(make_pair(r_start, c_start));
	visited[r_start][c_start] = true;
	noOfPathHelp(r_start+1,c_start, r_end, c_end, curr_path, visited, 1, paths);
	return mirrorPaths(paths);
}


void printPaths(vector<vector<pair<int,int>>> paths){
	cout << "No of paths : " << paths.size() << endl;
	for(vector<pair<int,int>> path : paths) printPath(path);
}

void profileAndPrintResult(vector<vector<pair<int,int>>> (*noOfPaths)(int, int, int,int,void (*help)(int,int,int,int,vector<pair<int,int>> &, vector<vector<bool>> &, int, vector<vector<pair<int,int>>> &)), void (*help)(int, int, int, int, vector<pair<int,int>> &, vector<vector<bool>> &, int, vector<vector<pair<int,int>>> &), int r_start, int c_start, int r_end, int c_end){
	auto start = high_resolution_clock::now();
	vector<vector<pair<int,int>>> paths = noOfPaths(r_start,c_start,r_end,c_end, help);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop-start).count();
	cout<< "Computing result took duration : " << duration << " ms" << endl;
	printPaths(paths);
	return;
}

int main(void){
	int r_end = 3, c_end = 3;
	profileAndPrintResult(noOfPaths, noOfPathHelp,0,0,r_end, c_end);
	profileAndPrintResult(noOfPathsOpt1, noOfPathHelp, 0,0,r_end,c_end);
	profileAndPrintResult(noOfPathsOpt1, noOfPathHelpOpt2, 0,0,r_end,c_end);
	profileAndPrintResult(noOfPathsOpt1, noOfPathHelpOpt3, 0,0,r_end,c_end);
	profileAndPrintResult(noOfPathsOpt1, noOfPathHelpOpt4, 0,0,r_end,c_end);
	auto start = high_resolution_clock::now();
	int paths = countPaths(0,0,r_end,c_end);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop-start).count();
	cout<< "Computing result took duration : " << duration << " ms" << endl;
	cout << paths << endl;
}
