#pragma once

#include <stdexcept>
#include <string>
#include <cstddef>
#include <memory>


template <typename T>
class List {
private:
	struct Record{
		T *item = nullptr;
		Record *next = nullptr;

		Record(T item, Record *next = nullptr) : next(next) {
			this->item = new T(item);
		}

		Record(Record *next = nullptr)
			: next(next) {}

		~Record(){
			if(item) delete item;
		}
	};
	Record head;
	std::size_t size = 0;
public:
	static const std::string INDEX_OUT_OF_RANGE;
	static const std::string ZERO_SIZE;

	class Iterator;

	List();
	List(const T *items, std::size_t size);
	List(std::size_t size);
	List(const List<T> &list);
	virtual ~List();

	List<T>& operator=(const List<T> &other);

	T& getFirst();
	T& getLast();
	T& get(std::size_t index);
	void set(const T &item, std::size_t index);
	std::unique_ptr<List<T>> getSublist(std::size_t start, std::size_t end);
	std::size_t getSize();
	void append(const T &item);
	void prepend(const T &item);
	void removeAt(std::size_t index);
	void insertAt(const T &item, std::size_t index);
	std::unique_ptr<List<T>> concat(const List<T> &list);


	List<T>::Iterator begin();
};
template <typename T>
const std::string List<T>::INDEX_OUT_OF_RANGE = "index out of range";
template <typename T>
const std::string List<T>::ZERO_SIZE = "size is 0";


template <typename T>
class List<T>::Iterator {
private:
	Record *currentRec = nullptr;
	Record *prevRec = nullptr;

	List<T> *list;
public:
	static const std::string NO_NEXT_ELEM;
	static const std::string NO_CURRENT_ELEM;

	Iterator(Record *currentRec, List<T> *list);

	T& next();
	void go();
	T& current();
	void remove();
	bool hasNext();
	void insert(const T &item);
};
template <typename T>
const std::string List<T>::Iterator::NO_NEXT_ELEM = "there is no next element";
template <typename T>
const std::string List<T>::Iterator::NO_CURRENT_ELEM = "there is no current element";


#include "list.tpp"

#include "list_iterator.tpp"