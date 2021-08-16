#include <bits/stdc++.h>
using namespace std;

bool reduction(tuple<int,int,int> edge, vector<int> &dist){
	int a,b,w;
	a = get<0>(edge); b = get<1>(edge); w = get<2>(edge);
	bool mod_b = false;
	if(dist[a] != INT_MAX){
		int path_a = dist[a] + w;
		if(path_a < dist[b]){
			mod_b = true;
			dist[b] = path_a;
		}
	}
	return mod_b;
}

pair<bool,vector<int>> bellmanFord(vector<tuple<int,int,int>> weightedEdges, int n, int st){
	vector<int> dist(n, INT_MAX);
	dist[st] = 0;
	bool negLenCycleExists;
	for(int i = 0; i < n; i++){
		negLenCycleExists = false;
		for(tuple<int,int,int> edge : weightedEdges) negLenCycleExists |= reduction(edge, dist);
	}
	return {negLenCycleExists,dist};
}

void printDistancesFromSt(pair<bool,vector<int>> res, int st){
	if(res.first) cout << "Distances can not be computed, negative len cycle exists" << endl;
	else{
		vector<int> dist = res.second;
		for(int i = 0 ; i < dist.size() ; i++) cout << "dist from " << st << " to node " << i << " : " << dist[i] << endl;
	}
}

int main(int argc, char* argv[]){
	char* inpFile;
	if(argc == 2) inpFile = argv[1];
	else inpFile = "weightedEdges.txt" ;
	freopen(inpFile, "r", stdin);
	vector<tuple<int,int,int>> weightedEdges;
	int a,b,w,n ;
	cin >> n ;
	while((cin >> a >> b >> w )) weightedEdges.push_back({a,b,w});
	int st = 0;
	pair<bool,vector<int>> result  = bellmanFord(weightedEdges, n, st);
	printDistancesFromSt(result, st);
}
