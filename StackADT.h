#ifndef STACKADT_H
#define STACKADT_H
#include <iostream>
#include"LinkedList.h"

//using namespace std;


template <class T>
class StackList :protected LinkedList<T>
{
private:
	//DataNode<T> *head;
	DataNode<T> *topItem;  // pointer to the top of the stack, aka last item entered in

public:
	StackList()
	{
		//  constructor
		//head = nullptr;
		topItem = nullptr;
	}

	void push(T value)
	{
		// put the new item on the top of the stack, aka add new node and make the new node the first item
		// update topItem to point to the new item that was added

		topItem = this->push_front(value);
	}

	void pop()
	{
		// checks for an empty stack first, if stack is empty print out the message and return
		// else, print out the item on the top of the stack, delete the node, 
		// and set the top pointer to the item that now sits on the top of the stack

		if (!topItem)
		{
			//std::cout << "error: the stack is empty";
			return;
		}
		else
		{
			//cout << topItem->value;
			topItem = this->pop_front();
		}
	}

	T peek()
	{
		return topItem->value;
	}

	void emptyTheStack()
	{
		// delete all items in the list
		this->emptyTheList();
	}

	int getStackSize()
	{
		// return the size of the stack as an <int>
		return this->getListSize();
	}

	void displayStack()
	{
		// print out all items in the stack
		this->displayList();
	}

	bool isEmpty()
	{
		// return true if the stack is empty, else return false
		if (!topItem)
			return true;

		else
			return false;
	}
};


#endif