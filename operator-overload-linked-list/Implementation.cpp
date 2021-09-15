/*Author: Jill Russell
CIS 221 - Project 3
Operator Overloaded Linked List
--Implementation File
*/

#include <iostream>
#include <iomanip>
#include "Specification.h"

using namespace std;

// Description: Initializes the list with zero elements.
OOLList::OOLList() {
	this->start = nullptr;
}

// Description: Returns the number of elements currently in the list.
int OOLList::getListSize() {
	//counts number of elements in list with i value, commented out lines can also display values
	OOLNode* iterator = this->start;
	int i = 0; //for looping
	if (iterator == nullptr) {
		cout << "The list is EMPTY..." << endl;
	}
	else {
		//cout << "BEGINNING OF LIST" << endl;
	while (iterator != nullptr) {
			i++;
			//cout << iterator->payload << " ";
			iterator = iterator->next;
		}
		cout << i << " elements in list" << endl;
		//cout << endl << "END OF LIST" << endl;
	}
	return 0;
}

// Description: Returns the number of bytes being used in the heap
// by the list.
int OOLList::getListSizeInBytes() {
	OOLNode* iterator = this->start;
	int size = 0;
	while (iterator != nullptr) {
		size = size + sizeof(iterator);
		iterator = iterator->next;
	}
	cout << size << " bytes being used by the list" << endl << endl;

	return size;
}

// Description: Places the payload contents of the list in the
// array referenced by 'populateMeWithElements'.
// Returns the number of elements that were placed
// in the provided memory location.
// Precondition: Enough memory has been allocated to the provided
// memory location to hold the full contents
// of the list.
// Postcondition: The memory allocated for 'populateMeWithElements'
// has been deallocated after the completion of
// this method call.
int OOLList::getListElements(int* populateMeWithElements) {
	OOLList getList;
	OOLNode* iterator = this->start;
	int numElements = 0;

	for (int i = 0; iterator != nullptr; i++) {
		populateMeWithElements[i] = iterator->payload;
		iterator = iterator->next;
		numElements++;
	}
	cout << endl;
	return numElements;
}

// Description: Inserts the value 'addMe' into the list.
// Returns 'OK' if the element was successfully added.
// Returns 'ERROR_MEMORY' if the node could not
// be created.
// Postcondition: The elements contained in the list are in
// incremental order.
// ---------- BEHAVIOR EXAMPLE --------------------------------------------
// S-StartOfList N-EndOfList (*)-NewValue
// Insert (5) in S-N => S-(5)-N
// Insert (5) in S-6-7-N => S-(5)-6-7-N
// Insert (5) in S-4-7-N => S-4-(5)-7-N
// Insert (5) in S-3-4-N => S-3-4-(5)-N
// Insert (5) in S-5-7-N => S-(5)-5-7-N
// Insert (5) in S-4-5-5-7-N => S-4-(5)-5-5-7-N
// Insert (5) in S-4-5-5-N => S-4-(5)-5-5-N
int OOLList::addElement(int addMe) {
	// Make the new NODE
	OOLNode* newNode = nullptr;
	newNode = new(OOLNode);
	if (newNode == nullptr) {
		return false;
	}
	newNode->payload = addMe;
	newNode->next = nullptr;

	// The list is empty.
	if (this->start == nullptr) {
		this->start = newNode;
		return true;
	}

	// When list has one or more elements.
	else {
		OOLNode* seeker = this->start;
		//
		if (seeker->payload > newNode->payload) {
			newNode->next = this->start;
			this->start = newNode;
			return true;
		}
		// Will run until the seeker reaches the end, or when it reaches a value greater than addMe
		while (seeker->next != nullptr && seeker->next->payload < newNode->payload) {
			seeker = seeker->next;
		}
		newNode->next = seeker->next;
		seeker->next = newNode;
		return true;
	}
}

// Description: Provides support identical to 'addElement()' with
// an overloaded '+' operator.
int OOLList::operator+(int addMe) {
	// Make the new NODE
	OOLNode* newNode = nullptr;
	newNode = new(OOLNode);
	if (newNode == nullptr) {
		return false;
	}
	newNode->payload = addMe;
	newNode->next = nullptr;

	// The list is empty.
	if (this->start == nullptr) {
		this->start = newNode;
		return true;
	}

	// When list has one or more elements.
	else {
		OOLNode* seeker = this->start;
		//
		if (seeker->payload > newNode->payload) {
			newNode->next = this->start;
			this->start = newNode;
			return true;
		}
		// Will run until the seeker reaches the end, or when it reaches a value greater than addMe
		while (seeker->next != nullptr && seeker->next->payload < newNode->payload) {
			seeker = seeker->next;
		}
		newNode->next = seeker->next;
		seeker->next = newNode;
		return true;
	}
}

// Description: Deletes the first instance of an element containing
// the value 'deleteMe' in the list.
// Returns 'OK' if the element was successfully deleted.
// Returns 'NOT_FOUND' if an element containing the
// specified value could not be found.
// Postcondition: The elements contained in the list are in
// incremental order.
//
// ---------- BEHAVIOR EXAMPLE --------------------------------------------
// S-StartOfList N-EndOfList (*)-DeletionTarget
// Delete (5) in S-N => S-N => Return 'false'
// Delete (5) in S-6-N => S-6-N => Return 'false'
// Delete (5) in S-(5)-N => S-N => Return 'true'
// Delete (5) in S-(5)-5-N => S-5-N => Return 'true'
// Delete (5) in S-(5)-6-N => S-6-N => Return 'true'
// Delete (5) in S-6-(5)-N => S-6-N => Return 'true'
// Delete (5) in S-(5)-6-5-N => S-6-5-N => Return 'true'
// Delete (5) in S-(5)-5-5-N => S-5-5-N => Return 'true'
bool OOLList::deleteElement(int deleteMe) {
	OOLNode* iterator = this->start;

	//if list is empty, there is nothing to delete
	if (iterator == nullptr) {
		return false;
	}

	//looks for a value equal to deleteMe and deletes it
	else if (iterator != nullptr && iterator->payload == deleteMe) {
		OOLNode* deleteThisOne = this->start;
		deleteMe = this->start->payload;
		this->start = this->start->next;
		delete deleteThisOne;
		return true;
	}

	//returns false if no values equal to deleteMe are found
	else return false;
}

// Description: Provides support identical to 'deleteElement()' with
// an overloaded '-' operator.
bool OOLList::operator-(int deleteMe) {
	OOLNode* iterator = this->start;

	//if list is empty, there is nothing to delete
	if (iterator == nullptr) {
		return false;
	}

	//looks for a value equal to deleteMe and deletes it
	else if (iterator != nullptr && iterator->payload == deleteMe) {
		OOLNode* deleteThisOne = this->start;
		deleteMe = this->start->payload;
		this->start = this->start->next;
		delete deleteThisOne;
		return true;
	}

	//returns false if no values equal to deleteMe are found
	else return false;
}