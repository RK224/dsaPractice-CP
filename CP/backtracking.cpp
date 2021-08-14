#include <bits/stdc++.h>

using namespace std;

bool sameColumn(int c, int pos_c){
 	return c == pos_c ;
}

bool leftDiagonal(int row, int c, int pos_r, int pos_c, int sizeLenBoard){
	int diff = row - pos_r;
	int diagCol = pos_c - diff;
	return diagCol == c;
}

bool rightDiagonal(int row,  int c , int pos_r, int pos_c, int sizeLenBoard){
	int diff = row - pos_r;
	int diagCol = pos_c + diff;
	return diagCol == c;
}

void getAllowedQueenPositions(int row, int sizeLenBoard, vector<pair<int,int>> curr_pos, vector<vector<pair<int,int>>> &allowedQueenPositions){
	if( row == sizeLenBoard) allowedQueenPositions.push_back(curr_pos);
	else{
		for(int c = 0 ; c < sizeLenBoard ; c++){
			bool allowed = true;
			for(pair<int,int> pos_rc : curr_pos){
				int pos_r = pos_rc.first, pos_c = pos_rc.second;
				if( sameColumn(c, pos_c) || leftDiagonal(row,c, pos_r, pos_c, sizeLenBoard) || rightDiagonal(row,c,pos_r,pos_c, sizeLenBoard)){
					allowed = false; 
					break;
				}
			}
			if(allowed){
				pair<int,int> pos = make_pair(row,c);
				curr_pos.push_back(pos);
				getAllowedQueenPositions(row+1,sizeLenBoard, curr_pos, allowedQueenPositions);
				curr_pos.pop_back();
			}
		}
	}
}

vector<vector<pair<int,int>>> allowedQueenPosn(int sideLenBoard){
	vector<vector<pair<int,int>>> allowedPos;
	if(sideLenBoard == 0) return allowedPos;
	else{
		vector<pair<int,int>> curr_pos;
		getAllowedQueenPositions(0,sideLenBoard,curr_pos, allowedPos);
		return allowedPos;
	}
}

void printBoard(vector<pair<int,int>> board){
	for(pair<int,int> pos : board) cout << "( " << pos.first << " , " << pos.second << " ) " ;
	cout << endl;
}

void printAllowedPos(vector<vector<pair<int,int>>> allowedPos){
	int possibleArr = allowedPos.size();
	cout <<  "No of arrangements " << possibleArr << endl;
	for(vector<pair<int,int>> board : allowedPos) printBoard(board);
}

int main(void){
	printAllowedPos(allowedQueenPosn(9));
}
