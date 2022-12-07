
#include "../nutils.h"
#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <list>
#include <utility>
#include <stack>
#include <regex>

using namespace std;

struct File{
	int size = -1;			
	string name;	
};


struct Directory{
	vector<Directory> subdir;
	vector<File> subfile;
	int size = -1;
	string name;
};

vector<Directory> dirVec;
vector<File> fileVec;

stack<reference_wrapper<Directory>> dirTrace;

auto linesTilNextCmd(list<string> lines) -> pair<list<string>, list<string>>{
	list<string> result;
	result.push_back(lines.front());
	lines.pop_front();
	while (!lines.empty() && lines.front().at(0) != '$') {
		result.push_back(lines.front());
		lines.pop_front();
	}
	return make_pair(result, lines);
}

auto runCmd(list<string> lines){
	string cmd = lines.front();
	lines.pop_front();
	if(lines.size() > 0){
		while (!lines.empty()) {
			string line = lines.front();
			lines.pop_front();
			string firsthalf = line.substr(0,line.find(' '));
			string name = line.substr(line.find(' ')+1, line.size());
			if(firsthalf == "dir"){
				Directory nd = Directory{name:name};
				dirTrace.top().get().subdir.push_back(nd);
				cout << "Found dir: " << name << endl;
			}	
			else{
				int size = stoi(firsthalf);
				File nf = File{size, name};
				dirTrace.top().get().subfile.push_back(nf);
				cout << "Found file: " << name << " with size: " << size << endl;
			}
		}
		return;
	}
	string dirname = cmd.substr(cmd.find_last_of(" ")+1, cmd.size());
	cout <<"Go to: " << dirname << endl;
	if(dirname == ".."){
		dirTrace.pop();
	}
	for(Directory& d: dirTrace.top().get().subdir){
		if(d.name == dirname){
			dirTrace.push(d);
			break;
		}
	}
}

int solution1 = 0;

int getSolution1(Directory& root){
	int size = 0;
	for(File& f: root.subfile){
		size += f.size;
	}
	for(Directory& d: root.subdir){
		size += getSolution1(d);
	}
	if(size < 100000){
		solution1 += size;
	}
	root.size = size;
	return size;
}

pair<string, int> getSolution2(Directory& root, string bestname, int bestsize, int bound){
	//cout << root.name << ": " <<root.size << endl;
	if(root.size < bound){
		return make_pair(bestname, bestsize);
	}
	if(root.size >= bound && root.size < bestsize){
		bestname = root.name;
		bestsize = root.size;
	}
	for(Directory& d: root.subdir){
		auto [nname, nsize] = getSolution2(d, bestname, bestsize, bound);
		if(nsize < bestsize){
			bestname = nname;
			bestsize = nsize;
		}
	}
	return make_pair(bestname, bestsize);
}


int main(){
	Directory rootRoot = Directory{};
	rootRoot.name = "root";
	Directory root = Directory{name:"/"};
	rootRoot.subdir.push_back(root);
	dirTrace.push(rootRoot);
	runLines(runCmd, linesTilNextCmd, getLineListReally("input.txt"));
	int totalSize = getSolution1(rootRoot);
	cout <<endl << "Solution 1: " << solution1 << endl;
	//cout << totalSize << endl;
	auto [name, size] = getSolution2(rootRoot, rootRoot.name, rootRoot.size, 30000000-(70000000-totalSize));
	cout << "Solution 2: " << size << endl;

}


