#include <memory>
#include <string>
#include <stdexcept>

#include "dict.hpp"
#include "list.hpp"
#include "sort.hpp"
#include "index.hpp"


List<std::string> split(std::string text){
	List<std::string> list;
	auto it = list.begin();

	while(text.size()){
		int pos = text.find(" ");
		if(pos == -1){
			it.insert(text);
			text.clear();
			continue;
		}
		it.insert(text.substr(0, pos));
		text.erase(0, pos + 1);
	}

	return list;
}

std::unique_ptr<IDictionary<std::string, int>> createIndexW(const std::string &text, int max_count){
	int count = 0;
	int page = 1;
	auto dict = new HashTable<std::string, int>();

	auto words = split(text);
	auto it = words.begin();

	while(it.hasNext()){
		if(count >= max_count){
			count = 0;
			page++;
		}

		dict->set(it.next(), page);
		count++;
	}

	return std::unique_ptr<HashTable<std::string,int>>(dict);
}

std::unique_ptr<IDictionary<std::string, int>> createIndexS(const std::string &text, int max_count){
	int count = 0;
	int page = 1;
	auto dict = std::make_unique<HashTable<std::string, int>>();

	auto words = split(text);
	auto it = words.begin();

	while(it.hasNext()){
		std::string word = it.next();
		int len = word.size();

		if(len > max_count) throw WordIsTooLargeError();

		if(count != 0 && count + 1 + len > max_count){
			count = 0;
			page++;
		}

		dict->set(word, page);

		if(count == 0)	count += word.size();
		else			count += 1 + word.size();
	}

	return dict;
}

std::unique_ptr<IDictionary<int, List<std::string>>> reduceIndex(IDictionary<std::string,int> *index){
	auto it = index->iterator();
	ArraySequence<Pair<int, std::string>> arr;

	while(it->hasNext()){
		arr.append({index->get(it->next()), it->current()});
	}

	auto sorted = sort<Pair<int, std::string>>(&arr, [](Pair<int, std::string> a, Pair<int, std::string> b) -> int{return a.key-b.key;});

	auto ptr = std::make_unique<HashTable<int, List<std::string>>>();
	for(std::size_t i = 0; i < sorted->getSize(); i++){
		if(! ptr->contains(sorted->get(i).key)){
			ptr->set(sorted->get(i).key, List<std::string>());
		}

		ptr->get(sorted->get(i).key).prepend(sorted->get(i).value);
	}

	return ptr;
}