
#include "array.hpp"
#include "list.hpp"

template <typename K, typename V>
class IDictionary{
public:
	virtual V& get(const K&) = 0;
	virtual void set(const K&, const V&) = 0;
	// virtual bool contains(const K&) = 0;
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
	int size = 3;
	DynamicArray<LinkedList<Pair<K, V>>> data;

	virtual unsigned hash(K) = 0;
public:
	HashTableBase();

	virtual V& get(const K&);
	virtual void set(const K&, const V&);
	// virtual bool contains(const K&);
	virtual void remove(const K&);
};

template <typename K, typename V>
HashTableBase<K, V>::HashTableBase() : 
	data(DynamicArray<LinkedList<Pair<K, V>>>(size)){}

template <typename K, typename V>
V& HashTableBase<K, V>::get(const K &key){
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while(it.hasNext()){
		auto &pair = it.next();
		if(pair.key == key)
			return pair.value;
	}
}

template <typename K, typename V>
void HashTableBase<K, V>::set(const K &key, const V &value){
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while(it.hasNext()){
		auto &pair = it.next();
		if(pair.key == key){
			pair.value = value;
			return;
		}
	}

	this->data.get(num).prepend(Pair<K,V>{.key=key, .value=value});
}

template <typename K, typename V>
void HashTableBase<K, V>::remove(const K &key){
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while(it.hasNext()){
		auto &pair = it.next();
		if(pair.key == key){
			it.remove();
			return;
		}
	}
}


template <typename K, typename V>
class HashTable : public HashTableBase<K, V>{};

template <typename V>
class HashTable<int, V> : public HashTableBase<int, V>{
private:
	virtual unsigned hash(int key){
		return key % this->size;
	}
};