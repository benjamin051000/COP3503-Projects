#pragma once
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class LinkedList {

	struct Node {
		T data;
		Node* next;
		Node* previous;

		bool hasNext() {
			return next != nullptr;
		}

		bool hasPrevious() {
			return next != nullptr;
		}

		Node() { 
			next = nullptr;
			previous = nullptr;
		}
		~Node() { 
			delete next;
			delete previous;
		}
		Node(T input) {
			data = input;
			next = nullptr;
		}
		
	};

	int listSize;
	Node* head;
	Node* tail;

	void set(const LinkedList& rhs);
	
public:
	/*=====Construction/Destruction=====*/
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList& rhs);

	/*=====Accessors=====*/
	void PrintForward() const;
	void PrintReverse() const;
	unsigned int NodeCount() const;
	void FindAll(vector<Node*> &outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;
	
	/*=====Insertion=====*/
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	/*=====Operators=====*/
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T>& operator=(const LinkedList<T> &rhs);
};



template<typename T>
void LinkedList<T>::set(const LinkedList& rhs) {
}

template<typename T>
LinkedList<T>::LinkedList() {
	listSize = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	//delete all the nodes
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) {
	set(rhs);
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList& rhs) {
	set(rhs);
	return *this;
}

template<typename T>
void LinkedList<T>::PrintForward() const {
	Node* currentNode = head;
	while (currentNode->hasNext()) {
		cout << currentNode->data << endl;
		currentNode = currentNode->next;
	}
	//Then, print the last node.
	cout << currentNode->data << endl;
}

template<typename T>
void LinkedList<T>::PrintReverse() const {
	Node* currentNode = tail;
	while (currentNode->hasPrevious()) {
		cout << currentNode->data << endl;
		currentNode = currentNode->previous;
	}
	//Then, print the last node.
	cout << currentNode->previous << endl;
}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return listSize;
}

template<typename T>
void LinkedList<T>::AddHead(const T& data) {
	if (listSize == 0) {
		head = new Node(data);
		tail = head; //&head ?
	}
	else {
		head->previous = new Node(data);
		//head->previous->next = head; //uh does this actually work
		head  = head->previous; //&tail->next ?
	}
	listSize++;
}

template<typename T>
void LinkedList<T>::AddTail(const T& data) {
	if (listSize == 0) {
		tail = new Node(data);
		head = tail; //&tail ?
	}
	else {
		tail->next = new Node(data);
		//tail->next->previous = tail; //uh does this actually work
		tail = tail->next; //&tail->next ?
	}
	listSize++;
}



