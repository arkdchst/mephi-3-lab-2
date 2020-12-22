#include <iostream>

#include "sparse.hpp"
#include "list.hpp"
#include "index.hpp"


int main(){
	auto dict = create_index_w("one two three four five six seven eight nine ten", 3);

	auto it = dict->iterator();

	while(it.hasNext()){
		std::cout << it.next() << " " << dict->get(it.current()) << std::endl;
	}

	return 0;
}
