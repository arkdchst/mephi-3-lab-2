#pragma once

#include <stdexcept>
#include <string>
#include <cstddef>

template <typename T> class DynamicArray{
private:
	T *data = nullptr;
	std::size_t size = 0;
public:
	const std::string INDEX_OUT_OF_RANGE = "index out of range";

	DynamicArray();
	DynamicArray(std::size_t size);
	DynamicArray(const T *data, std::size_t size);
	DynamicArray(const DynamicArray<T> &array, std::size_t size);
	DynamicArray(const DynamicArray<T> &array);
	virtual ~DynamicArray();
	T& get(std::size_t index);
	std::size_t getSize();
	void set(const T &value, std::size_t index);
	void resize(std::size_t size);
	bool operator==(const DynamicArray<T> &arr) const;
	DynamicArray<T>& operator=(const DynamicArray &array);
};


#include "array.tpp"