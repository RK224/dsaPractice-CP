#include <bits/stdc++.h>
using namespace std; 

int binarySearch(vector<int> vi, int v, int st, int en){
	if(st >  en){
		return -1;
	} else {
		int mid = st + (en - st)/2 ;
		int midVal = vi[mid];
		if(v < midVal) return binarySearch(vi,v,st,mid-1);
		else if( v == midVal) return mid ;
		else return binarySearch(vi,v,mid+1,en);
	}
}

int binarySearchItr(vector<int> vi, int v, int st, int en){
	int l = st, r = en;
	while(l <= r){
		int mid = l + (r-l)/2;
		int midVal = vi[mid];
		if(v < midVal) r = mid-1;
		else if ( v == midVal) return mid ;
		else l = mid+1 ;
	}
	return -1 ;
}


int lowerBound(vector<int> vi, int v, int st, int en){
	int lb = st - 1 , n = en - st + 1 ;
	for(int b = n ; b >= 1 ; b/=2){
		while(lb + b <= en && vi[lb + b] < v) lb+=b;
	}
	return lb + 1;
}

int upperBound(vector<int> vi, int v, int st, int en ){
	int ub = en + 1, n = en - st + 1;
	for(int b = n ; b >= 1; b/=2){
		while( ub - b >= st && vi[ub - b] > v ) ub -=b;
	}
	return ub ;
}

int binarySearchFirstOcc(vector<int> vi, int v, int st, int en){
	int idx = lowerBound(vi,v,st,en);
	if(idx <= en && vi[idx] == v) return idx ;
	else return -1;
}

int main(void){
	freopen("input.txt", "r", stdin);
	vector<int> vi;
	int x;
	while ( cin >> x ) {
		vi.push_back(x);
	}
	sort(vi.begin(), vi.end());
	for(int v : vi ) cout << v << " " ;
	cout << endl;

	srand(time(nullptr));
	int randIdx = rand() % vi.size();
	int v1 = vi[randIdx];
	int en = vi.size() -1;
	int idx = binarySearch(vi, v1, 0, en);
	cout << "Val = " << v1 << " found at idx = " << idx << endl;
	idx = binarySearchItr(vi, v1, 0, en);
	cout << "binarySearch Itr :: Val = " << v1 << " found at idx = " << idx << endl;

	idx = lowerBound(vi,v1 ,0,en);
	cout << "lowerBound Itr :: Val = " << v1 << " found at idx = " << idx << endl;

	idx = upperBound(vi,v1 ,0,en);
	cout << "upperBound Itr :: Val = " << v1 << " found at idx = " << idx << endl;

	idx = lowerBound(vi,v1,0,en);
	if(vi[idx] == v1){
		cout << "binarySearch Itr :: Val = " << v1 << " found at idx = " << idx << endl;
	}

	idx = binarySearchFirstOcc(vi,v1,0,en);
	cout << "binarySearchFirstOcc Itr :: Val = " << v1 << " found at idx = " << idx << endl;

	idx = lower_bound(vi.begin(),vi.end(),v1) - vi.begin();
	cout << "lowerBound system Itr :: Val = " << v1 << " found at idx = " << idx << endl;

	idx = upper_bound(vi.begin(),vi.end(),v1) - vi.begin();
	cout << "upperBound system Itr :: Val = " << v1 << " found at idx = " << idx << endl;
	return 0;
}
