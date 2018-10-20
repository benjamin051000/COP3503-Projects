#pragma once
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
struct LinkedList {

	struct Node {
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

		Node(T input) {
			data = input;
			next = nullptr;
			prev = nullptr;
		}
	};

	unsigned int listSize;
	Node* head;
	Node* tail;

	void set(const LinkedList& rhs);
	
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
	bool RemoveAt(unsigned int index);
	void Clear();

	/*=====Operators=====*/
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T>& operator=(const LinkedList<T> &rhs);
};



template<typename T>
void LinkedList<T>::set(const LinkedList& rhs) {
	Node* current = head;

	rhs->head = this->head;
	
	while (current != nullptr) {
		rhs.AddTail(current->data);

		current = current->next;
	}
}

template<typename T>
LinkedList<T>::LinkedList() {
	listSize = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	//store a pointer to the next one
	//delete what comes before it
	Node* current = head;

	if (current == nullptr) {
		return;
	}

	while (current->hasNext()) {
		current = current->next;
		delete current->prev;
	}
	//finally, delete it
	delete current;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) {
	set(rhs);
}

template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	return GetNode(index)->data;
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	return GetNode(index)->data;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	if (this->listSize != rhs->listSize) {
		return false;
	}
	for (int i = 0; i < listSize; i++) {
		if (this[i]->data != rhs[i]->data) {
			return false;
		}
	}
	return true;
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
	while (current != nullptr) { //Probably won't check the last Node
		if (current->data == value) {
			outData.push_back(current);
		}
		current = current->next;
	}
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
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
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	Node* node = head;

	//If index is out of bounds...
	if (index >= listSize) {
		throw - 1;
	}

	//Iterate through the Linked List to get to the right node
	for (unsigned int i = 0; i < index; i++) {
		node = node->next;
	}

	return node;
}

template<typename T>
void LinkedList<T>::AddHead(const T& data) {
	if (listSize == 0) {
		head = new Node(data);
		tail = head; //&head ?
	}
	else {
		head->prev = new Node(data);
		head->prev->next = head;
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
		tail->next->prev = tail;
		tail = tail->next;
	}
	listSize++;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (int i = count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
	
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		AddTail(data[i]);
	}
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	Node* newNode = new Node(data);
	if (node->next == nullptr) {
		node->next = newNode;
	}
	else {
		Node* nextNode = node->next;
		node->next = newNode;
		newNode->prev = node;
		
		newNode->next = nextNode;
		if (nextNode != nullptr) {
			nextNode->prev = newNode;
		}
	}
	listSize++;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	Node* newNode = new Node(data);
	if (node->prev == nullptr) {
		node->prev = newNode;
	}
	else {
		Node* prevNode = node->prev;
		node->prev = newNode;
		newNode->next = node;

		newNode->prev = prevNode;
		if (prevNode != nullptr) {
			prevNode->next = newNode;
		}
	}
	listSize++;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	//This will actually insert it at index - 1.
	if (index > listSize) {
		throw -1;
	}

	//Node* newNode = new Node(data);
	//use another method
	InsertAfter(GetNode(index - 1), data); //trash
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	Node* node = head;

	//If index is out of bounds...
	if (index >= listSize) {
		throw -1;
	}

	//Iterate through the Linked List to get to the right node
	for (unsigned int i = 0; i < index; i++) {
		node = node->next;
	}

	return node;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tail;
}

template<typename T>
bool LinkedList<T>::RemoveHead() {
	if (listSize == 0) {
		return false;
	}

	if (head->hasNext()) { //doesn't delete tail!
		head = head->next;
		delete head->prev;
		head->prev = nullptr;

		listSize--;
		return true;
	}
	if (listSize == 1) {
		delete head;
		head = nullptr;
		tail = nullptr;
		listSize--;
		return true;
	}
	//Should this delete a single node, which is the head?
	return false;
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
	if (listSize == 0) {
		return false;
	}

	if (tail->hasPrev()) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;

		listSize--;
		return true;
	}

	if (listSize == 1) {
		delete tail;
		head = nullptr;
		tail = nullptr;
		listSize--;
		return true;
	}
	return false;
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	unsigned int numRemoved = 0;
	Node* current = head;

	while (current != nullptr) {
		if (current->data == data) {
			//remove it
			Node* nextNode = current->next;
			Node* prevNode = current->prev;
			prevNode->next = nextNode;
			nextNode->prev = prevNode;

			delete current;

			numRemoved++;
			current = nextNode;
		}
		else {
			current = current->next;
		}
	}
	listSize -= numRemoved;
	return numRemoved;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) { //broken!
	if (!GetNode(index)) {
		return false;
	}

	Node* current = GetNode(index); //Cannot convert from LL<string> to LL<string>::Node*
	
	if (current->hasNext() && current->hasPrev()) {
		Node* nextNode = current->next;
		Node* prevNode = current->prev;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	}
	listSize--;
	delete current;

	return true;
}

template<typename T>
void LinkedList<T>::Clear() {
	while (RemoveHead()) {}
	listSize = 0;
	head = nullptr;
	tail = nullptr;
}
