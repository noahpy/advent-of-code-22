
#include <cmath>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include "../nutils.h"
#include <map>

using namespace std;

map<pair<int, int>, int> posmap;	
pair<int, int> hpos, tpos;
int solution1 = 0;

void runCmd(list<string> cmdlist){
	string cmdstr = cmdlist.front();
	string cmd = cmdstr.substr(0, cmdstr.find(" "));
	int n = stoi(cmdstr.substr(cmdstr.find(" ")+1, cmdstr.size()));
	pair<int, int> movement;
	//cout << endl << cmd << ": " << n << endl;
	if(cmd == "U")
		movement = make_pair(0, 1);
	else if (cmd == "D")
		movement = make_pair(0, -1);
	else if (cmd == "L")
		movement = make_pair(-1 , 0);
	else 
		movement = make_pair(1, 0);

	for(int i=0; i<n; i++){
		hpos = make_pair(hpos.first + movement.first, hpos.second + movement.second);
		if(abs(hpos.first - tpos.first) > 1){
			tpos.first += (hpos.first - tpos.first)/2;
			if(abs(hpos.second - tpos.second) == 1){
				tpos.second += (hpos.second - tpos.second);
			}
			if(posmap.find(tpos) == posmap.end()){
				solution1++;
				posmap.insert(make_pair(tpos, 1));
				//cout << tpos.first << " : " << tpos.second << endl;
			}
		}
		if(abs(hpos.second - tpos.second) > 1){
			tpos.second += (hpos.second - tpos.second)/2;
			if(abs(hpos.first - tpos.first) == 1){
				tpos.first += (hpos.first - tpos.first);
			}
			if(posmap.find(tpos) == posmap.end()){
				solution1++;
				posmap.insert(make_pair(tpos, 1));
				//cout << tpos.first << " : " << tpos.second << endl;
			}
		}

	}

}



vector<pair<int, int>> posvec;
map<pair<int, int>, int> posmap2;
int solution2 = 0;

void printGrid(){
	vector<string> grid;
	int size = 40;
	for(int i=0; i<size; i++){
		string s = "";
		for(int j=0; j<size; j++){
			s += '.';
		}
		grid.push_back(s);
	}
	for(int i=0; i<posvec.size(); i++){
		auto [x,y] = posvec[i];
		grid[y+size/2-1][x+size/2-1] = i+97;
	}
	grid[size/2-1][size/2-1] = 's';
	for(string s: grid){
		cout << s << endl;
	}

	cout << endl;
}

void runCmd2(list<string> cmdlist){
	string cmdstr = cmdlist.front();
	string cmd = cmdstr.substr(0, cmdstr.find(" "));
	int n = stoi(cmdstr.substr(cmdstr.find(" ")+1, cmdstr.size()));
	pair<int, int> movement;
	//cout << endl << cmd << ": " << n << endl;
	if(cmd == "U")
		movement = make_pair(0, 1);
	else if (cmd == "D")
		movement = make_pair(0, -1);
	else if (cmd == "L")
		movement = make_pair(-1 , 0);
	else 
		movement = make_pair(1, 0);


	for(int j=0; j<n; j++){
		for(int i=0; i<posvec.size()-1; i++){
			if(i==0){
				posvec[i].first += movement.first;
				posvec[i].second += movement.second;
			}
			
			if(abs(posvec[i].first - posvec[i+1].first) == 2 && abs(posvec[i].second - posvec[i+1].second) == 2){
				posvec[i+1].first += (posvec[i].first - posvec[i+1].first)/2;
				posvec[i+1].second += (posvec[i].second - posvec[i+1].second)/2;
				if(i+1 == posvec.size() -1 && posmap2.find(posvec[i+1]) == posmap2.end()){
					solution2++;
					posmap2.insert(make_pair(posvec[i+1], 1));
					//cout << tpos.first << " : " << tpos.second << endl;
				}
			}

			else if(abs(posvec[i].first - posvec[i+1].first) > 1){
				posvec[i+1].first += (posvec[i].first - posvec[i+1].first)/2;
				if(abs(posvec[i].second - posvec[i+1].second) == 1){
					posvec[i+1].second += (posvec[i].second - posvec[i+1].second);
				}
				if(i+1 == posvec.size() -1 && posmap2.find(posvec[i+1]) == posmap2.end()){
					solution2++;
					posmap2.insert(make_pair(posvec[i+1], 1));
					//cout << tpos.first << " : " << tpos.second << endl;
				}
			}
			else if(abs(posvec[i].second - posvec[i+1].second) > 1){
				posvec[i+1].second += (posvec[i].second - posvec[i+1].second)/2;
				if(abs(posvec[i].first - posvec[i+1].first) == 1){
					posvec[i+1].first += (posvec[i].first - posvec[i+1].first);
				}
				if(i+1 == posvec.size()-1 && posmap2.find(posvec[i+1]) == posmap2.end()){
					solution2++;
					posmap2.insert(make_pair(posvec[i+1], 1));
					//cout << tpos.first << " : " << tpos.second << endl;
				}
			}

		}
		//printGrid();
		/* cout << posvec[9].first << " : " << posvec[9].second << endl; */
	}
	//cout << endl;
}


void printResult(){
	vector<string> grid;
	int size = 40;
	for(int i=0; i<size; i++){
		string s = "";
		for(int j=0; j<size; j++){
			s += '.';
		}
		grid.push_back(s);
	}
	for(auto kv: posmap2){
		auto [x,y] = kv.first;
		grid[y+size/2-1][x+size/2-1] = '#';
	}
	grid[size/2-1][size/2-1] = 's';
	for(string s: grid){
		cout << s << endl;
	}

	cout << endl;
}




int main(){
	hpos = make_pair(0, 0);
	tpos = make_pair(0, 0);
	posmap.insert(make_pair(tpos, 1));
	solution1++;
	runLines(runCmd, getNextLine, getLineListReally("input.txt"));
	cout << "Solution 1: " << solution1 << endl;

	for(int i=0; i<10; i++){
		posvec.push_back(make_pair(0, 0));
	}
	posmap2.insert(make_pair(posvec[posvec.size()-1], 1));
	solution2++;
	runLines(runCmd2, getNextLine, getLineListReally("input.txt"));
	//printResult();
	cout << "Solution 2: " << solution2 << endl;

}
