#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void sort(vector<int> &vi, void (*helper)(vector<int> &, int, int));
int min_index(vector<int> vi, int st, int en);
void swap(vector<int> &vi, int idx1, int idx2);
void selectionSortHelp(vector<int> &vi, int st, int en); 
void selectionSortItr(vector<int> &vi, int st , int en);
void profileAndPrintResult(void (*sort)(vector<int> &, void (*helper)(vector<int>&, int,int)),void (*helper)(vector<int> &, int, int), vector<int> vi);
void bubbleSortHelper(vector<int> &vi, int st, int en);
void bubbleSortItr(vector<int> &vi, int st, int en);
void insertionSort(vector<int> &vi, int st, int en);
void insert(vector<int> &vi, int idx);
void insertionSortItr(vector<int> &vi, int st, int en);
void mergeSort(vector<int> &vi, int st, int en);
void mergeSortHelp(vector<int> &vi, int st, int en, vector<int> &v_copy);
void merge(vector<int> &vi, int st1, int en1, int st2, int en2, vector<int> v_copy);
void mergeSortItr(vector<int> &vi, int st, int en);
void quickSort(vector<int> &vi, int st, int en);
int partition(vector<int> &vi, int st, int en);

int main (void){
	freopen("input.txt","r", stdin );
	vector<int> vi;
	cout <<"Enter numbers to be sorted : " << endl;
	int x;
	while( cin >> x ) vi.push_back(x);
	for(int i : vi) cout << i << " " ;
	cout << endl;
	cout << endl << "selection sort recursive " << endl;
	profileAndPrintResult(sort, selectionSortHelp, vi);
	cout << endl << "selection sort itr " << endl;
	profileAndPrintResult(sort, selectionSortItr, vi);
	cout << endl << "Bubble sort rec " << endl;
	profileAndPrintResult(sort, bubbleSortHelper, vi);
	cout << endl << "Bubble sort itr " << endl;
	profileAndPrintResult(sort, bubbleSortItr, vi);
	cout << endl << "Insertion sort " << endl;
	profileAndPrintResult(sort, insertionSort , vi);
	cout << endl << "Insertion sort itr " << endl;
	profileAndPrintResult(sort, insertionSortItr, vi);
	cout << endl << "merge sort rec " << endl;
	profileAndPrintResult(sort, mergeSort, vi);
	cout << endl << "merge sort itr " << endl;
	profileAndPrintResult(sort, mergeSortItr, vi);
	cout << endl << "quick sort " << endl;
	profileAndPrintResult(sort, quickSort, vi);
	return 0;
}

void profileAndPrintResult(void (*sort)(vector<int> &, void (*helper)(vector<int>&, int,int)),
void (*helper)(vector <int>&, int,int), vector<int> vi){
	vector<int> v(vi.begin(),vi.end());
	auto start = high_resolution_clock::now();
	sort(v,helper);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop-start).count();
	cout << "Sorted in " << duration << " ns" << endl;
	for(int i : v) cout << i << " " ;
	cout << endl;
}

int min_index(vector<int> vi, int st, int en){
	int min_idx = -1, min_val = INT_MAX;
	for(int i = st ; i <= en ; i++){
		if ( vi.at(i) < min_val) {
			min_val = vi.at(i);
			min_idx = i;
		}
	}
	return min_idx;
}

void swap(vector<int> &vi, int idx1, int idx2) {
	int val1 = vi.at(idx1), val2 = vi.at(idx2);
	vi.at(idx1) = val2;
	vi.at(idx2) = val1;
}

void selectionSortHelp(vector<int> &vi, int st, int en){
	if( st ==  en ) return ;
	else {
		int min_idx = min_index(vi,st,en);
		swap(vi, st, min_idx);
		return selectionSortHelp(vi,st+1,en);
	}
}

void selectionSortItr(vector<int> &vi, int st , int en){
	for(int i = st; i < en ; i++){
		int min_idx = min_index(vi,i,en);
		swap(vi,i,min_idx);
	}
}

void sort(vector<int> &vi, void (*helper)(vector<int> &, int, int)){
	int en = vi.size() -1 ; 
	return helper(vi,0,en);
}

void bubbleSortHelper(vector<int> &vi, int st, int en){
	if( en ==  st) return ;
	else{
		for(int i = st ; i < en ; i++){
			if(vi.at(i) > vi.at(i+1)) swap(vi,i,i+1);
		}
		return bubbleSortHelper(vi,st,en-1);
	}
}

void bubbleSortItr(vector<int> &vi, int st, int en){
	for(int e = en; e > st ; e--){
		for(int i = st ; i < e ; i++){
			if( vi.at(i) > vi.at(i+1) ) swap(vi,i,i+1);
		}
	}
	return ;
}

//insert element at index idx in vector<int> vi, with st = 0, en = idx in sorted order.
void insert(vector<int> &vi, int idx){
	for(int j = idx ; j > 0 ; j--){
		if(vi.at(j) < vi.at(j-1)) swap(vi,j-1,j);
		else break;
	}
}

void insertionSort(vector<int> &vi, int st, int en){
	if( st > en) return ;
	else {
		if(st > 0) insert(vi, st);
		return insertionSort(vi, st+1, en);
	}
}

void insertionSortItr(vector<int> &vi, int st, int en){
	for(int i = st+1 ; i <= en ; i++){
		insert(vi,i);
	}
	return ;

}

void merge(vector<int> &vi, int st1, int en1, int st2, int en2, vector<int> v_copy){
	int l = st1 , r = st2 , i = st1 , en = vi.size() -1 ;
	while( l <= en1 && r <= en2){
		int first_left = v_copy.at(l), first_right = v_copy.at(r);
		if(first_left < first_right) {
			vi[i++] = first_left;
			l++;
		}else{
			vi[i++] = first_right;
			r++;
		}
	}
	while( l <= min(en,en1)) vi[i++] = v_copy[l++];
	while( r <= min(en,en2)) vi[i++] = v_copy[r++];
}

void mergeSortHelp(vector<int> &vi, int st, int en, vector<int> &v_copy){
	if( st == en ) return ;
	else {
		int mid = (st+en)/2;
		mergeSortHelp(vi,st,mid,v_copy);
		mergeSortHelp(vi,mid+1,en,v_copy);
		merge(vi,st, mid , mid + 1, en,v_copy);
		for(int i = st; i <= en ; i++) v_copy[i] = vi[i];
	}
}

void mergeSort(vector<int> &vi, int st, int en){
	vector<int> v_copy(vi);
	return mergeSortHelp(vi,st,en,v_copy);
}

void mergeSortItr(vector<int> &vi, int st, int en){
	int len = vi.size();
	vector<int> v_copy(vi);
	for(int size = 1 ; size <= len ; size*=2){ 
		int st1 = st, en1 = st1 + size - 1;
		int st2 = en1 + 1, en2 = st2 + size -1;
		while(st2 <= en){
			merge(vi,st1,en1,st2,min(en,en2),v_copy);
			st1 = en2+1;
			en1 = st1 + size -1 ;
			st2 = en1 + 1;
			en2 = st2 + size -1;
		}
		for(int i=st;i<=en;i++) v_copy[i] = vi[i];
	}
}


int partition(vector<int> &vi, int st, int en){
	int len = en - st + 1;
	int randIdx = st + (rand() % len) ;
	int partitionVal = vi[randIdx];
	swap(vi,st,randIdx);
	int partitionIdx = st+1;
	for(int i = st+1 ; i <= en ; i++){
		if(vi[i] < partitionVal){
			swap(vi,i,partitionIdx);
			partitionIdx++;
		}
	}
	int p = partitionIdx -1 ;
	swap(vi,st,p);
	return p;
}

void quickSort(vector<int> &vi, int st, int en){
	if(st >= en) return ;
	else {
		int p = partition(vi,st,en);
		quickSort(vi,st,p-1);
		quickSort(vi,p+1,en);
	}
}


