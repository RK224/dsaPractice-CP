#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono ;

pair<int,pair<int,int>> maxSubarraySumON3(vector<int> vi);
pair<int,pair<int,int>> maxSubarraySumON2(vector<int> vi);
pair<int,pair<int,int>> maxSubarraySumON1(vector<int> vi);
void profileAndPrintResult(pair<int,pair<int,int>> (*maxSubarraySum)(vector<int>), vector<int> vi);


int main(void){
	freopen("input.txt","r",stdin);
	vector<int> vi;
	int input = 0;
	cout << "Input numbers to put in an array : " << endl;
	while( cin >> input) vi.push_back(input);
	for(int v : vi) cout << v << " " ;
	cout << endl;
	profileAndPrintResult(maxSubarraySumON3,vi);
	profileAndPrintResult(maxSubarraySumON2,vi);
	profileAndPrintResult(maxSubarraySumON1,vi);
	return 0;
}

void profileAndPrintResult(pair<int,pair<int,int>> (*maxSubarraySum)(vector<int>), vector<int> vi){
	auto start = high_resolution_clock::now();
	pair<int,pair<int,int>> result = maxSubarraySum(vi);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop-start);
	int sum = result.first, maxStart = result.second.first, maxEnd = result.second.second;
	cout << "max sum : " << sum << " start : " << maxStart << " end : " << maxEnd << " duration : " << duration.count() << endl;	
}

pair<int,pair<int,int>> maxSubarraySumON3(vector<int> vi){
	pair<int,pair<int,int>> result ;
	int length = vi.size();
	int maxStart=-1, maxEnd=-1, maxSum=0;
	for(int i = 0; i < length; i++){
		for(int j = i ; j < length ; j++){
			int sum=0;
			for(int r = i; r <= j; r++) sum+= vi.at(r);
			if( sum > maxSum ) {
				maxStart=i;maxEnd=j;maxSum=sum;
			}
		}
	}
	pair<int,int> indices = make_pair(maxStart,maxEnd);
	result = make_pair(maxSum,indices);
	return result;
}

pair<int,pair<int,int>> maxSubarraySumON2(vector<int> vi){
	pair <int, pair<int,int>> result ;
	int length = vi.size();
	int maxStart=-1,maxEnd=-1,maxSum=0;
	for( int i = 0 ; i < length ; i++){
		int sum = 0;
		for( int j = i ; j < length ; j++ ) {
			sum += vi.at(j);
			if(sum > maxSum){
				maxStart=i; maxEnd=j; maxSum=sum;
			}
		}
	}
	pair<int,int> indices = make_pair(maxStart,maxEnd);
	result = make_pair(maxSum,indices);
	return result;
}

pair<int,pair<int,int>> maxSubarraySumON1(vector<int> vi){
	vector<pair<pair<int,int>,int>> results ;
	results.push_back(make_pair(make_pair(0,0),vi.at(0)));
	int length = vi.size();
	for(int i = 1; i < length ; i++){
		pair<pair<int,int>,int> prev_res = results.at(i-1);
		int start_idx = prev_res.first.first, sum = prev_res.second;
		int current_val = vi.at(i);
		int sum_val = sum + current_val;
		if(sum_val > current_val){
			results.push_back(make_pair(make_pair(start_idx,i),sum_val));
		}else {
			results.push_back(make_pair(make_pair(i,i),current_val));
		}
	}
	int max_start = -1, max_end = -1, max_sum = 0;
	for(auto data : results ) {
		int start = data.first.first, end = data.first.second, sum = data.second;
		if(sum > max_sum){
			max_start = start, max_end = end , max_sum = sum;
		}
	}
	return make_pair(max_sum,make_pair(max_start,max_end));
}

