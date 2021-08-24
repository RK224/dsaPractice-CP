#include <bits/stdc++.h>

using namespace std;

struct unionFind{
	int nNodes;
	vector<int> links, size;
};

typedef struct unionFind unionFind;
typedef unionFind* pUnionFind;

pUnionFind getUnionFind(int nNodes){
	pUnionFind pUF = new unionFind;
	pUF->nNodes = nNodes;
	pUF->links = vector<int>(nNodes,0);
	pUF->size = vector<int>(nNodes,1);
	return pUF;
}

void initializeUnionFind(pUnionFind pUF){
	for(int i = 0 ; i < pUF->nNodes ; i++){
		pUF->links[i] = i;
		pUF->size[i] = 1;
	}
}

int findRepr(int n1, pUnionFind pUF){
	int repr = n1;
	while(repr != (pUF->links)[repr]) repr = (pUF->links)[repr];
	return repr;
}

bool isSameComponent(int n1, int n2, pUnionFind pUF){
	return findRepr(n1,pUF) == findRepr(n2,pUF);
}

void combineComponents(int n1, int n2, pUnionFind pUF){
	int repr_n1, repr_n2;
	repr_n1 = findRepr(n1, pUF);
	repr_n2 = findRepr(n2, pUF);
	if(pUF->size[repr_n1] <  pUF->size[repr_n2]){
		pUF->size[repr_n2] += pUF->size[repr_n1];
		pUF->links[repr_n1] = repr_n2;
	}else{
		pUF->size[repr_n1] += pUF->size[repr_n2];
		pUF->links[repr_n2] = repr_n1;
	}
}

void printUnionFind(pUnionFind pUF){
	int nNodes = pUF->nNodes;
	cout << "LINKS : ";
	for(int i = 0 ; i < nNodes; i++) cout << i << "-->" << pUF->links[i] << "\t" ;
	cout << endl << "SIZE : ";
	for(int i = 0 ; i < nNodes; i++) cout << i << "-->" << pUF->size[i] << "\t" ;
	cout << endl;
}

vector<tuple<int,int,int>> Kruskal(vector<tuple<int,int,int>> wEdges, int nNodes){
	priority_queue<tuple<int,int,int>> pq;
	vector<tuple<int,int,int>> minSpanningTree;
	pUnionFind pUF = getUnionFind(nNodes);
	initializeUnionFind(pUF);

	int a,b, negW;
	for(tuple<int,int,int> wEdge : wEdges){
		a = get<0>(wEdge); b = get<1>(wEdge); negW = -1 * get<2>(wEdge);
		pq.push({negW,a,b});
	}

	while(!pq.empty()){
		tuple<int,int,int> wEdge = pq.top(); pq.pop();
		negW = get<0>(wEdge); a = get<1>(wEdge); b = get<2>(wEdge);
		if(!isSameComponent(a,b,pUF)) {
			minSpanningTree.push_back({a, b, -1*negW});
			combineComponents(a,b,pUF);
		}
	}

	return minSpanningTree;
}

void printSpanningTree(vector<tuple<int,int,int>> spanningTree){
	int totalWeight = 0;
	int w;
	for(tuple<int,int,int> edge : spanningTree){
		w = get<2>(edge); totalWeight += w;
		cout << get<0>(edge) << "-->" << get<1>(edge) << " " << w << endl;
	}
	cout << "Total weight " << totalWeight << endl;
}

void addNodeToMst(int v, int exclude, vector<pair<int,int>> adjNodes, vector<bool> &inMst, priority_queue<tuple<int,int,int>> &pq){
	inMst[v] = true;
	int u,w;
	for(pair<int,int> edge : adjNodes){
		u = edge.first; w = edge.second;
		if(u != exclude) pq.push({-1*w, v, u});
	}
}

vector<tuple<int,int,int>> Prim(vector<vector<pair<int,int>>> adjList, int n){
	vector<tuple<int,int,int>> mst;
	priority_queue<tuple<int,int,int>> pq;
	vector<bool> inMst(n, false);
	addNodeToMst(0, -1, adjList[0], inMst, pq);
	int u,v,w;
	while(!pq.empty()){
		tuple<int,int,int> edge = pq.top(); pq.pop();
		w = -1* get<0>(edge); v = get<1>(edge); u = get<2>(edge);
		if(!inMst[u]){
			mst.push_back({v,u,w});
			addNodeToMst(u, v, adjList[u], inMst, pq);
		}
	}
	return mst;
}

int main(int argc, char* argv[]){
	vector<tuple<int,int,int>> wEdges;
	char* filename;

	if(argc == 2) filename = argv[1];
	else filename = "weightedEdges.txt";

	freopen(filename, "r", stdin);
	int a,b,w,n;
	cin >> n ;
	while( cin >> a >> b >> w ) wEdges.push_back({a,b,w});
	pUnionFind pUF = getUnionFind(n);
	initializeUnionFind(pUF);
	cout << "Repr for node 0 : " << findRepr(0,pUF) << endl;
	cout << "Repr for node 1 : " << findRepr(1,pUF) << endl;
	cout << "isSameComponent 0 and 1 : " << isSameComponent(0, 1, pUF) << endl;
	combineComponents(0,1,pUF);
	printUnionFind(pUF);
	cout << "isSameComponent 0 and 1 : " << isSameComponent(0, 1, pUF) << endl;
	printSpanningTree(Kruskal(wEdges, n));

	vector<vector<pair<int,int>>> adjList(n, vector<pair<int,int>>());
	for(tuple<int,int,int> edge : wEdges){
		int a,b,w;
		a = get<0>(edge); b = get<1>(edge); w = get<2>(edge);
		adjList[a].push_back({b,w});
		adjList[b].push_back({a,w});
	}
	printSpanningTree(Prim(adjList,n));
}
