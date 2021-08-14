#include <bits/stdc++.h>

using namespace std;

struct node {
	int data ;
	struct node* next;
};

typedef struct node* Node;


struct linkedList{
	Node start;
	Node end;
	int size;
};

typedef struct linkedList lList;

void newLinkedList(lList &linkedList){
	linkedList.start= NULL, linkedList.end = NULL;
	linkedList.size = 0;
}

void printNode(Node n){
	cout << n << " Node( data = " << n->data << ", next = " << n->next << " )" << endl;
}

void printLinkedList(lList linkedList){
	cout << "LinkedList with start " << linkedList.start << " end " << linkedList.end << " size " << linkedList.size << endl;
	Node itr = linkedList.start;
	while(itr != linkedList.end){
		printNode(itr);
		itr = itr->next;
	}
}

void insertElement(lList &linkedList, int ele){
	Node n = new struct node;
	n->data = ele;
	if(linkedList.size == 0){
		n->next = linkedList.end;
	}else{
		n->next = linkedList.start;
	}
	linkedList.size++;
	linkedList.start = n;
	return;
}


pair<Node,Node> findElement(lList linkedList, int ele){
	Node itr = linkedList.start, prev_itr = NULL;
	while( itr != linkedList.end && itr->data != ele) {
		prev_itr = itr;
		itr = itr->next;
	}
	return make_pair(prev_itr, itr);
}

void removeElement(lList &linkedList, int ele){
	pair<Node,Node> prev_curr = findElement(linkedList,ele);
	Node prev = prev_curr.first, curr = prev_curr.second;
	if( curr != linkedList.end ){
		if( curr == linkedList.start ){
			linkedList.start = curr->next;
		}else{
			prev->next = curr->next;
		}
		linkedList.size--;
	}
	return ;
}

void reverse(lList &linkedList){
	Node itr_prev = linkedList.end , itr = linkedList.start;
	Node itr_nxt;
	while(itr != linkedList.end){
		itr_nxt = itr->next;
		itr->next = itr_prev;
		itr_prev = itr;
		itr = itr_nxt;
	}
	linkedList.start = itr_prev;
}

bool checkCycle1(lList linkedList){
	unordered_set<Node> nodeSet;
	Node itr = linkedList.start;
	while(itr != linkedList.end){
		if(nodeSet.count(itr)) return true;
		else {
			nodeSet.insert(itr);
			itr = itr->next;
		}
	}
	return false;
}

bool checkCycleFloyd(lList linkedList){
	Node slow = linkedList.start, fast = linkedList.start;
	bool met = false;
	while(fast != linkedList.end && fast->next != linkedList.end){
		slow = slow->next;
		fast = fast->next->next;
		if( slow == fast ) {
			met = true; 
			break;
		}
	}
	if(met){
		slow = linkedList.start;
		int distFromStart = 0;
		while(slow != fast){
			slow = slow->next; fast = fast->next;
			distFromStart++;
		}
		cout << "Cycle starts at " ;
		printNode(slow);
		int lenCycle = linkedList.size - distFromStart;
		cout << "Length of the cycle : " << lenCycle << endl;
	}
	return met;
}

int main(void){
	lList lnkList ;
	newLinkedList(lnkList);
	printLinkedList(lnkList);
	insertElement(lnkList,1);
	printLinkedList(lnkList);
	insertElement(lnkList,2);
	insertElement(lnkList,3);
	printLinkedList(lnkList);
	reverse(lnkList);
	printLinkedList(lnkList);
	pair<Node,Node> prev_curr = findElement(lnkList,3);
	Node prev = prev_curr.first, n = prev_curr.second;
	if(n != lnkList.end) {
		cout << "Found Element: " ;
		printNode(n);
	}else cout << "element not found" << endl;

	removeElement(lnkList,2);
	printLinkedList(lnkList);
	insertElement(lnkList,4);
	insertElement(lnkList,7);
	insertElement(lnkList,8);
	printLinkedList(lnkList);
	lnkList.start->next->next->next->next->next = lnkList.start->next->next;
	bool isCycle = checkCycleFloyd(lnkList);
	cout << "Is cycle " << isCycle << endl;
//	printLinkedList(lnkList);
	return 0;
}
