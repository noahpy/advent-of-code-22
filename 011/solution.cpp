
#include "../nutils.h"
#include <cstddef>
#include <functional>
#include <list>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <regex>


// is true when solving for first puzzle
bool easyMode = true;

class Monkey{
	public:
		list<long> items;
		long inspectcount = 0;
		function<long(long)> op;
		function<size_t(long)> test;
		long divisor;

	Monkey(list<long> l, function<long(long)> o, function<size_t(long)> t, long d){
		items = l;
		op = o;
		test = t;
		divisor = d;
	}

	auto throwToOther() -> pair<size_t, long>{
		if(items.empty())
			return make_pair(0, 0);
		inspectcount++;
		long nextItem = items.front();
		long c = nextItem;
		nextItem = op(nextItem); 
		if(easyMode)
			nextItem /= 3;
		return make_pair(test(nextItem), nextItem);
	}
};


auto makeOperator(string a, string o, string b) -> function<long(long)>{
	return [a, o, b](long x) -> long {
		long first, second;
		if(a == "old"){
			first = x;
		}
		else {
			first = stoi(a);
		}
		if(b == "old"){
			second = x;
		}
		else {
			second = stoi(b);
		}
		if(o == "+")
			return first + second;
		if(o == "*")
			return first * second;
		return 0;
	};	
}


auto makeTest(long divisor, long t, long f) -> function<size_t(long)>{
	return [divisor, t, f](long x){
		if(x%divisor == 0)
			return t;
		return f;
	};
}

vector<Monkey> monkeyVec;

void getMonkeys(list<string> lines){
	lines.pop_front();
	string listingstr = lines.front();
	listingstr = listingstr.substr(listingstr.find(": ") + 2, listingstr.size() - listingstr.find(": ")-1);
	regex regexp("[0-9]+");
	smatch m;
	string::const_iterator cbegin(listingstr.cbegin());
		list<long> items;
	while(regex_search(cbegin, listingstr.cend(), m, regexp)){
		for(string s: m){
			items.push_back(stol(s));
		}
		cbegin = m.suffix().first;
	}
	lines.pop_front();

	string opstring = lines.front();
	opstring = opstring.substr(opstring.find("= ") + 2, opstring.size() - opstring.find("= ") - 1);
	string a = opstring.substr(0, opstring.find(" "));
	string o = opstring.substr(opstring.find(" ")+1, 1);
	string b = opstring.substr(opstring.find_last_of(" ")+1, opstring.size()-opstring.find_last_of(" ")-1);
	lines.pop_front();

	long divisor = stol(lines.front().substr(lines.front().find_last_of(" ")+1, lines.front().size()-lines.front().find_last_of(" ")));
	lines.pop_front();
	long desttrue = stol(lines.front().substr(lines.front().find_last_of(" ")+1, lines.front().size()-lines.front().find_last_of(" ")));
	lines.pop_front();
    long destfalse = stol(lines.front().substr(lines.front().find_last_of(" ")+1, lines.front().size()-lines.front().find_last_of(" ")));
	lines.pop_front();

	monkeyVec.push_back(Monkey(items, makeOperator(a, o, b), makeTest(divisor, desttrue, destfalse), divisor));	
}


pair<list<string>, list<string>> getNextMonkey(list<string> lines){
	list<string> result{lines.front()};
	lines.pop_front();
	while(!lines.empty() && lines.front().substr(0,6) != "Monkey"){
		result.push_back(lines.front());
		lines.pop_front();
	}
	return make_pair(result, lines);
}


int main(){
	runLines(getMonkeys, getNextMonkey, getLineListReally("input.txt"));

	int n = 20;
	for(int round = 0; round < n; round++){
		for(Monkey& monkey: monkeyVec){
			while(!monkey.items.empty()){
				auto [index, item] = monkey.throwToOther();
				monkeyVec[index].items.push_back(item);
				monkey.items.pop_front();
			}
		}
	}

	pair<long, long> counts = make_pair(0, 0);
	for(Monkey monkey: monkeyVec){
		if(monkey.inspectcount > counts.first){
			counts.second = counts.first;
			counts.first = monkey.inspectcount;
		}
		else if(monkey.inspectcount > counts.second){
			counts.second = monkey.inspectcount;
		}
	}
	cout << "Solution 1: " << counts.first * counts.second << endl;


	monkeyVec.clear();
	easyMode = false;
	runLines(getMonkeys, getNextMonkey, getLineListReally("input.txt"));

	long bigDivisor = 1;
	for(Monkey monkey: monkeyVec){
		bigDivisor *= monkey.divisor;
	}

	n = 10000;
	for(int round = 0; round < n; round++){
		for(Monkey& monkey: monkeyVec){
			while(!monkey.items.empty()){
				auto [index, item] = monkey.throwToOther();
				long r = item % monkeyVec[index].divisor;
				/* cout << item; */
				item %= bigDivisor;
				/* cout << " -> " << item << endl; */
				if(r != item % monkeyVec[index].divisor)
					cout << "changed course!" << endl;
				monkeyVec[index].items.push_back(item);
				monkey.items.pop_front();
			}
		}
	}

	counts = make_pair(0, 0);
	for(Monkey monkey: monkeyVec){
		if(monkey.inspectcount > counts.first){
			counts.second = counts.first;
			counts.first = monkey.inspectcount;
		}
		else if(monkey.inspectcount > counts.second){
			counts.second = monkey.inspectcount;
		}
	}
	cout << "Solution 2: " << counts.first * counts.second << endl;

}
