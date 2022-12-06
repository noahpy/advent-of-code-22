
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

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










