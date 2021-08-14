#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

void log(int sum, vector<int> coins, unordered_set<int> skipIdx = unordered_set<int>()){
	cout << "Sum : " << sum << " with coins " ;
	for(int i = 0 ; i < coins.size() && !skipIdx.count(i); i++) cout << coins[i] << " " ;
	cout << endl;
}

int minCoinsHelp(int sum, vector<int> coins,unordered_set<int> skipIdx){
	if(sum == 0) {
		return 0;
	}else if(skipIdx.size() == coins.size()){
		return INT_MAX;
	}else{
		int minCoins = INT_MAX;
		for(int i = 0 ; i < coins.size(); i++){
			if(skipIdx.count(i)) continue;
			int coin, noCoin, remainingSum, noCoins ;
			coin = coins[i], noCoin = sum/coin, remainingSum = sum - noCoin * coin;
			skipIdx.insert(i);
			int remainingWithCoin = minCoinsHelp(remainingSum, coins,skipIdx);
			int remainingWithoutCoin = minCoinsHelp(sum, coins,skipIdx);
			if(remainingWithCoin == INT_MAX) {
				noCoins = remainingWithoutCoin ;
			}else{
			        noCoins = min(noCoin + remainingWithCoin, remainingWithoutCoin);
			}
			minCoins = min(noCoins, minCoins);
			skipIdx.erase(i);
		}
		return minCoins;
	}
}

int minCoins(int sum, vector<int> coins){
	unordered_set<int> skipIdx;
	return minCoinsHelp(sum,coins,skipIdx);
}

int minCoinsDP(int sum, vector<int> coins, map<int,int> &coinsCount, map<int,int> &firstCoins){
	if(sum < 0) return INT_MAX;
	else if( sum == 0 ){
		 firstCoins[sum] = 0;
		 return 0;
	}else{
		if(coinsCount.count(sum)){
			 return coinsCount[sum];
		}else{
			int minCoins = INT_MAX, firstCoin = 0;
			for(int coin : coins){
				int no = sum/coin, remainingSum = sum - no*coin;
				if(no != 0){
					int sum_coin = minCoinsDP(remainingSum, coins, coinsCount,firstCoins);
					if( sum_coin != INT_MAX) {
						int coinsWithC = no + sum_coin;
						if(coinsWithC < minCoins){
							minCoins =  coinsWithC;
							firstCoin = coin;
						}
					}
				}
			}
			coinsCount[sum] = minCoins;
			firstCoins[sum] = firstCoin;
			return minCoins;
		}
	}
}

void printFirstCoins(map<int,int> firstCoins, int sum){
	if(firstCoins.size() == 0) return;
	int currSum = sum,firstCoin = firstCoins[currSum];
	while(currSum > 0){
		if(firstCoins.count(currSum)) {
			firstCoin = firstCoins[currSum];
			cout << firstCoin << " " ;
		}
		currSum -= firstCoin;
	}
	cout << endl;
	return;
}

int minCoinsDPItr(int sum, vector<int> coins, map<int,int> &coinsCount, map<int,int> &firstCoins){
	coinsCount[0] = 0;
	for(int curr_sum = 1 ; curr_sum <= sum ; curr_sum++){
		int minCoins = INT_MAX, firstCoin = 0;
		for(int coin : coins){
			int noCoins, no = curr_sum/coin;
			if(no != 0 && curr_sum - no*coin >= 0){
				noCoins = no + coinsCount[curr_sum - no*coin];
				if(noCoins < minCoins){
					minCoins = noCoins;
					firstCoin = coin;
				}
			}
		}
		coinsCount[curr_sum] = minCoins;
		firstCoins[curr_sum] = firstCoin;
	}
	return coinsCount[sum];
}

int minCoinsDP(int sum, vector<int> coins, int (*minCoinsDPHelp)(int,vector<int>,map<int,int> &,map<int,int> &) = minCoinsDP){
	map<int,int> coinsCount,firstCoins;
	int minCoins = minCoinsDPHelp(sum,coins,coinsCount,firstCoins);
	printFirstCoins(firstCoins,sum);
	return minCoins;
}

int main(void){
	vector<int> coins = {1,2,3,5,7,11,13,17,21};
	high_resolution_clock::time_point start, stop;

	int sum = 51;
	int count;
	start = high_resolution_clock::now();
	count = minCoinsDP(sum,coins,minCoinsDPItr);
	stop  = high_resolution_clock::now();
	auto duration1 = duration_cast<nanoseconds>(stop-start).count();
	cout << "computed in " << duration1 << "ns. count = " << count << endl;

	start = high_resolution_clock::now();
	count = minCoinsDP(sum,coins);
	stop  = high_resolution_clock::now();
	duration1 = duration_cast<nanoseconds>(stop-start).count();
	cout << "computed in " << duration1 << "ns. count = " << count << endl;
}
