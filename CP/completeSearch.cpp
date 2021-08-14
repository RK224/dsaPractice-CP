#include <bits/stdc++.h>

using namespace std;

void getSubsetsHelp(set<int> &s, set<int> current_set, set<int>::iterator itr, vector<set<int>> &subsets){
	if(itr == s.end()) {
		subsets.push_back(current_set);
		return;
	}else{
		int val = *itr;
		++itr;
		getSubsetsHelp(s, current_set, itr, subsets);
		current_set.insert(val);
		getSubsetsHelp(s, current_set, itr, subsets);
	}
}

void getSubsetsHelp(vector<int> &s, vector<int> current_set, vector<int>::iterator itr, vector<vector<int>> &subsets){
	if(itr == s.end()) {
		subsets.push_back(current_set);
		return;
	}else{
		int val = *itr;
		++itr;
		getSubsetsHelp(s, current_set, itr, subsets);
		current_set.push_back(val);
		getSubsetsHelp(s, current_set, itr, subsets);
	}
}

template <typename T> vector<T> getSubsets(T s){
	vector<T> subsets;
	T current_set;
	typename T::iterator itr = s.begin();
	getSubsetsHelp(s, current_set, itr , subsets);
	return subsets;
}

template <typename T> void printSet(T s){
	cout << "{ " ;
	for(int i : s) cout << i << " " ;
	cout << "}" << endl;
}

template <typename T> void printSubsets(vector<T> subsets){
	cout << "No of subsets : " << subsets.size() << endl;
	for(T s : subsets) printSet<T>(s);
}

vector<vector<int>> getSubsetsBitsetApproach(vector<int> v){
	vector<vector<int>> subsets;
	int n = v.size();
	vector<int> current_set;
	for(int i = 0 ; i < (1<<n) ; i++){
		for(int idx = 0 ; idx < n ; idx++){
			if(i & (1 << idx)){
				//i is the representation of the subset in bits,
				//if value at idx in the bit representation of i is set
				//include element at idx in the subset.
				current_set.push_back(v[idx]);
			}
		}
		subsets.push_back(current_set);
		current_set.clear();
	}
	return subsets;
}

vector<set<int>> getSubsetsBitsetApproach(set<int> s){
	vector<int> v(s.begin(), s.end());
	vector<vector<int>> subsetsVector = getSubsetsBitsetApproach(v);
	vector<set<int>> subsetsSet;
	for(vector<int> subset_v : subsetsVector) {
		set<int> subset(subset_v.begin(),subset_v.end());
		subsetsSet.push_back(subset); 
	}
	return subsetsSet;
}

int main(void){
	freopen("input.txt","r", stdin);
	set<int> s;
	vector<int> v;
	int x;
	while( cin >> x ){
		s.insert(x);
		v.push_back(x);
	}
	vector<vector<int>> subsets = getSubsets<vector<int>>(v);
	vector<set<int>> subsets_set = getSubsets<set<int>>(s);
	printSubsets<vector<int>>(subsets);
	printSubsets<set<int>>(subsets_set);
	cout << "Getting subsets using bit approach " << endl;
	printSubsets<vector<int>>(getSubsetsBitsetApproach(v));
	printSubsets<set<int>>(getSubsetsBitsetApproach(s));
}
