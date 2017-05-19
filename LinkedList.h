// A class template for holding a linked list.
// The node type is also a class template.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream> // For cout
using namespace std;

//*********************************************
// The ListNode class creates a type used to *
// store a node of the linked list. *
//*********************************************

template <class T>
class DataNode
{
public:
	T value; // Node value
	DataNode<T> *next; // Pointer to the next node
	// Default Constructor
	DataNode()  // if no data is passed to the argument, turn this node into a size tracking node
	{
		value = 0;
		next = nullptr;
	}
	// Constructor
	DataNode(T nodeValue)
	{
		value = nodeValue;
		next = nullptr;
	}
};

//*********************************************
// LinkedList class *
//*********************************************

template <class T>
class LinkedList
{
private:
	DataNode<T> *head;  // pointer to the first node
	DataNode<T> *last; // Pointer to the last node

	//DataNode<int> ListSize;  // one way of tracking the list's size
	int listCount = 0;   // another way of tracking the list's size

protected:
	DataNode<T> *push_front(T newValue)
	{
		// creates a new node, sets nodes value as the sent value
		// sets new node as the first item in the list, and updates head and next node pointers
		//--------
		// insert a node at the front of the list
		DataNode<T> *newNode; // To point to a new node
		// Allocate a new node and store newValue there.
		newNode = new DataNode<T>(newValue);
		// point newNode->next to the old first node and make newNode the first node in the list
		newNode->next = head;
		head = newNode;


		findLastNode();
		listCount++;
		return newNode;
	}

	DataNode<T> *pop_front()
	{
		// deletes the first item in the list, deleteNode() will update the head pointer to point to the new first item
		// then returns a refernce to the updated head pointer
		this->deleteNode(head->value);
		findLastNode();
		return head;
	}
public:
	// Constructor
	LinkedList()
	{
		head = nullptr;
		last = nullptr;
	}
	// Destructor
	~LinkedList();
	// Linked list operations
	void push_end(T);
	void pop_end();
	void insertNodeByValue(T);
	void deleteNode(T);
	void displayList() const;


	void findLastNode()
	{
		DataNode<T> *nodePtr;
		DataNode<T> *nextPtr;
		if (!head)
		{
			last = nullptr;
			return;
		}
		else
		{
			nextPtr = nullptr;
			nodePtr = nullptr;

			// if the first node is the only node in the list, set last to the same as head
			if (head->next == nullptr)
			{
				last = head;
				return;
			}
			else
			{
				nodePtr = head;
				nextPtr = nodePtr->next;
				while (nodePtr->next != nullptr)
				{
					//This is how to not traverse the list
					//nextPtr->next = nodePtr;
					//nodePtr->next = nextPtr;
					last = nodePtr;
					nextPtr = nodePtr->next;
					nodePtr = nextPtr;
				}
				last = nodePtr;
			}

		}
	}
	void emptyTheList()
	{
		int size = this->getListSize();
		for (int count = 0; count < size; count++)
		{
			this->deleteNode(head->value);
		}
	}

	void insertNodeAtIndex(T newValue, int location)
	{
		//  insert node at any location by sending the location as an argument, along with the value to insert also
		//  using this method will NOT SORT THE DATA

		// check location for value errors.  If location is less than 1, set it to 1, and if location is greater than
		// the size of the list, set location to size + 1
		if (location < 1)
		{
			location = 1;
		}
		else if (location >(listCount + 1))
			//else if (location >(listSize.value + 1))
		{
			location = (listCount + 1);
			//location = (listSize.value + 1);
		}

		DataNode<T> *newNode; // To point to a new node
		DataNode<T> *traversingPtr; // To move through the list
		DataNode<T> *previousNode;

		// Allocate a new node and store newValue there.
		newNode = new DataNode<T>(newValue);

		// If there are no nodes in the list make newNode the first node.
		// if head does not exist, head will now point to the memory address of newNode
		if (!head)
			head = newNode;

		else // Otherwise, insert newNode at the desired location.
		{
			// Initialize nodePtr to head of list.
			traversingPtr = head;
			previousNode = nullptr;


			if (location == 1)  // if the location is 1, make newNode the first node in the list, and point newNode->next to the next node
			{
				head = newNode;
				newNode->next = traversingPtr;
			}

			else
			{

				for (int count = 0; count < (location - 1); count++) // keep pushing nodePtr until it gets the to location
				{

					previousNode = traversingPtr;
					traversingPtr = traversingPtr->next;
				}

				previousNode->next = newNode;
				newNode->next = traversingPtr;
			}
		}
		// update list count 
		//ListSize.value++;
		findLastNode();
		listCount++;
	}

	int searchNodes(T searchValue)
	{
		// search the nodes for the value sent
		// if the value is found, return the position and maybe cout the value
		// if the value was not found, return -1, simalar to a binary search

		int listLocation = 0;
		DataNode<T> *nodePtr; // To traverse the list

		// If the list is empty, return -1
		if (!head)
			return -1;

		// if the first node is the value, return its index, 1
		if (head->value == searchValue)
		{
			return 1;
		}
		else
		{
			// Initialize nodePtr to head of list and increment the location counter
			nodePtr = head;
			listLocation++;

			// Skip all nodes whose value member is not equal to searchValue.
			while (nodePtr != nullptr && nodePtr->value != searchValue)
			{
				nodePtr = nodePtr->next;
				listLocation++;
			}

			//  if the value was not found, and the list is at the end, return -1
			if (nodePtr == nullptr)
			{
				return -1;
			}

			// else, return the index of where the value was found
			else
			{
				return listLocation;
			}
		}
	}

	int getListSize()
	{
		// return the number of items in the list
		//return ListSize.value;  // this uses a dummy node's value to track the size
		return listCount;  // this method uses the int listCount variable to track the list size
	}

};


//**************************************************
// appendNode appends a node containing the value *
// passed into newValue, to the end of the list. *
//**************************************************

template <class T>
void LinkedList<T>::push_end(T newValue)
{

	DataNode<T> *newNode; // To point to a new node
	DataNode<T> *nodePtr; // To move through the list

	// Allocate a new node and store newValue there.
	newNode = new DataNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node.
	if (!head)
		head = newNode;
	else // Otherwise, insert newNode at end.
	{
		// Initialize nodePtr to head of list.
		nodePtr = head;

		// Find the last node in the list.
		while (nodePtr->next)
			nodePtr = nodePtr->next;

		// Insert newNode as the last node.
		nodePtr->next = newNode;
	}

	// update the list size
	//ListSize.value++;
	findLastNode();
	listCount++;
}

//---------------------------------------------------
// remove the node at the end of th list
//---------------------------------------------------
template <class T>
void LinkedList<T>::pop_end()
{
	DataNode<T> *nextNode; // To point to next node
	DataNode<T> *nodePtr; // To move through the list
	nodePtr = head;
	nextNode = nodePtr->next;
	while (nextNode->next)
	{
		nodePtr = nextNode;
		nextNode = nodePtr->next;
	}
	nodePtr->next = nullptr;
}
//***************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head. *
//***************************************************

template <class T>
void LinkedList<T>::displayList() const
{
	DataNode<T> *nodePtr; // To move through the list

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr)
	{
		// Display the value in this node.
		//cout << nodePtr->value << endl;
		cout << nodePtr->value;

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}

//**************************************************
// The insertNode function inserts a node with *
// newValue copied to its value member. *
//**************************************************

template <class T>
void LinkedList<T>::insertNodeByValue(T newValue)
{
	DataNode<T> *newNode; // A new node
	DataNode<T> *nodePtr; // To traverse the list
	DataNode<T> *previousNode = nullptr; // The previous node
	// Allocate a new node and store newValue there.
	newNode = new DataNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node.
	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else // Otherwise, insert newNode.
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to nullptr.
		previousNode = nullptr;

		// Skip all nodes whose value is less than newValue.
		while (nodePtr != nullptr && nodePtr->value < newValue)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == nullptr)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
	// update the list size
	//ListSize.value++;
	findLastNode();
	listCount++;
}

//******************************************************
// The deleteNode function searches for a node *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory. *
//******************************************************

template <class T>
void LinkedList<T>::deleteNode(T searchValue)
{
	DataNode<T> *nodePtr; // To traverse the list
	DataNode<T> *previousNode; // To point to the previous node
	// If the list is empty, do nothing.
	if (!head)
		return;

	// Determine if the first node is the one.
	if (head->value == searchValue)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;
		previousNode = nullptr;
		// Skip all nodes whose value member is not equal to searchValue.
		while (nodePtr != nullptr && nodePtr->value != searchValue)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list,
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr->next != nullptr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
		// if the last item in the list is the desired value, set previousNode-> to null and delete nodePtr
		else if (nodePtr->value == searchValue && nodePtr->next == nullptr)
		{
			previousNode->next = nullptr;
			delete nodePtr;
		}
	}
	// update the list size
	//ListSize.value--;
	findLastNode();
	listCount--;
}

//**************************************************
// Destructor *
// This function deletes every node in the list. *
//**************************************************
//
template <class T>
LinkedList<T>::~LinkedList()
{
	DataNode<T> *traversalNodePtr; // To traverse the list
	DataNode<T> *nextNode; // To point to the next node

	// Position nodePtr at the head of the list.
	traversalNodePtr = head;

	// While nodePtr is not at the end of the list...
	while (traversalNodePtr != nullptr)
	{
		// Save a pointer to the next node.
		nextNode = traversalNodePtr->next;

		// Delete the current node.
		delete traversalNodePtr;

		// Position nodePtr at the next node.
		traversalNodePtr = nextNode;
	}
}
#endif