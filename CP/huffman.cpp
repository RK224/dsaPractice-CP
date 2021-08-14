#include <bits/stdc++.h>
using namespace std;

struct node {
	int count;
	map<char,string> encodingMap;
};

typedef struct node Node;

bool lesserFirst(Node n1, Node n2){
	return n1.count > n2.count;
}

void printNode(Node n1){
	cout << "Count : " << n1.count << endl;
	for(pair<char,string> itr : n1.encodingMap) cout << itr.first << " --> " << itr.second << endl;
}

map<char,int> getFrequency(string s){
	map<char,int> freqMap;
	for(char c : s) freqMap[c] += 1;
	return freqMap;
}

vector<Node> createNodes(map<char,int> freqMap){
	vector<Node> nodes;
	for(pair<char,int> p : freqMap){
		map<char,string> m;
		m[p.first] = "";
		Node n = { p.second , m };
		nodes.push_back(n);
	}
	return nodes;
}

map<char,string> combineMap(map<char,string> m, map<char,string> m1){
	map<char,string> encodingMap;
	for(pair<char,string> p : m)  encodingMap[p.first] = "0" + p.second;
	for(pair<char,string> p : m1) encodingMap[p.first] = "1" + p.second;
	return encodingMap;
}

Node combineNodes(Node n1, Node n2){
	int count = n1.count + n2.count;
	map<char,string> encodingMap = combineMap(n1.encodingMap, n2.encodingMap);
	return {count, encodingMap};
}

map<char,string> huffmanMap(string s){
	map<char,int> freqMap = getFrequency(s);
	vector<Node> nodes = createNodes(freqMap);
	priority_queue<Node, vector<Node>, bool (*)(Node,Node)> pq(nodes.begin(),nodes.end(),lesserFirst);
	while(pq.size() >= 2){
		Node n1 = pq.top(); pq.pop();
		Node n2 = pq.top(); pq.pop();
		Node n  = combineNodes(n1,n2);
		pq.push(n);
	}
	map<char,string> encoding = pq.top().encodingMap;
	return encoding;
}

string encode(string s, map<char,string> encodingMap){
	string encoded = "";
	for(char c : s) encoded += encodingMap[c];
	return encoded;
}

string huffmanEncoding(string s){
	return encode(s, huffmanMap(s));
}

string decode(string encodedString, map<char,string> encodingMap){
	map<string,char> decodingMap;
	for(pair<char,string> p : encodingMap) decodingMap[p.second] = p.first;
	string key = "", decoded = "";
	int len = encodedString.length();
	for(int i = 0 ; i < len ; i++){
		key += encodedString[i];
		if(decodingMap.count(key)){
			decoded += decodingMap[key];
			key = "";
		}
	}
	return decoded;
}

int main(void){
	string s = "to be or not to be";
	const int len = s.length();
	string encoded = huffmanEncoding(s);
	map<char,string> encodingMap = huffmanMap(s);
	cout << "Encoded " << s << " str len = " << len << " "  << encoded << " " << encoded.length() << " bits " << endl;
	string decoded = decode(encoded, encodingMap);
	cout << "Decoded string = " << encoded << " " << decoded << endl;
	return 0;
}
