
#include "../nutils.h"
#include <cstddef>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <regex>

using namespace std;


vector<stack<char>> getStartStacks(){
	vector<string> lineList = getLineList("containers.txt");
	vector<stack<char>> result;
	for(string s : lineList){
		stack<char> stk;
		for(char c: s){
			stk.push(c);
		}
		result.push_back(stk);
	}
	return result;
}

tuple<int, int, int> getMove(string s){
	regex regexp("([0-9]+) from ([0-9]+) to ([0-9]+)");
	smatch m;
	regex_search(s, m, regexp);
	return make_tuple(stoi(m[1]), stoi(m[2]), stoi(m[3]));
}

vector<stack<char>> runMovement(vector<stack<char>> state, string s){
	auto [n, from, to] = getMove(s);
	for(size_t i = 0; i < n; i++){
		char tmp = state[from-1].top();
		state[from-1].pop();
		state[to-1].push(tmp);
	}
	return state;
}


vector<stack<char>> runMovement2(vector<stack<char>> state, string s){
	auto [n, from, to] = getMove(s);
	stack<char> stk;
	for(size_t i = 0; i < n; i++){
		char tmp = state[from-1].top();
		state[from-1].pop();
		stk.push(tmp);
	}
	while(!stk.empty()){
		state[to-1].push(stk.top());
		stk.pop();
	}
	return state;
}


int main(){
	vector<stack<char>> result = runStateFunction<vector<stack<char>>>(getStartStacks(), function<vector<stack<char>>(vector<stack<char>>, string)>{runMovement2}, getLineList("input.txt"));	
	for (stack<char> stk : result) {
		if(!stk.empty()){
			cout << stk.top();
		}
	}
	cout << endl;
}
