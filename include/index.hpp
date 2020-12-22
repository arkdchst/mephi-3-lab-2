#pragma once

#include <memory>
#include <string>
#include <stdexcept>

#include "dict.hpp"
#include "list.hpp"

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

std::unique_ptr<HashTable<std::string, int>> create_index_w(const std::string &text, int max_count){
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

std::unique_ptr<HashTable<std::string, int>> create_index_s(const std::string &text, int max_count){
	int count = 0;
	int page = 1;
	auto dict = std::make_unique<HashTable<std::string, int>>();

	auto words = split(text);
	auto it = words.begin();

	while(it.hasNext()){
		std::string word = it.next();
		int len = word.size();

		if(len > max_count)throw std::runtime_error("word is to large");

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