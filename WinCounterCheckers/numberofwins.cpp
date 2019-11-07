#include <iostream>
#include <string>
#include <fstream>
#include "winnerFunction.h"

using namespace std;

int main() {
	ofstream fout("wins.txt");
	int redWins = 0;
	int blackWins = 0;
	string reader;
	if (winner() == 0) {
		redWins++;
	}
	if (winner() == 1) {
		blackWins++;
	}
	cout << "Red Wins: " << redWins << endl;
	cout << "Black Wins: " << blackWins << endl;
	fout.close();
	ifstream fin("wins.txt");
	fin >> reader;
	cout << reader;
	cin >> redWins;
}