
/*
	Author: Henry Shen 	20 March 2016	
	For The College of New Jersey's Data Structure's class

	Insertion and deletion functions for an Doubly Linked List (DLL)
	Each node in the DLL contains a fake social security number and the person's name
	
*/
#include "DLL.h"
#include <iostream>
#include <string>

using namespace std;

// default constructor is already implemented
// do not modify the default constructor
DLL::DLL(){
    headPtr = NULL;
    itemCount=0;
}

// return the head pointer of the list

Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
// the new list is a different object from n
// the new list and object n have the same contents
// Please implement it
DLL::DLL(DLL& n){
	//cout << "in copy constructor, ";
    itemCount = n.itemCount;
   if (itemCount > 0){
	  	cout <<"in while loop, ";
	  	Node *origList = n.headPtr; //pointer accessing old node's data
	  	Node *secondHeadPtr = new Node; //second hptr for new ll
	  	Node *currNode = secondHeadPtr; // points to second ll node that will be filled
	  	Node *nextNode; //going to point to added node
	  	
	  while (currNode != NULL) {
	  	//cout << "in while loop, ";
	  	nextNode = new Node; //next node, currnode to point to 
	  	currNode->ssn = origList->ssn; currNode ->name = origList->name;
	  	currNode ->succ = nextNode; //create beginning of second ll, next node 
	  	nextNode ->pred = currNode;
	  	currNode = currNode -> succ;
	  	origList = origList ->succ;
	  	cout << currNode->name << " " << currNode->ssn << " ";  

	   }  
	}
}

// destructor
// release every node of the list

DLL::~DLL(){
	Node *delPtr = getHeadPtr(); //going to iterate through, will delete thing delptr points to
	Node *nextDel;
	while(delPtr !=NULL){
		nextDel = delPtr -> succ;
		delete delPtr;
		delPtr = nextDel;
	}
	itemCount = 0;
	
}

// if some node has SSN matcthes string ss
// return the index value of the node
// the index value of the first node is 0, the second node is 1, etc.
// if there is node matching ss, return -1
int DLL::search(string ss)const{
	cout <<"sdderchin for basic bitches #becky, " << endl;
	int numAt = 0;
	Node* temp = headPtr;
	Node* temp2;
    temp2 = headPtr;
    while (temp2!= NULL) {
        cout << temp2->ssn << "\t" << temp2->name << endl;
        temp2 = temp2->succ;
    }
	while(temp != NULL){
		cout << " beginning of the while ";
		if (temp->ssn.compare(ss) == 0){
			cout << " duplicate found " << endl;
			return numAt;
		}
		else{
			cout << numAt << " searching ";	
			temp = temp->succ;
			numAt++;
			cout << numAt << endl;
		}
		cout << " here " << endl;
	}
    return -1;
}


// insert (ss, name) to the existing list
// the SSN values are each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
// parameter count is the counter of number of valid insertion
// when you implement this method, consider the following situations:

bool DLL::insert(string ss, string name, int & count){
	cout << "\nIn insert function, inserting: " << name << " " << ss << endl;
	if (headPtr == NULL){ // empty list
		cout << "Linked list is empty, creating/adding first node, ";
		Node* firstNode = new Node;
		headPtr = firstNode;
		firstNode ->ssn = ss;
		firstNode ->name = name;
		firstNode ->succ = NULL;
		firstNode ->pred = NULL;
		count++;
		itemCount++;
		cout << "count = 0 worked, added name is " << name << endl;
		return true;
	}
	else{ 
		cout << "searching if no dups found, ";
		int isThere = search(ss);
		
		if (isThere != -1){ // see if dups are found
			cout << "ignored bitch!\n";
			return false;
		}
		//no dubps found, keep going 
		else {
			cout << "in else statement and no dups found, ";
			Node* temp1 = getHeadPtr(); //first node in ll
			cout << "head ptr points to: " << temp1 ->ssn << endl;
			Node* addedNode = new Node; //going to be added in back or front 
			addedNode ->ssn = ss; addedNode ->name = name; cout << "added data, \n";
			
			while (temp1 != NULL){
				//add to beginning
					cout << " in while, " << endl; 
					cout << temp1->name << " " << temp1->ssn << endl;
			
				if (ss.compare(temp1->ssn) < 0 && temp1->pred == NULL){
					cout << "\nadding at beginning of list, " << endl;
					addedNode->succ = temp1;
					temp1 ->pred = addedNode; 
					addedNode->pred = NULL;
					headPtr = addedNode;
					count++;
					itemCount++;
					return true;
				}
				//add to middle
				else if (ss.compare(temp1->ssn) > 0 && temp1->succ != NULL ){
					cout << "might add to middle, " << temp1 ->succ ->name << " " << temp1 ->succ -> ssn;
					if (ss.compare(temp1->succ->ssn) < 0){
						cout << "\nadded in middle, \n";
						Node *temp2 = temp1-> succ; // temp2 = temp1 +1 
						addedNode ->succ = temp2;
						addedNode->pred = temp1;
						temp1->succ = addedNode;
						temp2->pred = addedNode;
						count++;
						itemCount++;
						return true;
					}
					else 
						temp1 = temp1 ->succ;
				}
				// add to end
				else if (temp1->succ == NULL && ss.compare(temp1->ssn) > 0){
					cout << "\nadded in end, \n";
					addedNode -> pred = temp1;
					temp1 ->succ = addedNode;
					//addedNode ->succ = NULL;
					count++;
					itemCount++;
					return true;
				}
				else{
					cout << "temp1 ssn: " << temp1->ssn;
					temp1 = temp1 ->succ;
				}
			}

		}
	}
		
    return false;
}


// remove node containing ss value
// consider the following situations:

bool DLL::remove(string ss, int & count){
    Node* current = headPtr;
    int currCount = 0;
    //checks if list is empty
    if(current == NULL){
    	itemCount--;
      return true;
    }
    else {
      //checks if removeal item is first in the list
    	while (current != NULL){
	        if(current->ssn == ss){
	        	if (current->pred == NULL){
			      	  Node* next = current->succ;
			      	  headPtr = next;
			      	  next->pred = NULL;
			          delete current;
			          count++;
     	              	itemCount--;

			          return true;
			   }
			   if (current->succ != NULL){ // middle of the linked list
			   		Node *previous = current ->pred; 
			   		Node *peepee = current ->succ; //node in front of being deleted
			   		previous ->succ = NULL;
			   		peepee ->pred = NULL;
			   		//need these lines?
			   		current->succ = NULL;
			   		current ->pred = NULL;
			   		//end confusion (but do you really)
			   		delete current;
			   		previous->succ = peepee;
			   		peepee ->pred = previous;
			   		itemCount--;
			        count++;
			   		return true;
			   }
			   if (current->succ == NULL){ //delete at end 
			   		Node *peepee = current->pred;
			   		current ->pred = NULL;
			   		peepee ->succ = NULL;
			   		delete current;
			   		count++;
			   		itemCount--;
			   		return true;
			   }
			}
			else 
			   	current = current -> succ;

    	}
    	return false;
    }
}

// return the number of the nodes

int DLL::size(){
    
    return itemCount;
}

// iterate through each node
// print out SSN and memory address of each node

void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp!= NULL) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}