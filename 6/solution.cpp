
#include "../nutils.h"
#include <sstream>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

int main(){	
	list<char> result;
	ifstream t("input.txt");
	stringstream buffer;
	buffer << t.rdbuf();

	int markersize = 14;

	int counter = 0;
	for(char c : buffer.str()){
		result.push_back(c);
		counter ++;
		if(result.size() > markersize){
			result.pop_front();
		}
		if(result.size() == markersize && !existsDupl<list<char>, char>(result)){
			cout << counter << endl;
			return 0;
		}
	}
}





