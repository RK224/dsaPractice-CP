#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;



int main(void){
	freopen("input.txt","r",stdin);
	set<int> s;
	unordered_set<int> u_set;
	int x;
	while(cin >> x){
		s.insert(x);
		u_set.insert(x);
	}

	for(int i : s) cout << i << endl;
	int val = 19;
	cout << "Count of " << val << " is " << s.count(val) << endl; 

	auto start = high_resolution_clock::now();
	auto itr = s.find(val);
	if( itr == s.end()) cout << "Not found " << endl;
	else cout << "Found value " << *itr << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken to find: " << duration << endl;

	start = high_resolution_clock::now();
	auto itr2 = u_set.find(val);
	if( itr2 == u_set.end()) cout << "Not found " << endl;
	else cout << "Found value " << *itr2 << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken to find: " << duration << endl;

	start = high_resolution_clock::now();
	itr = s.find(65);
	if( itr == s.end()) cout << "Not found " << endl;
	else cout << "Found value " << *itr << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken to find: " << duration << endl;

	start = high_resolution_clock::now();
	itr2 = u_set.find(65);
	if( itr2 == u_set.end()) cout << "Not found " << endl;
	else cout << "Found value " << *itr2 << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken to find: " << duration << endl;

	int val1 = 17;
	start = high_resolution_clock::now();
	s.insert(itr,val1);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken : " << duration << endl;

	val1 = 200;
	start = high_resolution_clock::now();
	s.insert(itr,val1);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken : " << duration << endl;

	s.erase(17);
	val1 = 17;
	start = high_resolution_clock::now();
	s.insert(itr,val1);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken : " << duration << endl;

	val1 = 210;
	itr =  s.find(200);
	start = high_resolution_clock::now();
	s.insert(itr,val1);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Time taken : " << duration << endl;

	for(int i : s) cout << i << endl;

	cout << "Inserting unordered set" << endl;
	for(int i : u_set) cout << i << endl;
	return 0;
}
