/*
	Author: Henry Shen 	20 May 2016	
	For The College of New Jersey's Data Structure's class

	Insertion and deletion functions for an AVL Binary Tree data structure
	Each node in the tree contains a fake social security number and the person's name
	
*/

//inserts a node into the AVLTree
//if tree is empty, will first node entered will be the root
//if not empty, will traverse to bottem of the tree and add node to leaf
// @param ss, the SSN to be added
// @param na, the person's first and last name separated with a whitespace
// @return return true if no nodes with same SSN are found, succesfully added 
	//else return false of same ssn exists
bool AVLTree::insert(string ss, string na){
   //no AVLTree exists, creates new one, with first inserted note 
   //as the root node
    AVLNode *firstNode;
    firstNode = root;
    if (root == NULL){
         firstNode = new AVLNode(ss, na);
        root = firstNode;
        root ->height = 0;
        firstNode ->right = NULL;
        firstNode ->left = NULL;
    	return true; 
    }
    else {
    		//adding node to another node in the tree or to the root
    		AVLNode *searchNode = firstNode; 
    		AVLNode *insertPoint = NULL; //going to be parent of searchNode
		    while (searchNode != NULL ) { //searching 
		        if (ss.compare(searchNode->ssn) == 0) {
		        	//cout << " the same found, returning false " << endl;
		            return false;
		        }
		        else if (ss.compare(searchNode->ssn) < 0) {
		            //cout << "\tmoving left, node =" << searchNode ->ssn << endl;
		            insertPoint = searchNode;
		            if (searchNode ->left == NULL){
		            	insertPoint = searchNode;
		            	searchNode = NULL;
		            	//cout << "\tsearchNode is null now" << endl;
		            	break;
		            }
		            else {
		            	searchNode = searchNode->left;
		            	 //cout << "\tmoved left, now pointing to node = " << searchNode ->ssn << endl;
		            }
		        }
		      	else if (ss.compare(searchNode ->ssn) > 0){
		        	//cout << "\tmoved right, node =" <<searchNode ->ssn << endl;
		        	if (searchNode ->right != NULL){
		            	insertPoint = searchNode;
		           		searchNode = searchNode ->right;
		           		//cout << "\tmoved right, now pointing to node = " << searchNode->ssn << endl;
		           	}
		           	else {
		           		insertPoint = searchNode;
		           		searchNode = NULL;
		          		
		            	//cout << "\tsearchNode is null now" << endl;
		            	break;

		          		}
		        }
		        else {
		        	return false;
		        }
	    	}
	    	//cout << "\tout of while loop" << endl;
	    	if (searchNode == NULL){
	    		//cout << "\tsearchNode is null " << endl;
	    		AVLNode *newNode = new AVLNode(ss, na);
	    		newNode ->parent = insertPoint;
	    		if (ss.compare(insertPoint ->ssn) < 0){
	    			insertPoint ->left = newNode;

	    		}
	    		else 
	    			insertPoint ->right = newNode;
	    		//cout << "\tinserted new node " << endl;

	    		AVLNode *balancePtr = insertPoint;
	    		//cout << " i guess cant aassign to null ?? dfdsf "<< balancePtr -> parent << endl;
	    		while (balancePtr != NULL){
	    			//cout << "now balancing " << endl;
	    			balancePtr = balance(balancePtr);
	    			balancePtr = balancePtr ->parent;
	    		}
	    		return true;
	    	}
	    //}

    }
}


//deletes a node fro mthe AVL Tree
// @param ss, the SSN to be searched and deleted
// @return return true if node found and deleted 
//else return false if no exisiting node exists
bool AVLTree::deleteNode(string ss){
	
    AVLNode *searchPtr = root; //traverses the tree, will point to node to delete 
    AVLNode *searchParent = searchPtr ->parent; //could be action position for special delete case 
    //cout << "in deleting ssn = " << ss << endl;
    while (searchPtr != NULL){
    	if (searchPtr ->ssn == ss){
    		//actually delete
    		//if node is only a leaf
    		if (searchPtr ->right == NULL  && searchPtr ->left == NULL){
    			//cout << "\tdeleteing leaf " << endl;
    			if (ss.compare(searchParent ->ssn) > 0){
    				searchParent ->right = NULL;
    			}
    			else 
    				searchParent ->left = NULL; 
    			searchPtr ->parent = NULL;
    			delete searchPtr;
    			break;
    		}
    		//only has one child node
    		else if (searchPtr ->right != NULL && searchPtr ->left == NULL){ // delete right node
    			cout << "delete parent with one child" << endl;
    			searchPtr ->right ->parent = searchParent;
    			searchParent ->right = NULL;
    			searchPtr ->parent = NULL;
    			delete searchPtr;
    			break;
    		}
    		else if (searchPtr ->right == NULL && searchPtr ->left != NULL){ //delete left
	    		cout << "delete parent with one child" << endl;
    			searchPtr ->left ->parent = searchParent;
    			searchParent ->left = NULL;
    			searchPtr ->parent = NULL;
    			break; 

    		}
    		else { // in middle of tree
    			AVLNode *largestLeft = maxOfSubtree(searchPtr ->left);
    			/*cout << " delete in middle of tree "<< endl;
    			cout << "largestLeft = " << largestLeft ->ssn << endl;*/
    			//cout << "root right = " << root->right->ssn << endl;
    			//cout << "searchPtr = " << searchPtr ->ssn << endl;
    			searchPtr ->ssn = largestLeft ->ssn;
    			searchPtr ->name = largestLeft ->name;
    			//cout << "new searchPtr = " << searchPtr ->ssn << endl;
    			if (largestLeft ->parent != searchPtr){
    				//cout << " parent -> left is biggest" << endl;
    				largestLeft ->parent -> right = NULL;
    			}
    			else if (largestLeft ->parent == searchPtr){
    				//cout << " somethign bad is happening, searchPtr -> left = " << searchPtr ->left ->ssn << endl;
    				largestLeft ->parent = NULL;
    				searchPtr ->left = NULL;
    				//cout << "made shit null" << endl;
    				if (largestLeft ->right  == NULL && largestLeft ->left == NULL){
    					//cout << "what?????" << endl;
    				}

    			} 
    			else
    				cout << "wtf is happeningnggdgdg!!!" << endl;
    			
    			largestLeft ->parent = NULL;
    			//cout << " 1 " << endl;
    			print();
    			//cout << "largestLeft = " << largestLeft ->ssn << endl;
    			delete largestLeft;
     			//cout << "got to here " << endl;
   			
    			break;
    		}

    	}
    	else if (ss.compare(searchPtr ->ssn) < 0){
    		//move left
    		//cout << "\tmoved left" << endl;
    		searchParent = searchPtr;
    		searchPtr = searchPtr ->left;
    		
    	}
    	else if (ss.compare(searchPtr ->ssn) > 0){
    		//move right
    		//cout << "\tmoved right" << endl;
    		searchParent = searchPtr;
    		searchPtr = searchPtr ->right;
    		
    	}
    	else {
    		//cout << "you cray" << endl;
    		return false;
    	}

    }
    if (searchPtr == NULL){
    	//cout << "\tno matches found " << endl;
    	return false;
    }
    else {
    	//cout << "\t before balancing" << endl;
    	//print();

		AVLNode *balancePtr = searchParent;
	    //cout << "\tbalancing" << endl; 
	    while (balancePtr != NULL){
	 		//cout << "now balancing " << endl;
	    	balancePtr = balance(balancePtr);
	    	balancePtr = balancePtr ->parent;
	    }
    }
	//print();
    //cout << "\tend of deletion " << endl;
    return true;
}
   