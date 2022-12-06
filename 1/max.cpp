
#include <bits/types/FILE.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>

int main(void){
    std::ifstream infile("input.txt");
	std::string line;
	int max = 0;
	int result = 0;
	while (std::getline(infile, line)){
		try{
			std::cout << line << "\n";
			result += std::stoi(line);
		}
		catch(std::exception e) {
		   if(result > max){
			   max = result;
		   }
		   result = 0;
		}
	}
	printf("%d\n", max);
}
