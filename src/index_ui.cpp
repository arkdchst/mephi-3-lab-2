#include <iostream>
#include <random>
#include <time.h>

#include "menu.hpp"
#include "sparse.hpp"
#include "list.hpp"
#include "sort.hpp"
#include "index.hpp"

std::string randomString(unsigned count, unsigned len_from, unsigned len_to){
	srand(time(0));

	int letters_num = 26;
	char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',};

	std::string str;
	for(auto i = 0; i < count; i++){
		int len = rand() % (len_to - len_from + 1) + len_from;

		for(auto j = 0; j < len; j++){
			str += letters[rand() % letters_num];
		}
		if(i != count - 1) //don't add space in the end
			str += ' ';
	}

	return str;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char> &cout, List<std::string> &list){
	auto it = list.begin();
	while(it.hasNext()){
		cout << it.next() << " ";
	}
	return cout;
}

void printIndex(std::string text, int what, int maxCount){
	std::cout << std::endl;

	std::unique_ptr<IDictionary<int, List<std::string>>> index;
	if(what == 0){
		index = reduceIndex( createIndexW(text, maxCount).get() );
	}
	else if(what == 1){
		try{		
			index = reduceIndex( createIndexS(text, maxCount).get() );
		}catch(const WordIsTooLargeError &e){
			std::cout << "word is too large\n" << std::endl;
			return;
		}

	}
	auto it = index->iterator();

	ArraySequence<Pair<int, List<std::string>>> arrayData;
	while(it->hasNext()){
		arrayData.append({it->next(), index->get(it->current())});
	}

	auto sorted = sort<Pair<int, List<std::string>>>(&arrayData, [](Pair<int, List<std::string>> a, Pair<int, List<std::string>> b){return a.key - b.key;});

	for(auto i = 0; i < sorted->getSize(); i++){
		auto elem = sorted->get(i);
		std::cout << elem.key << " " << elem.value << std::endl;
	}

	std::cout << std::endl;

}

int main(){
	TextInput textItem("enter text", "");
	IntInput maxCount("max count", 1, 1);
	ChoiceInput what("max count of what", {"words", "characters"}, 0);

		IntInput wordCount("word count", 1, 1);
		IntInput wordLenFrom("word length from", 1, 1);
		IntInput wordLenTo("word length to", 1, 1);
		Action generate("generate text", [&]() {
			int from = wordLenFrom.getValue();
			int to = wordLenTo.getValue();
			if(from > to) std::cout << "\"from\" is greater than \"to\"\n" << std::endl;
			else
				textItem.setValue(randomString(wordCount.getValue(), from, to));
		});
	Menu generateMenu("generate text", {&wordCount, &wordLenFrom, &wordLenTo, &generate}, false);

	Action createIndex("create index", [&]() {printIndex(textItem.getValue(), what.getValue(), maxCount.getValue());});
	Menu mainMenu("root", {&textItem, &maxCount, &what, &generateMenu, &createIndex}, true);
	mainMenu.enter();

	return 0;
}
