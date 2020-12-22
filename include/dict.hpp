#pragma once

#include <string>
#include <stdexcept>

#include "array.hpp"
#include "list.hpp"

class KeyNotFoundError : std::runtime_error{
public:
	KeyNotFoundError() : std::runtime_error("key not found"){}
};

template <typename K, typename V>
class IDictionary{
public:
	virtual ~IDictionary() = default;

	virtual V& get(const K&) = 0;
	virtual void set(const K&, const V&) = 0;
	virtual bool contains(const K&) = 0;
	virtual void remove(const K&) = 0;
};

template <typename K, typename V>
struct Pair{
	K key;
	V value;
};

template <typename K, typename V>
class HashTableBase : public IDictionary<K,V> {
protected:
	std::size_t size = 3;
	DynamicArray<List<Pair<K, V>>> data;

	virtual unsigned hash(K) = 0;
public:
	class Iterator;

	HashTableBase();

	virtual V& get(const K&) override;
	virtual void set(const K&, const V&) override;
	virtual bool contains(const K&) override;
	virtual void remove(const K&) override;

	Iterator iterator();
};

template <typename K, typename V>
class HashTableBase<K,V>::Iterator{
protected:
	bool initFlag = true;
	std::size_t i = 0; //number of current bucket
	typename List<Pair<K, V>>:: Iterator *it = nullptr; //iterator inside current list

	HashTableBase<K,V> *table;

	bool findNext();
public:
	static const std::string NO_NEXT_ELEM;
	static const std::string NO_CURRENT_ELEM;

	Iterator(HashTableBase<K,V> *table);
	virtual ~Iterator();

	K next();
	void go();
	K current();
	bool hasNext();
};
template <typename K, typename V>
const std::string HashTableBase<K,V>::Iterator::NO_NEXT_ELEM = "there is no next element";
template <typename K, typename V>
const std::string HashTableBase<K,V>::Iterator::NO_CURRENT_ELEM = "there is no current element";


template <typename K, typename V>
class HashTable : public HashTableBase<K, V>{};


#include "dict.tpp"