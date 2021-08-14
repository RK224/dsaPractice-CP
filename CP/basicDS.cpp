#include <bits/stdc++.h>
using namespace std;

int main(void){
	freopen("input.txt","r", stdin);
	stack<int> stk;
	multiset<int> multi_set;
	set<int> sSet;
	queue<int> q;
	priority_queue<int> pqD;
	priority_queue<int, vector<int>, greater<int>> pqI;
	bitset<16> bs(10);
	cout << "bitset " << bs << endl;
	for(int i = 0 ; i < 16 ; i++ ) cout << bs[i] << " " ;
	cout << endl;
	int x;
	while( cin >> x) {
		cout << x << endl;
		stk.push(x);
		q.push(x);
		pqD.push(x);
		pqI.push(x);
		multi_set.insert(x);
		sSet.insert(x);
	}

	cout << "Printing stack " << endl;
	while(!stk.empty()){
		cout << stk.top() << endl;
		stk.pop();
	}

	cout << "Printing queue " << endl;
	while(!q.empty()){
		cout << q.front() << endl;
		q.pop();
	}

	cout << "Printing pd decreasing" << endl;
	while(!pqD.empty()){
		cout << pqD.top() << endl;
		pqD.pop();
	}

	cout << "Printing pd increasing" << endl;
	while(!pqI.empty()){
		cout << pqI.top() << endl;
		pqI.pop();
	}

	cout << "Printing multi set increasing" << endl;
	for(int i : multi_set) cout << i << endl;

	cout << "Printing set increasing" << endl;
	for(int i : sSet) cout << i << endl;

	set<int,greater<int>> dSet(sSet.begin(), sSet.end());
	cout << "Printing set decreasing" << endl;
	for(int i : dSet) cout << i << endl;
	return 0;
}
