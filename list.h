#ifndef LIST_H_
#define LIST_H_


#include <cassert>
#include <cstddef> // for size_t

/**************
 * Class List *
 **************/
template<class T>
class List {
public:
	List();
	List(const List&);
	List& operator=(const List&);
	~List();

	/* Add an element to the end of the list */
	void insert(const T& val);

	/* Returns the last element of the list */
	const T& getTail();
	
	class Iterator;
	Iterator begin() const;
	Iterator end() const;

	size_t size() const;
	bool empty() const;
	Iterator find(const T& val) const;

private:
	class Node;

	Node* _head;
	Node* _tail;
	size_t _size;
};

/********************
 * Class List::Node *
 ********************/

template<class T>
class List<T>::Node {
	Node& operator=(const Node&);
public:
	T _data;
	Node* _next;
	Node(const T& data) :
			_data(data), _next(NULL) {
	}
	Node(const Node& copy) :
			_data(_data), _next(_next) {
	}
};

/************************
 * Class List::Iterator *
 ************************/

template<class T>
class List<T>::Iterator {
	const List<T>* _list;
	int _index;
	List<T>::Node* _node;
	Iterator(const List<T>* list, int index);
	friend class List<T> ;
public:
	T& operator*() const;
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator& it) const;
	bool operator!=(const Iterator& it) const;
	T* operator->() const;
};

/********************************
 * List function implementation *
 ********************************/

template<class T>
List<T>::List() :
		_head(NULL), _tail(NULL), _size(0) {
}

template<class T>
List<T>::List(const List& list) :
		_head(NULL), _tail(NULL), _size(0) {
	List<T>::Node* curr = list._head;
	if (curr) {
		_head = new Node(curr->_data);
		_tail = _head;
		curr = curr->_next;
		_size++;
	}
	while (curr) {
		Node* tmp = new Node(curr->_data);
		_tail->_next = tmp;
		_tail = tmp;
		curr = curr->_next;
		_size++;
	}
}

template<class T>
List<T>& List<T>::operator =(const List& list) {
	if (this == &list) {
		return *this;
	}
	List<T> tmpList;
	try {
		List<T>::Node* curr = list._head;
		if (curr) {
			tmpList._head = new List<T>::Node(curr->_data);
			tmpList._tail = tmpList._head;
			curr = curr->_next;
			tmpList._size++;
		}
		while (curr) {
			List<T>::Node* tmp = new List<T>::Node(curr->_data);
			tmpList._tail->_next = tmp;
			tmpList._tail = tmp;
			curr = curr->_next;
			tmpList._size++;
		}
	} catch (...) {
		// delete tmpList nodes
		while (tmpList._head) {
			List<T>::Node tmp = tmpList._head;
			tmpList._head = tmpList._head->_next;
			delete tmp;
		}
		throw;
	}
	// delete this list nodes
	while (_head) {
		List<T>::Node tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
	_head = tmpList._head;
	_tail = tmpList._tail;
	_size = tmpList._size;
	return *this;
}

template<class T>
List<T>::~List() {
	while (_head) {
		List<T>::Node* tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
}

template<class T>
void List<T>::insert(const T& val) {
	List<T>::Node* node = new List<T>::Node(val);
	if (_tail != NULL) {
		_tail->_next = node;
	} else {
		_head = node;
	}
	_tail = node;
	_size++;
}

template<class T>
const T& List<T>::getTail() {
	return _tail->_data;
}

template<class T>
typename List<T>::Iterator List<T>::begin() const {
	return Iterator(this, 0);
}

template<class T>
typename List<T>::Iterator List<T>::end() const {
	return Iterator(this, _size);
}

template<class T>
size_t List<T>::size() const {
	return _size;
}

template<class T>
bool List<T>::empty() const {
	return _size == 0;
}

/******************************************
 * List::Iterator function implementation *
 ******************************************/

template<class T>
typename List<T>::Iterator List<T>::find(const T& val) const {
	for (List<T>::Iterator it = begin(); it != end(); ++it) {
		if (*it == val) {
			return it;
		}
	}
	return end();
}

template<class T>
List<T>::Iterator::Iterator(const List<T>* list, int index) :
		_list(list), _index(index), _node(list->_head) {
}

template<class T>
T& List<T>::Iterator::operator *() const {
	assert(_index >= 0 && _index < _list->size());
	return _node->_data;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator ++() {
	++_index;
	if(_node != NULL)
		_node = _node->_next;
	return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator ++(int) {
	Iterator res = *this;
	++_index;
	if(_node != NULL)
			_node = _node->_next;
	return res;
}

template<class T>
bool List<T>::Iterator::operator ==(const Iterator& it) const {
	assert(_list == it._list);
	return _index == it._index;
}

template<class T>
bool List<T>::Iterator::operator !=(const Iterator& it) const {
	return !(*this == it);
}

template<class T>
inline T* List<T>::Iterator::operator ->() const {
	assert(_index >= 0 && _index < _list->size());
	return &(_node->_data);
}

#endif /* LIST_H_ */
