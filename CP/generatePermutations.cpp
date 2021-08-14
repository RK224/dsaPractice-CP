#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

void combine(int val, vector<vector<int>> perms , vector<vector<int>> &permutations){
	if(perms.empty()){
		vector<int> perm ; perm.push_back(val) ; permutations.push_back(perm);
	} else{
		for(vector<int> perm : perms){
			perm.push_back(val);
			permutations.push_back(perm);
		}
	}
}

vector<vector<int>> generatePermutationsHelper(vector<int> v, unordered_set<int> &skipIdx){
	vector<vector<int>> permutations;
	if(skipIdx.size() == v.size()){
		return permutations;
	}else{
		for(int i = 0; i < v.size(); i++){
			if(skipIdx.count(i)) continue;
			skipIdx.insert(i);
			vector<vector<int>> perms = generatePermutationsHelper(v,skipIdx);
			skipIdx.erase(i);
			combine(v[i],perms, permutations);
		}
		return permutations;
	}
}

vector<vector<int>> generatePermImp(vector<int> v){
	vector<vector<int>> permutations;
	unordered_set<int> skipIdx;
	permutations = generatePermutationsHelper(v, skipIdx);
	return permutations;
}

vector<vector<int>> generatePermutations(vector<int> v){
	vector<vector<int>> permutations ;
	if( v.empty() ) {
		return permutations;
	}else{
		for(int i = 0 ;  i < v.size() ; i++){
			vector<int> v_copy(v);
			v_copy.erase(v_copy.begin() + i);
			vector<vector<int>> perm_vcopy = generatePermutations(v_copy);
			combine(v[i],perm_vcopy,permutations);
		}
		return permutations;
	}
}

void printPermutation(vector<int> permutation){
	cout << "( ";
	for(int val : permutation) cout << val << " ";
	cout << ")" << endl;
}

void printPermutations(vector<vector<int>> permutations){
	cout << "Number of permutations : " << permutations.size() << endl;
	for(vector<int> perm : permutations) printPermutation(perm);
}

vector<vector<int>> generatePermutationsLibImpl(vector<int> v){
	vector<vector<int>> permutations;
	sort(v.begin(),v.end());
	do{
		permutations.push_back(v);
	}while(next_permutation(v.begin(),v.end()));
	return permutations;
}

void profileAndPrintResult(vector<vector<int>> (*generatePermutations)(vector<int>), vector<int> v){
	auto start = high_resolution_clock::now();
	vector<vector<int>> perm = generatePermutations(v);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Computing permutations took " << duration << " nanoseconds" << endl;
	printPermutations(perm);
	return;
}

int main(void){
	vector<int> v = {3,1,2,0,8,7};
	cout << "At home impl Imp" ;
	profileAndPrintResult(generatePermImp,v);
	cout << "At home impl " ;
	profileAndPrintResult(generatePermutations,v);
	cout << "Library impl " ;
	profileAndPrintResult(generatePermutationsLibImpl,v);
}


