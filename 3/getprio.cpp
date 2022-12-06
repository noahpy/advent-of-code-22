
#include "../nutils.h"
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

using namespace std;



map<char, int> getDefaultMap(){
	map<char, int> charmap;	
	char s = 'A';
	while (s <= 'Z') {
		charmap.insert({s, -1});
		s++;
	}
	s = 'a';
	while (s <= 'z') {
		charmap.insert({s, -1});
		s++;
	}
	return charmap;
}

vector<char> getDefaultVec(){
	vector<char> result;
	char s = 'A';
	while (s <= 'Z') {
		result.push_back(s);
		s++;
	}
	s = 'a';
	while (s <= 'z') {
		result.push_back(s);
		s++;
	}
	return result;
}


vector<char> getCharList(string s){
	vector<char> result;
	for(char c: s){
		result.push_back(c);
	}
	return result;
}


int charToValue(char c){
	if(c >= 'a'){
		return (c-'a')+1;
	}
	return (c-'A')+27;
}



int runPrioFilter(int state, string s){
	int result = 0;
	size_t halflen = s.size()/2;
	vector<char> a = getCharList(s.substr(0,halflen));
	vector<char> b = getCharList(s.substr(halflen, halflen));
	for(char c: vecToSet<char>(getIntersect<char>(a, b))){
		result += charToValue(c);
	}
	return state + result;
}


tuple<int, vector<char>, int> runBadgeFilter(tuple<int, vector<char>, int> state, string s){
	auto [sum, v, count] = state;
	if(count == 0){
		return make_tuple(sum, getCharList(s), count + 1);
	}
	v = getIntersect<char>(v, getCharList(s));
	if(count == 1){
		return make_tuple(sum, v, count + 1);
	}
	for(char c: vecToSet<char>(v)){
		sum += charToValue(c);
	}
	v.clear();
	return make_tuple(sum, v, 0);
}





int main(){	
	vector<string> linelist = getLineList("input.txt");
	auto [sum, v, count] = runStateFunction<tuple<int, vector<char>, int>>(make_tuple(0, vector<char>{}, 0), function<tuple<int, vector<char>, int>(tuple<int, vector<char>, int>, string)>{runBadgeFilter}, linelist);
	cout << sum << endl;
	}

