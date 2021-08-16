#include <bits/stdc++.h>
using namespace std;

map<int,vector<int>> getAdjacencyList(vector<pair<int,int>> edges){
	map<int,vector<int>> adjList;
	int x, y;
	for(pair<int,int> edge : edges){
		x = edge.first; y = edge.second;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}
	return adjList;
}

vector<vector<int>> getAdjacencyMatrix(vector<pair<int,int>> edges, int n){
	vector<vector<int>> adjMatrix(n,vector<int>(n,0));
	int x,y;
	for(pair<int,int> edge : edges){
		x = edge.first , y = edge.second;
		adjMatrix[x][y] = 1;
		adjMatrix[y][x] = 1;
	}
	return adjMatrix;
}

void printAdjacencyList(map<int,vector<int>>adjList){
	for(pair<int,vector<int>> adjNodes : adjList){
		cout << "neighbors of node " << adjNodes.first << " : ";
		for(int node : adjNodes.second) cout << node << " " ;
		cout << endl;
	}
}

void printAdjacencyMatrix(vector<vector<int>> adjMatrix){
	for(vector<int> v : adjMatrix){
		for(int i : v) cout << i << " " ;
		cout << endl;
	}
}

void printEdgeList(vector<pair<int,int>> edges){
	for(pair<int,int> edge : edges) cout << edge.first << " " << edge.second << endl;
}

void dfsHelp(int st, map<int,vector<int>> adjList, vector<int> &visited, vector<int> &prev, vector<vector<int>> &paths, vector<int> &path,bool print = true){
	if(visited[st]){
		path.push_back(st);
		paths.push_back(path);
		path.pop_back();
		return;
	}else{
		visited[st] = 1;
		if(print) cout << st << endl;
		for(int adjNode : adjList[st]){
			path.push_back(st);
			if(adjNode != prev[st]){
				prev[adjNode] = st;
				dfsHelp(adjNode, adjList, visited, prev, paths, path, print);
			}
			path.pop_back();
		}
	}
}

void dfs(int st, map<int,vector<int>> adjList){
	int n = adjList.size();
	vector<int> visited(n, 0), prev(n, -1), path;
	vector<vector<int>> paths;
	dfsHelp(st,adjList,visited,prev,paths,path);
}


void bfs(int st, map<int,vector<int>> adjList){
	int n = adjList.size();
	vector<int> visited(n,0), prev(n,-1), dist(n, INT_MAX);
	queue<int> queuedToVisit;
	queuedToVisit.push(st);
	visited[st] = 1;
	dist[st] = 0;
	int curr_node;
	while(!queuedToVisit.empty()){
		curr_node = queuedToVisit.front();
		queuedToVisit.pop();
		for(int adjNode : adjList[curr_node]){
			if(adjNode != prev[curr_node] && !visited[adjNode]){
				prev[adjNode] = curr_node;
				queuedToVisit.push(adjNode);
				visited[adjNode] = 1;
			}
		}
		if(curr_node != st) dist[curr_node] = min(dist[prev[curr_node]] + 1, dist[curr_node]);
		cout << curr_node << endl;
	}
}

int getUnvisited(vector<int> visited){
	int unvisitedIdx = -1;
	for(int i = 0 ; i < visited.size() ; i++){
		if(!visited[i]){
			unvisitedIdx = i;
			break;
		}
	}
	return unvisitedIdx;
}

bool isConnectedGraph(map<int,vector<int>> adjList){
	int n = adjList.size();
	vector<int> visited(n,0), prev(n,-1);
	int unvisitedIdx = getUnvisited(visited);
	vector<vector<int>> paths;
	vector<int> path;
	dfsHelp(unvisitedIdx, adjList, visited, prev, paths, path,false);
	unvisitedIdx = getUnvisited(visited);
	return unvisitedIdx == -1 ;
}

vector<vector<int>> getConnectedComponents(map<int,vector<int>> adjList){
	int n = adjList.size();
	vector<int> visited(n,0), prev(n,-1);
	int unvisitedIdx;
	vector<int> component, path;
	vector<vector<int>> connectedComponents, paths;

	while((unvisitedIdx = getUnvisited(visited)) != -1){
		dfsHelp(unvisitedIdx, adjList, visited, prev, paths, path,false);
		for(int i = 0; i < visited.size(); i++){
			if(visited[i] == 1) {
				component.push_back(i);
				visited[i] += 1;
			}
		}
		connectedComponents.push_back(component);
		component.clear();
	}
	return connectedComponents;
}

vector<vector<int>> getCycleFromPaths(vector<vector<int>> paths){
	if(paths.size() == 0) return paths;
	else{
		vector<vector<int>> cycles;
		vector<int> cycle;
		for(vector<int> path : paths){
			bool cycleStart = false;
			for(int node : path){
				if(node == path.back()) cycleStart = true;
				if(cycleStart) cycle.push_back(node);
			}
			cycles.push_back(cycle);
			cycle.clear();
		}
		return cycles;
	}
}

vector<vector<int>> getCycles(map<int,vector<int>> adjList){
 	int n = adjList.size();
	vector<int> visited(n,0), prev(n,-1), path;
	vector<vector<int>> paths;
	int unvisitedIdx;
	while((unvisitedIdx = getUnvisited(visited)) != -1){
		dfsHelp(unvisitedIdx, adjList, visited, prev, paths, path, false);
	}
	vector<vector<int>> cycles = getCycleFromPaths(paths);
	return cycles;
}

int main(int argc, char* argv[]){
	vector<pair<int,int>> edges;
	const char* fileName;
	if(argc == 2){
		fileName = argv[1];
	}else{
		string defaultFile= "cycle.txt";
		fileName = defaultFile.c_str();
	}
	freopen(fileName,"r", stdin);
	int n,x,y;
	cin >> n ;
	while(cin >> x >> y) edges.push_back({x,y});

	printEdgeList(edges);

	map<int,vector<int>> adjList = getAdjacencyList(edges);
	printAdjacencyList(adjList);

	vector<vector<int>> adjMatrix = getAdjacencyMatrix(edges,n);
	printAdjacencyMatrix(adjMatrix);

	cout << "DFS traversal" << endl;
	dfs(0, adjList);

	cout << "BFS traversal" << endl;
	bfs(0, adjList);

	cout << "isConnectedGraph : " << isConnectedGraph(adjList) << endl;

	vector<vector<int>> connectedComponents = getConnectedComponents(adjList);
	cout << "Connected components" << endl;
	for(vector<int> component : connectedComponents){
		for(int node : component) cout << node << " " ;
		cout << endl;
	}

	vector<vector<int>> cycles = getCycles(adjList);
	cout << "Cycles : " << cycles.size() << endl;
	for(vector<int> cycle : cycles){
		for(int node : cycle) cout << node << " " ;
		cout << endl;
	}
}
