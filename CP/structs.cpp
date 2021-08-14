#include <bits/stdc++.h>

using namespace std;

typedef struct Fraction{
	int numerator, denominator;
	bool operator<(const Fraction &f){
		if(denominator == f.denominator) return numerator < f.numerator;
		else {
			int myNumerator = numerator * f.denominator;
			int fNumerator = f.numerator* denominator;
			return myNumerator < fNumerator;
		}
	}

	string printFraction(){
		string fractionString = to_string(numerator) + "/" + to_string(denominator);
		return fractionString;
	}
} F;

bool dumbCompare(Fraction f1 , Fraction f2){
	return (f1.numerator + f1.denominator) < (f2.numerator + f2.denominator);
}

int main(void){
	F f1 = {1,2}, f2 = {3,4}, f3 = {1,1};
	f1.printFraction();
	f2.printFraction();
	f3.printFraction();
	cout << "f1 < f2 : " << (f1 < f2) << endl;
	cout << "f2 < f3 : " << (f2 < f3) << endl;
	cout << "f1 < f3 : " << (f3 < f1) << endl;
	vector<F> fractions = {f2,f1,f3};
	for(F fraction : fractions) cout << fraction.printFraction() << " " ;
	cout << endl;
	sort(fractions.begin(),fractions.end());
	for(F fraction : fractions) cout << fraction.printFraction() << " " ;
	cout << endl;
	sort(fractions.rbegin(),fractions.rend());
	for(F fraction : fractions) cout << fraction.printFraction() << " " ;
	cout << endl;
	sort(fractions.begin(),fractions.end(),dumbCompare);
	for(F fraction : fractions) cout << fraction.printFraction() << " " ;
	cout << endl;	
}
