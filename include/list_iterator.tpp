
template <typename T>
LinkedList<T>::Iterator::Iterator(Record *current, LinkedList<T> *list)
	: current(current), prev(current), list(list) {}


template <typename T>
T& LinkedList<T>::Iterator::next(){
	if(this->current->next == nullptr)
		throw std::runtime_error(NEXT_IS_NULL);

	if(this->prev != this->current)
		this->prev = this->current;
	this->current = this->current->next;
	return this->current->item.value();
}

template <typename T>
void LinkedList<T>::Iterator::remove(){
	if(this->prev == this->current) throw std::runtime_error(NOTHING_TO_REMOVE);

	Record *rem = this->current;
	this->prev->next = this->current->next;
	this->current = this->prev;
	delete rem;

	this->list->size--;
}


template <typename T>
bool LinkedList<T>::Iterator::hasNext(){
	return this->current->next != nullptr;
}