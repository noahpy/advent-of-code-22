
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <list>
#include <iostream>

using namespace std;

/**
 * Takes a path to a file as input and returns 
 * a vector of the lines of the file read as a string.
 *
 * @param string path
 *
 * @return vector<string> result
*/
vector<string> getLineList(string path){
	ifstream file(path);
	string line;
	vector<std::string> result;
	while(getline(file, line)){
		result.push_back(line);
	}
	return result; 
}


list<string> getLineListReally(string path){
	ifstream file(path);
	string line;
	list<std::string> result;
	while(getline(file, line)){
		result.push_back(line);
	}
	return result; 
}




void runLines(function<void(list<string>)> f, function<pair<list<string>, list<string>>(list<string>)> getNextLines, list<string> lines){
	list<string> nextLines;
	pair<list<string>, list<string>> p = getNextLines(lines);
	nextLines = p.first;
	lines = p.second;
	while (1) {
		f(nextLines);	
		pair<list<string>, list<string>> p = getNextLines(lines);
		nextLines = p.first;
		lines = p.second;
		if(lines.empty()){
			f(nextLines);
			break;
		}
	}
}



pair<list<string>, list<string>> getNextLine(list<string> lines){
	list<string> line{lines.front()};
	lines.pop_front();
	return make_pair(line, lines);
}











