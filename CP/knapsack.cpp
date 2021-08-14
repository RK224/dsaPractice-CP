#include <bits/stdc++.h>

using namespace std;

void getSubsetsHelp(vector<int> &s, vector<int>::iterator itr,vector<vector<int>> &subsets,vector<int> current_set = vector<int>()){
	if(itr == s.end()){
		subsets.push_back(current_set);
	}else{
		int val = *itr;
		itr++;
		getSubsetsHelp(s,itr,subsets,current_set);
		current_set.push_back(val);
		getSubsetsHelp(s,itr,subsets,current_set);
	}
}

vector<vector<int>> getSubsets(vector<int> s){
	vector<vector<int>> subsets;
	getSubsetsHelp(s,s.begin(),subsets);
	return subsets;
}

void printSet(vector<int> vi){
	cout << "( ";
	for(int i : vi) cout << i << " " ;
	cout << ")" << endl;
}
void printSubsets(vector<vector<int>> subsets){
	for(vector<int> vi : subsets) printSet(vi);
}

set<int> possibleSums(vector<int> vi){
	set<int> sums;
	vector<vector<int>> subsets = getSubsets(vi);
	int sum;
	for(vector<int> v : subsets){
		sum = 0;
		for(int i : v) sum+=i;
		sums.insert(sum);
	}
	return sums;
}

int knapsack0_1(vector<int> val, vector<int> weights, int W){
	vector<vector<int>> sum(W+1,vector<int>(weights.size() + 1, 0));
	for(int i = 1 ; i < sum.size() ; i++){
		for(int j = 1 ; j < sum[0].size() ; j++){
			int remWeight = i - weights[j-1];
			if( remWeight >= 0){
				sum[i][j] = max(val[j-1] + sum[remWeight][j-1], sum[i][j-1]);
			}else sum[i][j] = sum[i][j-1];
		}
	}
	return sum[W][weights.size()];
}

//RECONSTRUCT SOLUTION
int knapsack0_1LM(vector<int> val, vector<int> weights, int W){
	vector<int> sum(W+1,0);
	for(int i = 0; i < weights.size() ; i++){
		for(int w = W ; w >= 0 ; w--){
			if(w >= weights[i]) sum[w] = max(sum[w], val[i] + sum[w - weights[i]]);
		}
	}
	return sum[W];
}

int main(void){
	vector<int> vi = {1,3,3,5};
	vector<vector<int>> subsets = getSubsets(vi);
	printSubsets(subsets);
	possibleSums(vi);
	vector<int> val = {100,60,120}, weights = {20,10,30};
	int W = 50;
	cout << knapsack0_1LM(val, weights, W) << endl;
}
