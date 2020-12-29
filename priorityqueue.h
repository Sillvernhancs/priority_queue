 // priorityqueue.h
//
// TODO:  write this header comment
#pragma once

#include <iostream>
#include <sstream>
#include <set>
#include <string>
using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    
   void _copyOpHelper(NODE* node) {
    	if(node == nullptr) {
    		return;
    	}
    	enqueue(node->value, node->priority);
    	// if it has a duplicate priority;
		if(node->link != nullptr) {
			NODE* temp = node->link;
			while(temp!= nullptr) {
				enqueue(temp->value, temp->priority);
				temp = temp->link;
			}
		}
		_copyOpHelper(node->left);
    	_copyOpHelper(node->right);
    }
    
    void _clearHelper(NODE* node, int &sizeNow) {
    	if (node != nullptr) {
    		_clearHelper(node->left,sizeNow);
    		_clearHelper(node->right,sizeNow);
    		// delete the linked list for dups if it has.
    		if(node->link != nullptr) {
    			NODE* next = nullptr;
    			while(node->link != nullptr) {
    				next = node->link->link;
    				delete node->link;
    				node->link = next;
    				sizeNow--;
    			}
    		}
    		// delete the node.
    		delete node;
    		sizeNow--;
    	}
    	
    }
    
        // a helper function for getMin
    
    NODE* getMin(NODE* node) {
		if (node == nullptr) {
			return nullptr;
		}
		NODE* min = node;
		while(min->left != nullptr) {
			min = min->left;
		}
		return min;
    }
    
     // helper function for TO STRING.
    bool _printHelper(NODE* node, ostream& output) {
    	if(node != nullptr) {
    		_printHelper(node->left, output);
    		output << node->priority << " value: " << node->value << "\n";
    		_printHelper(node->link, output);
    		_printHelper(node->right, output);
    		return true;
    	} else {
    		return false;
    	}
    	
    }
    
        // The helper function for equality operator.
    bool _equalityHelper(NODE* node, NODE* node2) const {
    	// if they are both empty
    	if (node == nullptr && node2 == nullptr) {
    		return true;
    	} else if (node == nullptr || node2 == nullptr) {
    		return false;
    	}
    	
    	if (_equalityHelper(node->left, node2->left) == true &&
    		_equalityHelper(node->right, node2->right) == true &&
    		_equalityHelper(node->link, node2->link) == true &&
    		node->priority == node2->priority &&
    		node->value == node2->value
    		) {
			// if EVERYTHING matches up, then it's true.
    		return true;
    	} else {
			// if ANYTHING didn't add up, then it's false
			return false;
    	}
    }
    
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        
        size = 0;
        root = nullptr;
        curr = nullptr;
        
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //

    priorityqueue& operator=(const priorityqueue& other) {
        
        if(this == &other) {
        	return *this;
        }
        // // delete old "this"
        clear();
        
        if(other.root != nullptr) {
        	_copyOpHelper(other.root);
        } else {
        	this->size = 0;
        	this->root = nullptr;
        	this->curr = nullptr;
        }
        
        return *this;
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //

    void clear() {
        _clearHelper(this->root,this->size);
        root = nullptr;
        curr = nullptr;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        if (root != nullptr) {
        	clear();
        }
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority) {
    	// make a node with all the data that we need;
    	NODE* node = new NODE;
    	node->value = value;
    	node->priority = priority;
    	node->left = nullptr;
    	node->right = nullptr;
    	node->link = nullptr;
    	node->parent = nullptr;
    	node->dup = false;
    	
    	// if the tree is empty.
    	if(root == nullptr) {
    		root = node;
    		size = 1;
    		return;
    	}
    	// make a temp pointer that points to the root.
    	NODE* temp = root;
    	NODE* parent = nullptr;
    	while (temp != nullptr) {
    		// save the parent pointer
    		parent = temp;
    		// if we need to go left.
    		if (priority < temp->priority) {
    			if (temp->left == nullptr) {
    				temp->left = node;
    				temp->dup = false;
    				node->parent = parent;
    				break;
    			} else {
    				temp = temp->left;
    			}
    		} else if (priority > temp->priority){
    			// we need to go right.
    			if (temp->right == nullptr) {
    				temp->dup = false;
    				temp->right = node;
    				node->parent = parent;
    				break;
    			} else {
    				temp = temp->right;
    			}
    		} else {
    			// IF THE VALUE ALREADY EXIST.
    			node->dup = true;
    			// IF it's the first link.
    			// go the the end of the linked list.
    			while(temp->link != nullptr) {
    				temp = temp->link;
    			}
    			// insert the node in.
    			temp->link = node;
    			node->parent = parent;
    			break;
    		}
    	}
        size++;
        
    }

    // end of helper function for getMin.
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T dequeue() {
        // first get the smallest
        NODE* temp = getMin(this->root);
        NODE* parent = nullptr;
    	// a set to be delete after we change temp.
    	NODE *toDelete = temp;
        // initialize;
        T valueOut;
        // IF THE QUEUE IS EMPTY
        if (temp == nullptr) {
        	return valueOut;
        }
        // decrement size.
        this->size--;
        // get the data
        valueOut = temp->value;
        // if temp has a parent.
        if (temp->parent != nullptr) {
        	parent = temp->parent;
        }
        // check if there is a linked list.
        if (temp->dup == true || temp->link != nullptr) {
	        // if it's not at the end of the linked list.
	        if (temp->link != nullptr) {	
	
	        	if (parent == nullptr) {
	        		root = temp->link;
	        		root->right = temp->right;
	        		root->parent = nullptr;
	        		delete toDelete;
	        		return valueOut;
	        	}
	        	// link the values.
	        	// copy the left child
	        	if (temp->left != nullptr) {
	        		temp->link->left = temp->left;
	        	} else {
	        		temp->link->left = nullptr;
	        	}
	        	// copy the right child
	        	if (temp->right != nullptr) {
	        		temp->link->right = temp->right;
	        	} else {
	        		temp->link->right = nullptr;
	        	}
	        	temp->link->parent = parent;
	        	// if the parent is on the left.
	        	if (parent->right == temp) {
	        		parent->right = temp->link;
	        		delete toDelete;
	        		temp = parent->right;
	        	} else if (parent->left == temp) {
	        		parent->left = temp->link;
	        		delete toDelete;
	        		temp = parent->left;
	        	}
	        	return valueOut;
	        }
        }
        // remove if it's a leaf.
        if (temp->left == nullptr && temp->right == nullptr) {
    		//delete the node when height is one.
    		if (parent == nullptr) {
    			delete temp;
    			this->root = nullptr;
    		// if the the node has a parent on the right.
    		} else if (parent->left == temp) {
    			// cout << "CATCH 2\n";
    			delete temp;
    			parent->left = nullptr;
    		// if the the node has a parent on the left.
    		} else if (parent->right == temp) {
    			// cout << "CATCH 3\n";
    			delete temp;
    			parent->right = nullptr;
    		}
    	// if it has a right child.
        } else if (temp->left == nullptr && temp->right != nullptr) {
    		// delete the node when it's the root node.
        	if (parent == nullptr) {
        		// cout << "CATCH 4\n";
        		this->root = temp->right;
        		this->root->parent = nullptr;
        		delete toDelete;
        	// delete when it has a parent on the right
        	} else if (parent->left == temp) {
				parent->left = temp->right;
				temp->right->parent = parent;
				delete toDelete;
			// delete when it has a parent on the left
    		} else if (parent->right == temp) {
				parent->right = temp->left;
				temp->left->parent = parent;
				delete toDelete;
    		}
        }
        return valueOut;
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;

    void begin() {
    	curr = root;
    	curr = getMin(curr);
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(?) - hard to say.  But approximately O(logn + m).  Definitely not O(n).
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //

    bool next(T& value, int &priority) {
    	if (curr == nullptr) {
    		return false;
    	}
    	
    	// get the value.
    	value = curr->value;
        priority = curr->priority;
        // IF THERE ARE DUPLICATES
        if (curr->link != nullptr) {
        	if (curr->link->dup == true) {
	         	curr = curr->link;
	         	// grab the data.
	        	return true;
        	}
         }
         
        // Check if it's at the end of the linked list. 
        if (curr->dup == true && curr->link == nullptr) {
        	// edge case where it's at the end of the linked list
        	// AND has no parents.
        	if (curr->parent == nullptr 
        	&& (curr->left == nullptr 
        	&& curr->right == nullptr)) {
		    	return false;
        	}
        	// if it's not the thing mentioned above then
        	// keep going.
        	curr = curr->parent;
        }
        
        // edege case where the tree has a height of 0.
        if (curr->parent == nullptr && 
        	curr->left == nullptr && 
        	curr->right == nullptr) {
        	return false;
        }
        
        // if the sub right tree is not empty
        // go to the right sub tree.
        if (curr->right != nullptr) {
        	curr = getMin(curr->right);
        	return true;
        }
        
        // get the parent's node.
	    NODE* parent = curr->parent;
	    // if nothing above was run, the climb back up the tree.
	    while( parent != nullptr && curr == parent->right) {
	    	// move back up the tree.
	    	curr = parent;
	    	parent = parent->parent;
	    }

	    curr = parent;

	    if (curr == nullptr) {
    		return false;
    	}

        return true;
    }
    

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        string str = "";
        stringstream sstream(str);
        _printHelper(this->root, sstream);
        str = sstream.str();
        return str; // TO DO: update this return
        
        
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
        // TO DO: write this function.
        T valueOut;
        NODE* temp = getMin(this->root);
        valueOut = temp->value;
        // cout << temp->value << "|||||" <<temp->priority << endl;
        
        return valueOut; // TO DO: update this return
        
        
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    //

    
    bool operator==(const priorityqueue& other) const {
        bool match = _equalityHelper(this->root, other.root);
        return match;
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
