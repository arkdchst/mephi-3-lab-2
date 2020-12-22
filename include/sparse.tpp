
template <typename T>
SparseMatrix<T>::SparseMatrix(Matrix<T> matrix, T zero) : zero(zero) {
	this->data = new HashTable<Point, T>();

	this->width = matrix.getWidth();
	this->height = matrix.getHeight();

	for(std::size_t i = 0; i < this->width; ++i) for(std::size_t j = 0; j < this->height; ++j) {
		T &item = matrix.get(i, j);
		if(item != zero)
			this->data->set({i, j}, item);
	}
}

template <typename T>
SparseMatrix<T>::SparseMatrix(T zero)
	: zero(zero){}

template <typename T>
SparseMatrix<T>::~SparseMatrix(){
	delete this->data;
}


template <typename T>
void SparseMatrix<T>::set(const T &item, std::size_t x, std::size_t y){
	if(item != this->zero)
		this->data->set(Point{.x = x, .y = y}, item);
}

template <typename T>
T& SparseMatrix<T>::get(std::size_t x, std::size_t y){
	return this->data->get(Point{.x = x, .y = y}); //throws error if element is zero
}

template <typename T>
std::size_t SparseMatrix<T>::getWidth() const {
	return this->width;
}

template <typename T>
std::size_t SparseMatrix<T>::getHeight() const {
	return this->height;
}

template <typename T>
bool SparseMatrix<T>::isZero(std::size_t x, std::size_t y) const {
	return ! this->data->contains({x,y});
}

template <typename T>
std::unique_ptr<HashTable<Point, T>> SparseMatrix<T>::getData(){
	return std::make_unique<HashTable<Point, T>>(*this->data);
}
