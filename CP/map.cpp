#include <bits/stdc++.h>
using namespace std;

int main(void){

	map<string,int> m;
	m["rk"] = 10;
	m["dd"] = 10;
	
	cout << "value of dd " << m["dd"] << endl;
	cout << m["nd"] << endl;
	cout << m.count("nd") << endl;
	cout << m.count("ad") << endl;

	m["dd"] = 20;
	cout << "value of dd " << m["dd"] << endl;

	auto itr = m.insert(make_pair("dd",30));
	if(itr.second) cout << "Inserted" << endl;
	else{
		cout << "Not inserted" << endl;
		cout << "Existing value " << itr.first->first << " "  << itr.first->second << endl;
	}
	cout << "value of dd " << m["dd"] << endl;
	return 0;

}
