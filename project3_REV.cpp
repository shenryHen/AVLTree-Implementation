/*
	Author Henry Shen 20 March 2016

	Driver file for Doubly Linked List
*/
#include "DLL.h"
#include <iostream>
#include <string>
#include <fstream>
//#include <cstdio>
#include <ctime>

using namespace std;

int main(int arc, char *argv[]){
	clock_t start, end;
	double duration;
	start = clock();
    DLL myList;
    fstream input(argv[1]);
	int numInsert = 0; //number of insertions to DLL
	int numDelete = 0; // number of deletions
	int numRetrieve = 0; //number of retrievals from DLL 
	while (!input.eof()){
		bool upCount; //contains if listLength is incrmted/decrmnted or not
		char instruct;
		string tempSSN;
		string tempName;
		input >> instruct;
		input >> tempSSN;
		getline(input, tempName); // gets full name w/ space
		//cout << "The instructions " << instruct << "\tFull temp name is " << tempName << endl;
		switch (instruct){
			case 'i':
				//cout << "Inserting now\t";
				myList.insert(tempSSN, tempName, numInsert);
				tempSSN.clear(); 	tempName.clear();
				break;
			case 'd':
				myList.remove(tempSSN, numDelete);
				tempSSN.clear(); 	tempName.clear();
				break;
			case 'r':
				if(myList.search(tempSSN) != -1)
					numRetrieve++;
				tempSSN.clear(); 	tempName.clear();
				break;
			default:
				break;
		}
	}


	input.close();
    end = clock();
    duration = (end - start) / (double) CLOCKS_PER_SEC;
    
    cout << "Number of valid insertions: " << numInsert << endl;
	cout << "Number of valid deletions: " << numDelete << endl;
	cout << "Number of valid id retrievals: " << numRetrieve << endl;
	cout << "Number of items in the linked list is " << myList.size() << endl;
    cout << "Elapsed time: " << duration << endl;
    myList.display();
    cout << "size is " << myList.size();

    return 0;
    
    
}