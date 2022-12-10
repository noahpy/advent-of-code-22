
#include "../nutils.h"
#include <functional>
#include <string>
#include <vector>
#include <iostream>

using namespace std;



int calScore(int state, string s){
	char op = s[0] - 'A';
	char me = s[2] - 'X';
	int result;
	cout << s[0] << " vs. " << s[2] << "\n";
	switch (modulo<char>((op-me),3)) {
		case 0:
			result = 3;
			break;
		case 1:
			result = 0;
			break;
		case 2:
			result = 6;
			break;
	}
	switch (me) {
		case 0:
			result += 1;
			break;
		case 1:
			result += 2;
			break;
		case 2:
			result += 3;
			break;
	}
	cout << "result: " << result << "\n\n";
	return state + result;
}


int calScore2(int state, string s){
	char op = s[0] - 'A';
	char me = s[2] - 'X';
	int result;
	cout << s[0] << " vs. " << s[2] << "\n";
	char dif;
	switch (me) {
		case 0:
			result = 0;
			dif = 1;
			break;
		case 1:
			result = 3;
			dif = 0;
			break;
		case 2:
			result = 6;
			dif = 2;
			break;
	}
	switch (modulo<char>((op-dif), 3)) {
		case 0:
			result += 1;
			break;
		case 1:
			result += 2;
			break;
		case 2:
			result += 3;
			break;
	}
	cout << "result: " << result << "\n\n";
	return state + result;
}


int main(){
	int result = runStateFunction<int>(0, function<int(int, string)>{calScore2}, getLineList("input.txt"));	
	cout << result << "\n";
}
