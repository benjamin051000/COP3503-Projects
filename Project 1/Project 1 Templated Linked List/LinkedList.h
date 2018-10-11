#pragma once
#include <vector>

template<typename T>
class LinkedList {

	class Node {
		T value;
		Node* next;

	public:
		Node() { next = nullptr; }
		~Node() { delete next; }
		Node(T input) {
			value = input;
			next = nullptr;
		}
	};

	int listSize;
	Node* head;
	Node* tail;

public:
	/*=====Construction/Destruction=====*/
	LinkedList();
	~LinkedList();

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
	void InsertAfter(Nod* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	/*=====Operators=====*/
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T>& operator=(const LinkedList<T> &rhs);
};

template<typename T>
LinkedList<T>::LinkedList() {
	head = new Node();
	listSize = 1;
}

template<typename T>
LinkedList<T>::~LinkedList() {
}

template<typename T>
void LinkedList<T>::PrintForward() const {
}

template<typename T>
void LinkedList<T>::PrintReverse() const {
}
