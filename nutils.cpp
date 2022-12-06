
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;


vector<string> getLineList(string path){
	ifstream file(path);
	string line;
	vector<std::string> result;
	while(getline(file, line)){
		result.push_back(line);
	}
	return result; 
}










