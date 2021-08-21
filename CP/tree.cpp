#include <bits/stdc++.h>

using namespace std;

struct node{
	struct node *parent;
	int value;
	vector<struct node*> children;
};

typedef struct node Node;
typedef Node* pNode;

pNode getNode(int value){
	pNode pN = new Node;
	pN->parent = NULL;
	pN->value = value;
	return pN;
}

void addChild(pNode parent, pNode child){
	child->parent = parent;
	(parent->children).push_back(child);
}

void printNode(pNode pN){
	cout << "addr " << pN << " node( parent = " << pN->parent << " ,value = " << pN->value << " ) ";
}

void dfs(pNode root){
	printNode(root);
	cout << endl;
	for(pNode child : root->children) dfs(child);
}

int numberOfNodesInSubtree(pNode root){
	int nNodes = 1;
	for(pNode child : root->children) nNodes += numberOfNodesInSubtree(child);
	return nNodes;
}

int pathDistSameSubtree(pNode st, pNode dest){
	if(st == dest) return 0;
	else{
		int pathLen = INT_MAX;
		for(pNode child : st->children) pathLen = min(pathLen, pathDistSameSubtree(child,dest));
		if(pathLen == INT_MAX) return pathLen;
		else return pathLen + 1;
	}
}

int pathDist(pNode n1, pNode n2, pNode root){
	int pathLen = min(pathDistSameSubtree(n1,n2), pathDistSameSubtree(n2,n1));
	if(pathLen == INT_MAX){
		int root_n1 = pathDistSameSubtree(root, n1);
		int root_n2 = pathDistSameSubtree(root, n2);
		if(root_n1 != INT_MAX && root_n2 != INT_MAX) return root_n1 + root_n2;
		else return INT_MAX;
	}else return pathLen;
}

pair<int,int> max_two(int a, int b, int c){
	vector<int> v = {a,b,c};
	sort(v.begin(),v.end());
	return { v[1], v[2] };
}

pair<int,int> diameterHelp(pNode root){
	int p1, p2, d;
	p1 = p2 = d = 0;
	for(pNode child : root->children){
		pair<int,int> res = diameterHelp(child);
		d = max(d, res.second);
		pair<int,int> p1_p2 = max_two(p1,p2, res.first);
		p1 = p1_p2.first; p2 = p1_p2.second;
	}
	int n_c = (root->children).size();
	int d_root = p1 + p2 + min(2, n_c);
	int d_max = max(d_root, d);
	int p_max = min(1, n_c) + max(p1,p2);
	return {p_max,d_max};

}

int diameter(pNode root){
	pair<int,int> res = diameterHelp(root);
	return res.second;
}

int main(void){
	pNode n1,n2,n3,n4,n5,n6,n7,n8;
	n1 = getNode(1); n2 = getNode(2); n3 = getNode(3); n4 = getNode(4);
	n5 = getNode(5); n6 = getNode(6); n7 = getNode(7); n8 = getNode(8);
	addChild(n1, n2);
	addChild(n1, n3);
	addChild(n1, n4);
	addChild(n2, n5);
	addChild(n2, n6);
	addChild(n6, n8);
	addChild(n4, n7);
	dfs(n1);
	cout << numberOfNodesInSubtree(n1) << endl;
	cout << numberOfNodesInSubtree(n2) << endl;
	cout << numberOfNodesInSubtree(n4) << endl;
	cout << "bn n1 and n8" << endl;
	cout << pathDist(n1,n8,n1) << endl;
	cout << "bn n8 and n2" << endl;
	cout << pathDist(n8,n2,n1) << endl;
	cout << "bn n8 and n7" << endl;
	cout << pathDist(n8,n7,n1) << endl;
	cout << "diameter of tree rooted at " << n1 << " " << diameter(n1) << endl;
	cout << "diameter of tree rooted at " << n2 << " " << diameter(n2) << endl;
}

