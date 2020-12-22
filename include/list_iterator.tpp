
template <typename T>
List<T>::Iterator::Iterator(Record *currentRec, List<T> *list)
	: currentRec(currentRec), prevRec(currentRec), list(list) {}


template <typename T>
T& List<T>::Iterator::next(){
	this->go();

	return this->current();
}

template <typename T>
void List<T>::Iterator::go(){
	if(this->currentRec->next == nullptr)
		throw std::runtime_error(this->NO_NEXT_ELEM);

	if(this->prevRec != this->currentRec)
		this->prevRec = this->currentRec;
	this->currentRec = this->currentRec->next;
}

template <typename T>
T& List<T>::Iterator::current(){
	if(this->prevRec == this->currentRec) throw std::runtime_error(this->NO_CURRENT_ELEM);

	return *(this->currentRec->item);
}

template <typename T>
void List<T>::Iterator::remove(){
	if(this->prevRec == this->currentRec) throw std::runtime_error(this->NO_CURRENT_ELEM);

	Record *rem = this->currentRec;
	this->prevRec->next = this->currentRec->next;
	this->currentRec = this->prevRec;
	delete rem;

	this->list->size--;
}

template <typename T>
bool List<T>::Iterator::hasNext(){
	return this->currentRec->next != nullptr;
}

template <typename T>
void List<T>::Iterator::insert(const T &item){
	Record *newRec = new Record(item, currentRec->next);
	this->currentRec->next = newRec;

	this->list->size++;

	this->next();
}
