
#include <cstddef>
#include <functional>
#include <vector>
#include "../nutils.h"
#include <string>
#include <exception>
#include <iostream>

using namespace std;

vector<int> getTopThree(vector<int> state, string s){
	try {
		int x = stoi(s);
		state[3] = state[3] + x;
	} catch (exception e) {
		if(state[0] < state[3]){
			state[2] = state[1];
			state[1] = state[0];
			state[0] = state[3];
		}
		else if(state[1] < state[3]){
			state[2] = state[1];
			state[1] = state[3];
		}
		else if(state[2] < state[3]){
			state[2] = state[3];
		}
		state[3] = 0;
	}
	return state;
}


int main(void){
	vector<string> s = getLineList("input.txt");
	vector<int> slist{0,0,0,0};
	slist = runStateFunction<vector<int>>(slist, function<vector<int>(vector<int>, string)>{getTopThree}, s);
	cout << (slist[0] + slist[1] + slist[2]) << "\n";	
}
