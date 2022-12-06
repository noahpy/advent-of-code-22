
#include "../nutils.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

int countListLen(int state, std::string s){
	state++;
	std::cout << state << "!\n";
	return state;
}


int main(void){
    std::vector<std::string> l = getLineList("input.txt");
	int r = runStateFunction<int>(0, std::function<int(int, std::string)>(countListLen), l);
	std::cout << r << "\n";
	}
