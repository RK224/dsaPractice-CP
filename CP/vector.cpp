#include <bits/stdc++.h>
using namespace std;

typedef struct dynamicArray{
	int* array;
	int len;
	int capacity;
} dynamicArray;

typedef dynamicArray* pDynamicArray;

pDynamicArray getArray(int capacity){
	pDynamicArray dArray = new dynamicArray;
	dArray->array = new int[capacity];
	dArray->capacity = capacity;
	dArray->len = 0;
	return dArray;
}

void printDynamicArray(pDynamicArray arr){
	int len = arr->len;
	int* array = arr->array;
	cout << "len : " << len << " capacity : " << arr->capacity << endl;
	for(int v = 0 ; v < len ; v++ ) cout << array[v] << " " ;
	cout << endl;
	return ;
}

void push_back(pDynamicArray arr, int val){
	int len = arr->len, capacity = arr->capacity;
	if(len == capacity) {
		int new_capacity = 2 * capacity;
		int* prev_arr = arr->array;
		arr->array = new int[new_capacity];
		arr->capacity = new_capacity;
		for(int i = 0 ; i < len ; i++) arr->array[i] = prev_arr[i];
	}
	arr->array[len] = val;
	arr->len++;
	return;
}

int front(pDynamicArray arr){ return arr->array[0]; }

int back(pDynamicArray arr){ return arr->array[arr->len]; }

int pop_back(pDynamicArray arr){ 
	int val = back(arr);
	arr->len--;
	return val;
}

int length(pDynamicArray arr){ return arr->len; }

int capacity(pDynamicArray arr){ return arr->capacity ; }

int getIdx(pDynamicArray arr, int idx){ return arr->array[idx] ; }

int main(void){
	pDynamicArray arr = getArray(3);
	printDynamicArray(arr);
	push_back(arr,10);
	push_back(arr,20);
	push_back(arr,30);
	printDynamicArray(arr);
	push_back(arr,40);
	printDynamicArray(arr);
	pop_back(arr);
	printDynamicArray(arr);

	vector<int> vi(10);
	for(int v : vi) cout << v << endl;
	return 0;
}


