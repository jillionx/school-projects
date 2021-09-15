///////////////////////////////////////////////////////////////////////////////
// Author: Mark Dencler
// Description: This is the object specification for an "Ordered Linked List".
// Overloaded operator '+' allows element insertions.
// Overloaded operator '-' allows for deletions.
///////////////////////////////////////////////////////////////////////////////

// PRE-PROCESSOR
#pragma once

// CONSTANTS
const int OK = 1;
const int NOT_FOUND = 2;
const int ERROR_MEMORY = -1;

// NODE SPECIFICATION
// Description: Each linked OOLNode structure contains the information
// for a single element in the list.
struct OOLNode {
	int payload;
	OOLNode* next;
};

// OBJECT SPECIFICATION
// Description: Object interface specification for
// "Operator-overloaded Ordered Linked List" (OOLList).
class OOLList {
private:
	OOLNode* start;

public:
	// Description: Initializes the list with zero elements.
	OOLList();

	// Description: Returns the number of elements currently in the list.
	int getListSize();

	// Description: Returns the number of bytes being used in the heap
	// by the list.
	int getListSizeInBytes();

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
	int getListElements(int* populateMeWithElements);

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
	int addElement(int addMe);

	// Description: Provides support identical to 'addElement()' with
	// an overloaded '+' operator.
	int operator+(int addMe);

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
	bool deleteElement(int deleteMe);

	// Description: Provides support identical to 'deleteElement()' with
	// an overloaded '-' operator.
	bool operator-(int deleteMe);
};