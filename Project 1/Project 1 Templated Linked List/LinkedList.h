#pragma once
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
struct LinkedList {

	struct Node { //move methods outside?
		T data;
		Node* next;
		Node* prev;

		bool hasNext() {
			return next != nullptr;
		}

		bool hasPrev() {
			return prev != nullptr;
		}

		Node() { 
			next = nullptr;
			prev = nullptr;
		}

		~Node() { 
			//delete next; //maybe we shouldn't delete this, since we need it to delete the following nodes?
			//delete prev;
		}

		Node(T input) { //Is this necessary? Creates a node with data and no connections.
			data = input;
			next = nullptr;
			prev = nullptr;
		}
	};

	unsigned int listSize;
	Node* head;
	Node* tail;

	void set(const LinkedList& rhs);
	T& getElement(unsigned int i);
	
//public:
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

	/*=====Removal=====*/
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(int index);
	void Clear();

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
T& LinkedList<T>::getElement(unsigned int index) {
	Node* node = head;

	//If index is out of bounds...
	if (index >= listSize) {
		throw -1;
	}
	//Iterate through the Linked List to get to the right node
	for (unsigned int i = 0; i < index; i++) {
			node = node->next;
	}
	return node->data;
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
	Node* currentNode = head;
	while (currentNode->hasNext()) {
		currentNode = currentNode->next;
		delete currentNode->prev;
		//delete currentNode->prev->next;
	}
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) {
	set(rhs);
}

template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	return getElement(index);
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	return getElement(index);
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
	while (currentNode->hasPrev()) {
		cout << currentNode->data << endl;
		currentNode = currentNode->prev;
	}
	//Then, print the last node.
	cout << currentNode->data << endl;
}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return listSize;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* current = head;
	while (current->hasNext()) { //Probably won't check the last Node
		if (current->data == value) {
			outData.push_back(current);
		}
		current = current->next;
	}
}

template<typename T>
typename const LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
	Node* current = head;
	while (current->hasNext()) {
		if (current->data == data) {
			return current;
		}
		current = current->next;
	}

	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T & data) {
	Node* currentNode = head;
	while (currentNode->hasNext()) {
		if (currentNode->data == data) {
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	return nullptr;
}

template<typename T>
typename const LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	return NULL;
}

template<typename T>
void LinkedList<T>::AddHead(const T& data) {
	if (listSize == 0) {
		head = new Node(data);
		tail = head; //&head ?
	}
	else {
		head->prev = new Node(data);
		head->prev->next = head; //broken
		head  = head->prev;
	}
	listSize++;
}

template<typename T>
void LinkedList<T>::AddTail(const T& data) {
	if (listSize == 0) {
		tail = new Node(data);
		head = tail;
	}
	else {
		tail->next = new Node(data);
		tail->next->prev = tail; //broken
		tail = tail->next;
	}
	listSize++;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	return NULL;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return head;
}

template<typename T>
typename const LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tail;
}

template<typename T>
typename const LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tail;
}

template<typename T>
bool LinkedList<T>::RemoveHead() { 
	if (head->hasNext()) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		return true;
	}
	//Should this delete a single node, which is the head?
	return false;
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
	if (tail->hasPrev()) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		return true;
	}
	return false;
}
