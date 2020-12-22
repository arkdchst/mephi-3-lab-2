#include <memory>
#include <cstddef>

#include "dict.hpp"
#include "matrix.hpp"

struct Point{
	std::size_t x;
	std::size_t y;

	bool operator==(const Point &other){
		return this->x == other.x && this->y == other.y;
	}
};

template <typename V>
class HashTable<Point, V> : public HashTableBase<Point, V>{
private:
	virtual unsigned hash(Point key){
		return (key.x + key.y) % this->size;
	}
};

template <typename T>
class SparseMatrix : IMatrix<T>{
private:
	HashTable<Point, T> *data;

	std::size_t width, height;

	const T zero;
public:

	SparseMatrix(Matrix<T>, T zero = T()); //convert Matrix to SparseMatrix
	SparseMatrix(T zero);
	virtual ~SparseMatrix();

	virtual T& get(std::size_t x, std::size_t y) override;
	virtual void set(const T&, std::size_t x, std::size_t y) override;

	virtual std::size_t getWidth() const override;
	virtual std::size_t getHeight() const override;

	bool isZero(std::size_t x, std::size_t y) const;

	std::unique_ptr<HashTable<Point, T>> getData();
};


#include "sparse.tpp"