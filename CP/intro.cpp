#include <bits/stdc++.h>
using namespace std;

#define REP(a,b) for(int i = a; i < b; i++) 

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int arr[5];
	cout << "Input 5 numbers, we will square them " << endl;
	REP(0,5){
		cin >> arr[i];
	}
	cout << "Enter a line, will print the whole line back" << endl;
	string s;
	cin.ignore();
	getline(cin,s);
	cout << s << endl;
	for ( int a : arr ) {
		cout << "Square of " << a << " is : " << a*a << endl;
	}

}
