#pragma once

template <typename T>
LinkedList<T>::LinkedList()
	: size(0){}

template <typename T>
LinkedList<T>::LinkedList(const T *items, std::size_t size) : LinkedList() {
	Record *ptr = &(this->head);
	for(std::size_t i = 0; i < size; ++i){
		ptr->next = new Record{.item=items[i]};
		ptr = ptr->next;
	}

	this->size = size;
}

template <typename T>
LinkedList<T>::LinkedList(std::size_t size) : LinkedList() {
	Record *ptr = &(this->head);
	for(std::size_t i = 0; i < size; i++){
		ptr->next = new Record{.item=T()};
		ptr = ptr->next;
	}

	this->size = size;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list){
	const Record *other = &(list.head);
	Record *ptr = &(this->head);

	while(other->next != nullptr){
		ptr->next = new Record{.item=other->next->item};

		other = other->next;
		ptr = ptr->next;
	}

	this->size = list.size;
}

template <typename T>
LinkedList<T>::~LinkedList(){
	Record *ptr = this->head.next;
	Record *next;
	while(ptr != nullptr){
		next = ptr->next;
		delete ptr;
		ptr = next;
	}

	this->size = 0;
}


template <typename T>
T& LinkedList<T>::getFirst(){
	if(this->size == 0) throw std::length_error(ZERO_SIZE);

	return *(this->head.next->item);
}

template <typename T>
T& LinkedList<T>::getLast(){
	if(this->size == 0) throw std::length_error(ZERO_SIZE);

	Record *ptr = &(this->head);
	while(ptr->next != nullptr) ptr = ptr->next;
	return *(ptr->item);
}

template <typename T>
T& LinkedList<T>::get(std::size_t index){
	if(index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);


	Record *ptr = &(this->head);
	for(std::size_t i = 0; i < index + 1; i++){
		ptr = ptr->next;
	}

	return *(ptr->item);
}

template <typename T>
void LinkedList<T>::set(const T &item, std::size_t index){
	if(index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);


	Record *ptr = &(this->head);
	for(std::size_t i = 0; i < index + 1; i++){
		ptr = ptr->next;
	}

	ptr->item = item;
}

template <typename T>
std::unique_ptr<LinkedList<T>> LinkedList<T>::getSublist(std::size_t start, std::size_t end){ //end excluding
	if(!(0 <= start && start <= end && end <= this->size)){
		if(start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);
		if(end > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);
		if(start > end) throw std::logic_error("end must be not less than start");
	}

	LinkedList<T> *newList = new LinkedList<T>();


	Record *ptr = &(this->head);
	Record *newPtr = &(newList->head);

	for(std::size_t i = 0; i < start; i++) ptr = ptr->next;

	for(std::size_t i = 0; i < end - start; i++){
		newPtr->next = new Record{.item = ptr->next->item};

		ptr = ptr->next;
		newPtr = newPtr->next;
	}

	newList->size = end - start;

	return std::unique_ptr<LinkedList<T>>(newList);
}

template <typename T>
std::size_t LinkedList<T>::getSize(){ return this->size; }

template <typename T>
void LinkedList<T>::append(const T &item){
	Record *ptr = &(this->head);
	while(ptr->next != nullptr) ptr = ptr->next;

	ptr->next = new Record{.item=item};

	this->size++;
}

template <typename T>
void LinkedList<T>::prepend(const T &item){
	Record *newRec = new Record{.item=item, .next=this->head.next};
	this->head.next = newRec;

	this->size++;		
}

template <typename T>
void LinkedList<T>::removeAt(std::size_t index){
	if(index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);

	Record *ptr = &(this->head);
	for(std::size_t i = 0; i < index; i++) ptr = ptr->next;

	Record *rem = ptr->next;
	ptr->next = rem->next;

	delete rem;

	this->size--;
}

template <typename T>
void LinkedList<T>::insertAt(const T &item, std::size_t index){
	if(index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);


	Record *ptr = &(this->head);
	for(std::size_t i = 0; i < index; i++) ptr = ptr->next;

	Record *newRec = new Record{.item = item, .next = ptr->next};
	ptr->next = newRec;

	this->size++;
}

template <typename T>
std::unique_ptr<LinkedList<T>> LinkedList<T>::concat(const LinkedList<T> &list){
	Record *ptr1 = &(this->head);
	const Record *ptr2 = &(list.head);

	LinkedList<T> *newList = new LinkedList<T>();
	Record *ptr = &(newList->head);
	while(ptr1->next != nullptr){
		ptr->next = new Record{.item=ptr1->next->item};

		ptr1 = ptr1->next;
		ptr = ptr->next;
	}
	while(ptr2->next != nullptr){
		ptr->next = new Record{.item=ptr2->next->item};

		ptr2 = ptr2->next;
		ptr = ptr->next;
	}

	newList->size = this->size + list.size;
	return std::unique_ptr<LinkedList<T>>(newList);
}


template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin(){
	return LinkedList<T>::Iterator(&(this->head), this);
}