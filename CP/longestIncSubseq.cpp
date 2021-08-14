#include <bits/stdc++.h>
using namespace std;

vector<int> longestIncreasingSubseqLen(vector<int> vi){
	vector<int> maxLen(vi.size(),1);
	vector<int> prevEleIdx(vi.size(),-1);
	int maxLenIdx =  0;
	for(int i = 0; i < vi.size(); i++){
		for(int j = 0 ; j < i ; j++){
			if(vi[j] < vi[i] && maxLen[j] + 1 > maxLen[i]){
				prevEleIdx[i] = j;
				maxLen[i] = maxLen[j] + 1;
			}
		}

		if(maxLen[i] > maxLen[maxLenIdx]) maxLenIdx = i;
	}
	vector<int> largestIncSubseq;
	for(int i = maxLenIdx; i >= 0; ){
		largestIncSubseq.push_back(vi[i]);
		i = prevEleIdx[i];
	}
	reverse(largestIncSubseq.begin(),largestIncSubseq.end());
	return largestIncSubseq;
}

vector<int> longestIncSubseqFast(vector<int> vi){
	vector<int> lastEleSubseq(vi.size()+1, INT_MAX), prevIdx(vi.size() + 1,-1), prevEleIdx(vi.size(),-1);
	lastEleSubseq[0] = INT_MIN;
	for(int i = 0 ; i < vi.size() ; i++){
		int idx = lower_bound(lastEleSubseq.begin(), lastEleSubseq.end(), vi[i]) - lastEleSubseq.begin();
		if(idx < vi.size()){
			lastEleSubseq[idx] = vi[i];
			prevIdx[idx+1] = i;
			prevEleIdx[i] = prevIdx[idx];
		}
	}

	int longestIncSubseqLen;
	for(int i = 0 ; i <  vi.size() - 1 ; i++){
		if(lastEleSubseq[i+1] == INT_MAX){
			longestIncSubseqLen = i;
			break;
		}
	}

	vector<int> longestIncSubseq;
	for(int i = prevIdx[longestIncSubseqLen + 1]; i >= 0; ){
		longestIncSubseq.push_back(vi[i]);
		i = prevEleIdx[i];
	}
	reverse(longestIncSubseq.begin(), longestIncSubseq.end());
	return longestIncSubseq;
}

int main(void){
	vector<int> vi = {6,2,5,1,7,4,8,3}, largestIncSubseq = longestIncreasingSubseqLen(vi);
	cout << largestIncSubseq.size() << endl;
	for(int i : largestIncSubseq) cout << i << " " ;
	cout << endl;
	largestIncSubseq = longestIncSubseqFast(vi);
}

