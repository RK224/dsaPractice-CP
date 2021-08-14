#include <bits/stdc++.h>

using namespace std;

void popQueue(stack<int> &s){
	stack<int> temp;
	while(!s.empty()){
		temp.push(s.top());
		s.pop();
	}
	temp.pop();
	while(!temp.empty()){
		s.push(temp.top());
		temp.pop();
	}
	return;
}

int frontQueue(stack<int> s){
	stack<int> temp;
	while(!s.empty()){
		temp.push(s.top());
		s.pop();
	}
	int front = temp.top();
	temp.pop();
	while(!temp.empty()){
		s.push(temp.top());
		temp.pop();
	}
	return front;
}

int main(void){
	freopen("input.txt", "r", stdin);
	queue<int>q;
	stack<int>s;
	int x;
	while(cin>>x){
		q.push(x);
		s.push(x);
	}

	cout << "Printing queue" << endl;
	while(!q.empty()){
		cout << q.front() << endl;
		q.pop();
	}

	cout << "Printing stack" << endl;

	while(!s.empty()){
		int top = frontQueue(s);
		cout << top << endl;
		popQueue(s);
	}
}
