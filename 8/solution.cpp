
#include "../nutils.h"
#include <iostream>
#include <string>
#include <vector>


bool check_visible(int x, int y, vector<string> lines){
	char height = lines[y][x];
	bool visible = true;
	if(x == 0 || x == lines[0].size()-1 || y == 0 || y == lines.size()-1)
		return true;

	for(int dx = x-1; dx>=0; dx--){
		visible &= height > lines[y][dx];
	}
	if(visible){
		return true;
	}

	visible = true;
	for(int dx = x+1; dx<lines[0].size(); dx++){
		visible &= height > lines[y][dx];
	}
	if(visible){
		return true;
	}

	visible = true;
	for(int dy = y-1; dy >= 0; dy--){
		visible &= height > lines[dy][x];
	}
	if(visible){
		return true;
	}

	visible = true;
	for(int dy = y+1; dy<lines.size(); dy++){
		visible &= height > lines[dy][x];
	}
	if(visible){
		return true;
	}
	return false;

}


int get_rating(int x, int y, vector<string> lines){
	char height = lines[y][x];
	int result = 1;

	int count = 0;
	for(int dx = x-1; dx>=0; dx--){
		count ++;
		if(height <= lines[y][dx]){
			break;	
		}
	}
	result *= count;
	
	count = 0;
	for(int dx = x+1; dx<lines[0].size(); dx++){
		count ++;
		if(height <= lines[y][dx]){
			break;	
		}
	}
	result *= count;

	count = 0;
	for(int dy = y-1; dy >= 0; dy--){
		count ++;
		if(height <= lines[dy][x]){
			break;	
		}
	}
	result *= count;
	
	count = 0;
	for(int dy = y+1; dy<lines.size(); dy++){
		count ++;
		if(height <= lines[dy][x]){
			break;	
		}
	}
	result *= count;


	return result;	
}



int main(){
	vector<string> lines = getLineList("input.txt");
	int solution1 = 0;
	int solution2 = 0;
	for(int y=0; y < lines.size(); y++){
		for(int x=0; x < lines[0].size(); x++){
			int result = get_rating(x, y, lines);	
			if(result > solution2){
				solution2 = result;
			}
			if (check_visible(x, y, lines)) {
				solution1++;
			}
		}
	}
	cout << "Solution 1: " << solution1 << endl;
	cout << "Solution 2: " << solution2 << endl;
}
