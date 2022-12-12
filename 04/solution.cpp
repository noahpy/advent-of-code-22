
#include "../nutils.h"
#include <functional>
#include <string>
using namespace std;


int runCountRedundant(int state, string s){
	string a = s.substr(0,s.find(","));
	string b = s.substr(s.find(",")+1, s.size()-s.find(",")-1);
	int a_lower = stoi(a.substr(0,a.find("-")));
	int a_higher = stoi(a.substr(a.find("-")+1, a.size()-a.find("-")-1));
	int b_lower = stoi(b.substr(0,b.find("-")));
	int b_higher = stoi(b.substr(b.find("-")+1, b.size()-b.find("-")-1));
	if(a_lower == b_lower || a_higher == b_higher){
		return state+1;
	}
	if(a_lower < b_lower && a_higher > b_higher){
		return state+1;
	}
	if(b_lower < a_lower && b_higher > a_higher){
		return state+1;
	}
	return state;
}


int runCountOverlap(int state, string s){
	string a = s.substr(0,s.find(","));
	string b = s.substr(s.find(",")+1, s.size()-s.find(",")-1);
	int a_lower = stoi(a.substr(0,a.find("-")));
	int a_higher = stoi(a.substr(a.find("-")+1, a.size()-a.find("-")-1));
	int b_lower = stoi(b.substr(0,b.find("-")));
	int b_higher = stoi(b.substr(b.find("-")+1, b.size()-b.find("-")-1));
	
	if(a_higher >= b_lower && a_higher <= b_higher){
		return state+1;
	}
	if(a_lower >= b_lower && a_lower <= b_higher){
		return state+1;
	}
	if(a_lower == b_lower || a_higher == b_higher){
		return state+1;
	}
	if(a_lower < b_lower && a_higher > b_higher){
		return state+1;
	}
	if(b_lower < a_lower && b_higher > a_higher){
		return state+1;
	}

	return state;
}


int main(){
	int result = runStateFunction<int>(0, function<int(int, string)>{runCountOverlap}, getLineList("input.txt"));
	cout << result << endl;
}
