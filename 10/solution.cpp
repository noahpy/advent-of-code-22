
#include "../nutils.h"
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>


int cyclecount = 0;
int x = 1;

int solution1 = 0;
int samplecounter = 20;


void sixSumSignalStrength(list<string> lines){
	string cmd = lines.front();
	int v = 0;
	if(cmd.substr(0,4) == "addx"){
		v = stoi(cmd.substr(5, cmd.length()-5));
		cyclecount += 2;
	}
	else {
		cyclecount++;
	}
	if(cyclecount >= samplecounter && samplecounter	<= 220){
		solution1 += samplecounter * x;
		samplecounter += 40;
	}
	x+=v;
}


vector<string> image;
int posy = 0;
int posx = 0;

void drawImage(list<string> lines){
	if(posy > 5){
		return;
	}
	string cmd = lines.front();
	int v = 0;
	int dcycle = 1;
	if(cmd.substr(0,4) == "addx"){
		v = stoi(cmd.substr(5, cmd.length()-5));
		dcycle = 2;
	}
	for(int i=0; i < dcycle; i++){
		if(abs(posx - x) <= 1){
			image[posy][posx] = '#';
		}
		posx ++;
		if(posx > 39){
			posy ++;
			posx = 0;
		}
	}
	x+=v;
}


void printImage(){
	for(string s: image){
		cout << s << endl;
	}
}



int main(){
	runLines(sixSumSignalStrength, getNextLine, getLineListReally("input.txt"));	
	cout << "Solution 1: " << solution1 << endl;

	cyclecount = 0;
	x = 1;
	for(int y = 0; y < 6; y++){
		string s = "";
		for(int x = 0; x < 40; x++){
			s += " ";
		}
		image.push_back(s);
	}
	runLines(drawImage, getNextLine, getLineListReally("input.txt"));	
	printImage();
}
