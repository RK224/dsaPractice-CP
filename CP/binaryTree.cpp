#include <bits/stdc++.h>

using namespace std;

struct node {
	int value;
	struct node *left, *right;
};

typedef struct node* Node;

void printNode(Node n){
	cout <<  n << " Node( value = " << n->value << " , left = " << n->left << " , right = " << n->right <<  " )" << endl;
}

Node getNode(int value, Node leftSubtree = NULL, Node rightSubtree = NULL){
	Node n = new struct node;
	n->value = value;
	n->left = leftSubtree;
	n->right = rightSubtree;
	return n;
}

void preOrder(Node root){
	if(root != NULL){
		printNode(root);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder(Node root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printNode(root);
	}
}

void inOrder(Node root){
	if(root != NULL){
		inOrder(root->left);
		printNode(root);
		inOrder(root->right);
	}
}

int main(void){
	Node n1, n2, n3, n4, n5, n6, n7;
	n7 = getNode(7);
	n6 = getNode(6);
	n5 = getNode(5,n6);
	n3 = getNode(3,NULL,n7);
	n4 = getNode(4);
	n2 = getNode(2, n4, n5);
	n1 = getNode(1, n2, n3);
	cout << "Preorder traversal" << endl;
	preOrder(n1);
	cout << "Postorder traversal" << endl;
	postOrder(n1);
	cout << "Inorder traversal" << endl;
	inOrder(n1);
	return 0;
}
