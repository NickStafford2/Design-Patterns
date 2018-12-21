/*
Name:       Nicholas Stafford
Program:    diff.cpp
Class:      cs44001
Due Date:   1/25/18

Description: compare 2 files and note where they are different
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;



int main(int argc, char *argv[]) {

	// If there is not 2 arguments provided, terminate.   
	if (argc != 3) {
		cerr << "Enter in two text files to compare" << endl;
		return 0;
	}

	cout << endl;

	// Create file readers readers for both files.
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);

	// Ensure both files are open
	if (!file1.is_open() || !file2.is_open()) {
		cerr << "Could not open files" << endl;
		return 0;
	}

	int lineNumber = 1;
	// search through files line by line and compare
	// stop searching when the end of both files is reached
	while (!(file1.eof() && file2.eof())) {
		string line1, line2;

		// if the end of te file is reached assume there is an empty string
		if (file1.eof()) line1 = "";
		else getline(file1, line1);

		if (file2.eof()) line2 = "";
		else getline(file2, line2);



		if (line1 != line2) {
			// Print out the lines values 
			cout << argv[1] << ": " << lineNumber << ": " << line1 << endl;
			cout << argv[2] << ": " << lineNumber << ": " << line2 << endl;

			// create a string with a ^ at the location of the first different charicters 
			int i = 0;
			while (line1[i] == line2[i]) {
				// compare the lines until you find the difference. Track location as you go
				i++; 
			}
			//find how many spaces are before the difference is displayed on the console
			string spacer(strlen(argv[1]) + 2 + to_string(lineNumber).length() + 2 + i, ' ');

			cout << spacer << "^" << endl;
		}
		lineNumber++;
	}
	file1.close(); 
	file2.close();
	return 1;
}
