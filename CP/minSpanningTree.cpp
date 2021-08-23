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
	(pUF->links).reserve(nNodes);
	(pUF->size).reserve(nNodes);
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
	for(int i = 0 ; i < nNodes; i++) cout << i << "-->" << pUF->links[i] << " " ;
	cout << endl << "SIZE : ";
	for(int i = 0 ; i < nNodes; i++) cout << i << "-->" << pUF->size[i] << " " ;
	cout << endl;
}


int main(void){
	vector<tuple<int,int,int>> wEdges;
	freopen("weightedEdges.txt", "r", stdin);
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
}
