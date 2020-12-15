#pragma once

#include <stdexcept>
#include <string>
#include <cstddef>
#include <memory>
#include <optional>


template <typename T>
class LinkedList {
private:
	struct Record{
		std::optional<T> item;
		Record *next = nullptr;
	};
	Record head;
	std::size_t size = 0;
public:
	static const std::string INDEX_OUT_OF_RANGE;
	static const std::string ZERO_SIZE;

	class Iterator;

	LinkedList();
	LinkedList(const T *items, std::size_t size);
	LinkedList(std::size_t size);
	LinkedList(const LinkedList<T> &list);
	virtual ~LinkedList();
	T& getFirst();
	T& getLast();
	T& get(std::size_t index);
	void set(const T &item, std::size_t index);
	std::unique_ptr<LinkedList<T>> getSublist(std::size_t start, std::size_t end);
	std::size_t getSize();
	void append(const T &item);
	void prepend(const T &item);
	void removeAt(std::size_t index);
	void insertAt(const T &item, std::size_t index);
	std::unique_ptr<LinkedList<T>> concat(const LinkedList<T> &list);

	LinkedList<T>::Iterator begin();
};
template <typename T>
const std::string LinkedList<T>::INDEX_OUT_OF_RANGE = "index out of range";
template <typename T>
const std::string LinkedList<T>::ZERO_SIZE = "size is 0";


template <typename T>
class LinkedList<T>::Iterator {
private:
	Record *current = nullptr;
	Record *prev = nullptr;

	LinkedList<T> *list;
public:
	static const std::string NEXT_IS_NULL;
	static const std::string NOTHING_TO_REMOVE;

	Iterator(Record *current, LinkedList<T> *list);

	T& next();
	void remove();
	bool hasNext();
	// void insert(const T &item);
};
template <typename T>
const std::string LinkedList<T>::Iterator::NEXT_IS_NULL = "there is no next element";
template <typename T>
const std::string LinkedList<T>::Iterator::NOTHING_TO_REMOVE = "nothing to remove";


#include "list.tpp"

#include "list_iterator.tpp"