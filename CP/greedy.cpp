#include <bits/stdc++.h>

using namespace std;

pair<bool,vector<pair<int, int>>> greedyMinCoins(vector<int> coins, int sum){
	sort(coins.rbegin(),coins.rend());
	vector<pair<int,int>> count_coin;
	int sumVal = sum, no;
	for(int coin : coins){
		no = sumVal/coin;
		sumVal -= no * coin;
		if( no > 0 ) count_coin.push_back({no,coin});
	}

	return make_pair(sumVal == 0 , count_coin) ;
}

void printCountCoin(pair<bool,vector<pair<int,int>>> result, int sum){
	vector<pair<int,int>> count_coin = result.second;
	bool sumReached = result.first;
	if(!sumReached) {
		cout << "Cannot compute sum " << sum << " with the given coins" << endl;
		return;
	}
	cout << "Sum : " <<  sum << endl;
	for(pair<int,int> pair : count_coin)	cout << pair.first << " coins of value " << pair.second << endl;
}

bool endsEarly(pair<int,int> j1, pair<int,int> j2){
	return j1.second < j2.second;
}

vector<pair<int,int>> scheduleMaxJobs(int st, int en, vector<pair<int,int>> jobs){
	vector<pair<int,int>> schedule;
	sort(jobs.begin(), jobs.end(), endsEarly);
	int prev_end = st;
	for(pair<int,int> job : jobs){
		if( job.first >= st && job.second <= en && job.first >= prev_end ){
			schedule.push_back(job);
			prev_end = job.second;
		}
	}
	return schedule;
}

void printJobs(vector<pair<int,int>> jobs, int st, int en){
	cout << "Between st = " << st << " and en = " << en << endl;
	for(pair<int,int> job : jobs) cout << "start = " << job.first << " end = " << job.second << endl;
}

bool fasterTaskFirst(tuple<string,int,int> t1, tuple<string,int,int> t2){
	return get<1>(t1) < get<1>(t2);
}

pair<int,vector<tuple<string,int,int>>> scheduleTaskAndDeadlines(vector<tuple<string,int,int>> tasks){
	vector<tuple<string,int,int>> schedule ;
	sort(tasks.begin(), tasks.end(), fasterTaskFirst);
	int st = 0, en = 0, points = 0;
	for(tuple<string,int,int> task : tasks){
		string name = get<0>(task);
		int duration = get<1>(task), deadline = get<2>(task);
		st = en;
		en = st + duration;
		points += (deadline - en);
		schedule.push_back({name, st, en});
	}
	return {points,schedule};
}

void printTasks(vector<tuple<string,int,int>> tasks){
	for(tuple<string,int,int> task : tasks) cout << "Task " << get<0>(task) << " st = " << get<1>(task) << " en = " << get<2>(task) << endl;
}

int main(void){
	vector<int> coins = {1,3,4};
	vector<pair<int,int>> jobs = {{1,3},{2,5},{3,9},{6,8},{8,10}};
	vector<tuple<string,int,int>> tasks = {{"A",2,4},{"B",3,5},{"C",2,7},{"D",4,5}};
	int sum = 6, st = 0, en = 10;
	printCountCoin(greedyMinCoins(coins,sum),sum);
	printJobs(scheduleMaxJobs(st,en,jobs),st,en);
	pair<int,vector<tuple<string,int,int>>> result = scheduleTaskAndDeadlines(tasks);
	int points = result.first;
	tasks = result.second;
	cout << "Got " << points << " points" << endl;
	printTasks(tasks);
}
