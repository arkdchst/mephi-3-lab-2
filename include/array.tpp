#pragma once


template <typename T>
DynamicArray<T>::DynamicArray()
	: size(0) {}

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t size) : size(size) {
	this->data = new T[size]();
}

template <typename T>
DynamicArray<T>::DynamicArray(const T *data, std::size_t size) : DynamicArray(size) {
	for(std::size_t i = 0; i < size; i++)
		this->data[i] = data[i];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &array, std::size_t size) : DynamicArray(size){
	if(size > array.size) throw std::out_of_range(INDEX_OUT_OF_RANGE);

	for(std::size_t i = 0; i < size; i++)
		this->data[i] = array.data[i];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &array) : 
	DynamicArray(array.data, array.size) {}

template <typename T>
DynamicArray<T>::~DynamicArray(){
	delete[] this->data;
	this->size = 0;
}

template <typename T>
T& DynamicArray<T>::get(std::size_t index){
	if(index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);

	return this->data[index];
}

template <typename T>
std::size_t DynamicArray<T>::getSize(){ return this->size; }

template <typename T>
void DynamicArray<T>::set(const T &value, std::size_t index){
	if(index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE);

	this->data[index] = value;
}

template <typename T>
void DynamicArray<T>::resize(std::size_t size){
	T *newData = new T[size];
	for(std::size_t i = 0; i < (this->size > size ? size : this->size); i++)
		newData[i] = data[i];

	delete[] data;
	this->data = newData;

	this->size = size;
}

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T> &arr) const {
	if(this->size != arr.size) return false;

	for(std::size_t i = 0; i < this->size; i++)
		if(this->data[i] != arr.data[i]) return false;
	

	return true;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray &array){
	delete[] this->data;

	this->size = array.size;
	this->data = new T[this->size];

	for(std::size_t i = 0; i < size; i++)
		this->data[i] = array.data[i];

	return *this;
}

