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
		cout << endl;
	}
}

bool leastDistanceNode(pair<int,int> n1, pair<int,int> n2){
	int w1, w2;
	w1 = n1.second; w2 = n2.second;
	return w1 > w2;
}

vector<int> djikstra(vector<vector<pair<int,int>>> weightedAdjList, int n, int st){
	priority_queue<pair<int,int>, vector<pair<int,int>> , bool (*)(pair<int,int>, pair<int,int>)> pq(leastDistanceNode);
	vector<int> visited(n,0);
	vector<int> distance(n, INT_MAX);
	distance[st] = 0;
	for(int i = 0 ; i < n ; i++) pq.push({i, distance[i]});
	while(!pq.empty()){
		pair<int,int> node = pq.top(); pq.pop();
		int v = node.first;
		if(visited[v]) continue;
		visited[v] = 1;
		int v2, w;
		for(pair<int,int> edge : weightedAdjList[v]){
			v2 = edge.first; w = edge.second;
			distance[v2] = min(distance[v2], distance[v] + w);
			pq.push({v2, distance[v2]});
		}
	}
	return distance;
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

	vector<vector<pair<int,int>>> weightedAdjList(n, vector<pair<int,int>>());
	for(tuple<int,int,int> wEdge : weightedEdges){
		a = get<0>(wEdge); b = get<1>(wEdge); w = get<2>(wEdge);
		weightedAdjList[a].push_back({b,w});
	}

	vector<int> distances = djikstra(weightedAdjList, n, st);
	printDistancesFromSt({false, distances}, st);
}
