
template <typename K, typename V>
HashTableBase<K, V>::HashTableBase() : 
	data(DynamicArray<List<Pair<K, V>>>(size)){}

template <typename K, typename V>
V& HashTableBase<K, V>::get(const K &key){
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while(it.hasNext()){
		auto &pair = it.next();
		if(pair.key == key)
			return pair.value;
	}

	throw KeyNotFoundError();
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
bool HashTableBase<K, V>::contains(const K &key){
	unsigned num = this->hash(key);
	auto it = this->data.get(num).begin();

	while(it.hasNext()){
		auto &pair = it.next();
		if(pair.key == key)
			return true;
	}

	return false;	
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

	throw KeyNotFoundError();
}


template <typename K, typename V>
typename HashTableBase<K,V>::Iterator HashTableBase<K, V>::iterator(){
	return Iterator(this);
}



template <typename K, typename V>
HashTableBase<K,V>::Iterator::Iterator(HashTableBase<K,V> *table) : table(table){}

template <typename K, typename V>
HashTableBase<K,V>::Iterator::~Iterator(){
	if(this->it){
		delete this->it;
		this->it = nullptr;
	}
}


template <typename K, typename V>
K HashTableBase<K,V>::Iterator::next(){
	this->go();

	return this->current();
}

template <typename K, typename V>
bool HashTableBase<K,V>::Iterator::findNext(){
	if(this->initFlag){
		if(this->table->size == 0) return false;
		this->it = new typename List<Pair<K, V>>::Iterator(this->table->data.get(0).begin());

		this->initFlag = false;
	}

	while(!this->it->hasNext()){
		if(this->i + 1 >= this->table->size) return false;
		this->i++;
		if(this->it){
			delete this->it;
			this->it = nullptr;
		}
		this->it = new typename List<Pair<K, V>>:: Iterator(this->table->data.get(this->i).begin());
	}

	return true;
}

template <typename K, typename V>
K HashTableBase<K,V>::Iterator::current(){
	if(this->initFlag) throw std::runtime_error(this->NO_CURRENT_ELEM);

	return this->it->current().key;
}


template <typename K, typename V>
void HashTableBase<K,V>::Iterator::go(){
	if(! this->findNext())
		throw std::runtime_error(this->NO_NEXT_ELEM);

	this->it->go();
}

template <typename K, typename V>
bool HashTableBase<K,V>::Iterator::hasNext(){
	return this->findNext();
}

template <typename V>
class HashTable<int, V> : public HashTableBase<int, V>{
private:
	virtual unsigned hash(int key){
		return key % this->size;
	}
};

template <typename V>
class HashTable<std::string, V> : public HashTableBase<std::string, V>{
private:
	virtual unsigned hash(std::string key){
		return key.size() % this->size;
	}
};
