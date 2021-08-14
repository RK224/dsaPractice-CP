#include <bits/stdc++.h>

using namespace std;

vector<stack<int>> createPiles(vector<int> vi){
	vector<int> tops(vi.size(), INT_MAX);
	vector<stack<int>> piles(vi.size(), stack<int>());
	int lastIdx = 0;
	for(int i : vi){
		int idx = lower_bound(tops.begin(), tops.end(), i) - tops.begin();
		if(idx == vi.size()){
			//i is bigger that each element in tops
			piles[lastIdx].push(i);
			tops[lastIdx] = i;
			lastIdx++;
		}else{
			piles[idx].push(i);
			tops[idx] = i;
		}
	}
	return piles;
}

bool compareStacks(stack<int> s1, stack<int> s2){
	return s1.top() > s2.top();
}

vector<int> mergePiles(vector<stack<int>> piles){
	vector<int> sorted;
	priority_queue<stack<int>, vector<stack<int>>, bool (*)(stack<int>, stack<int>) > pq(compareStacks);
	for(stack<int> s: piles){
		if(!s.empty()) pq.push(s);
	}
	while(!pq.empty()){
		stack<int> s = pq.top(); 
		pq.pop();
		sorted.push_back(s.top()); 
		s.pop();
		if(!s.empty()){
			pq.push(s);
		}
	}
	return sorted;
}

vector<int> patienceSort(vector<int> vi){
	vector<stack<int>> piles = createPiles(vi);
	vector<int> sorted = mergePiles(piles);
	return sorted;
}


int main(void){
	vector<int> vi = {6,2,5,1,7,4,8,3};
	vector<int> sorted = patienceSort(vi);
	for(int i : sorted) cout << i << " " ;
	cout << endl;
}
