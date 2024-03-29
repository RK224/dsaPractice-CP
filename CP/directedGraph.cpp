#include <bits/stdc++.h>

using namespace std;

int getUnprocessed(vector<int> state, int n){
	int unprocessed = -1;
	for(int i = 0 ; i < n ; i++){
		if(state[i] == 0){
			unprocessed = i;
			break;
		}
	}

	return unprocessed;
}

void dfs(int st, vector<vector<int>> adjList, vector<int> &state, vector<int> &sorted, bool &isCycle){
	if (state[st] == 2) return ;
	else if (state[st] == 1) {
		isCycle = true; //Not possible to sort topologically because of cycle
		return;
	} else {
		state[st] = 1;
		for(int node : adjList[st]){
			dfs(node, adjList, state, sorted, isCycle);
		}
		sorted.push_back(st);
		state[st] = 2;
	}
}

vector<int> topologicalSort(vector<vector<int>> adjList, int n){
	vector<int> sorted;
	vector<int> state(n,0); //0 -- not processed, 1 -- processing, 2 -- processed
	int unprocessed;
	bool isCycle = false;
	while(( unprocessed = getUnprocessed(state,n) ) != -1){
		dfs(unprocessed, adjList, state, sorted, isCycle);
		if(isCycle){
			sorted.clear();
			break;
		}
	}
	reverse(sorted.begin(), sorted.end());
	return sorted;
}

void printTopologicalSort(vector<vector<int>> adjList, int n){
	vector<int> sorted = topologicalSort(adjList, n);
	if(sorted.empty()) cout << "Graph contains a cycle, not possible to sort topologically" << endl;
	else{
		for(int node : sorted) cout << node << " " ;
		cout << endl;
	}
}

int numberPaths(int st, int en, vector<vector<int>> adjList, int n){
	vector<int> sorted = topologicalSort(adjList, n);
	vector<int> n_paths(n,0);
	n_paths[en] = 1;
	int r = n - 1;
	while(sorted[r] != en) r--;
	for(int i = r - 1; i >= 0 ; i--){
		int v = sorted[i];
		int nPaths_v = 0;
		for(int node : adjList[v]) nPaths_v += n_paths[node];
		n_paths[v] = nPaths_v;
	}
	return n_paths[st];
}

vector<int> shortestPath(int st, int en, vector<vector<int>> adjList, int n){
	vector<int> sorted = topologicalSort(adjList, n);
	vector<int> dist(n, INT_MAX);
	vector<vector<int>> shortest_path(n, vector<int>());
	dist[en] = 0;
	shortest_path[en].push_back(en);
	int r = n-1;
	while(sorted[r] != en) r--;

	for(int i = r-1; i >= 0; i--){
		int v = sorted[i];
		int closestNode = -1;
		int disFromV = INT_MAX;
		for(int adjNode : adjList[v]){
			if(dist[adjNode] < disFromV){
				disFromV = dist[adjNode];
				closestNode = adjNode;
			}
		}

		if(disFromV != INT_MAX && closestNode != -1){
			shortest_path[v].push_back(v);
			dist[v] = 1 + disFromV;
			shortest_path[v].insert(shortest_path[v].end(), shortest_path[closestNode].begin(), shortest_path[closestNode].end() );
		}
	}
	return shortest_path[st];
}

int main(int argc, char* argv[]){
	bool fromTerm = true;
	if(argc == 2){
		fromTerm = false;
		freopen(argv[1],"r", stdin);
	}else cout << "No input file, taking input from stdin" << endl;
	int n,a,b;
	if(fromTerm) cout << "Input number of nodes : " << endl;
	cin >> n ;
	if(fromTerm) cout << "Input edges, press ctrl + D when done" << endl;
	vector<pair<int,int>> edges;
	while( cin >> a >> b ) edges.push_back({a,b});
	vector<vector<int>> adjList(n, vector<int>());
	for(pair<int,int> edge : edges) adjList[edge.first].push_back(edge.second);
	vector<int> sorted = topologicalSort(adjList, n);
	int st, en;
	st = sorted[2]; en = sorted[n-2];
	cout << "Number of paths between " << st << " and " << en << " : " << numberPaths(st, en, adjList, n) << endl;
//	st = 0; en = 5;
	vector<int> shortest_path = shortestPath(st, en, adjList, n);
	cout << "shortest path between " << st << " and " << en << " : " ;
	for(int node : shortest_path) cout << node << " " ;
	cout << endl;
}
