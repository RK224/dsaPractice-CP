#include <bits/stdc++.h>
using namespace std;


pair<int,vector<vector<int>>> editDistance(string s1, string s2){
	int n = s1.size() + 1, m = s2.size() + 1;
	vector<vector<int>> distanceMatrix(n, vector<int>(m,0));
	for(int i = 0; i < n; i++) distanceMatrix[i][0] = i;
	for(int i = 0; i < m; i++) distanceMatrix[0][i] = i;

	for(int r = 1; r < n ; r++){
		for(int c = 1; c < m; c++){
	 		distanceMatrix[r][c] =  min(1 + min(distanceMatrix[r-1][c], distanceMatrix[r][c-1]), distanceMatrix[r-1][c-1] + (s1[r-1] != s2[c-1]));
		}
	}
	return {distanceMatrix[n-1][m-1], distanceMatrix};

}

//RECREATE STEPS
vector<tuple<string,char,char>> transformSteps(string s1, string s2, vector<vector<int>> distanceMatrix){
	int r = distanceMatrix.size(), c = distanceMatrix[0].size();
	vector<tuple<string,char,char>> mods;
	while(r > 0 && c > 0){
		if(s1[r-1] == s2[c-1]){
			r--; c--;
		}else{
			int dlt = distanceMatrix[r-1][c], insert = distanceMatrix[r][c-1], modify = distanceMatrix[r-1][c-1];
			if( (dlt >= insert && insert >= modify) || (insert >= dlt && dlt >= modify) ){
				//modify is the smallest
				mods.push_back({"MODIFY", s1[r-1], s2[c-1]});
				r--; c--;
			}else if( (modify >= insert && insert >= dlt) || (insert >= modify && modify >= dlt)){
				//dlt is the smallest
				mods.push_back({"DELETE at idx " + to_string(c) , s1[r-1], '-'});
				r--;
			}else{
				mods.push_back({"INSERT at idx " + to_string(r) , s2[c-1], '-'});
				c--;
			}
		}
	}

	if(r == 0 && c != 0) {
		 while( c - 1 >= 0 ) {
			mods.push_back({"INSERT at idx 0",s2[c-1], '-'});
			c--;
		}
	}else if( r != 0 && c == 0) {
		 while( r - 1 >= 0 ) {
			mods.push_back({"DELETE at idx 0", s1[r-1], '-'});
			r--;
		}
	}

	if( r == 0 && c == 0) reverse(mods.begin(),mods.end());
	return mods;
}

void printTransformSteps(vector<tuple<string,char,char>> mods){
	for(tuple<string,char,char> step : mods){
		string op = get<0>(step);
		char from = get<1>(step), to = get<2>(step);
		if(op == "MODIFY") cout << op << " " << from << " --> " << to << endl;
		else cout << op << " " << from << endl;
	}
}

int main(void){
	string s1 = "lata", s2 = "satish";
	pair<int, vector<vector<int>>> result = editDistance(s1,s2);
	int distance = result.first;
	vector<vector<int>> distanceMatrix = result.second;
	cout << distance << endl;
	for(int i = 1 ; i < distanceMatrix.size(); i++){
		for(int j = 1; j < distanceMatrix[0].size() ; j++){
			cout << distanceMatrix[i][j] << " ";
		}
		cout << endl;
	}
	printTransformSteps(transformSteps(s1, s2, distanceMatrix));
}
