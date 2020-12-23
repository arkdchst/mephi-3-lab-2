#include <iostream>

#include "sequence.hpp"
#include "array.hpp"
#include "sparse.hpp"
#include "menu.hpp"
#include "sort.hpp"

void prettyPrint(HashTable<Point, int> &data){
	auto it = data.iterator();

	ArraySequence<Pair<Point, int>> arrayData;
	while(it->hasNext()){
		arrayData.append({it->next(), data.get(it->current())});
	}

	auto sorted = sort<Pair<Point, int>>(&arrayData, [](Pair<Point, int> a, Pair<Point, int> b) -> int
		{
			if(a.key.x != b.key.x) return a.key.x - b.key.x;
			return a.key.y - b.key.y;
		}

	);

	for(auto i = 0; i < sorted->getSize(); i++){
		auto elem = sorted->get(i);
		std::cout << elem.key.x << " " << elem.key.y << ": " << elem.value << std::endl;
	}
}

int main(){
	int width, height;
	Matrix<int> *matrix;

	std::cout << "enter matrix width: " << std::flush;
	width = readInt(1);

	std::cout << "enter matrix height: " << std::flush;
	height = readInt(1);

	matrix = new Matrix<int>(width, height);

	std::cout << "enter matrix content:" << std::endl;
	for(std::size_t y = 0; y < height; y++) for(std::size_t x = 0; x < width; x++){
		int temp;
		std::cin >> temp;
		matrix->set(temp, x, y);
	}
	std::cout << "\n\n";


	SparseMatrix<int> *sparse = new SparseMatrix(*matrix);
	auto data = sparse->getData();

	prettyPrint(*data);

	return 0;
}
