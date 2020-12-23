#include <functional>
#include <utility>
#include <tuple>
#include <vector>
#include <map>
#include <set>

#include <gtest/gtest.h>

#include "dict.hpp"
#include "index.hpp"

using ReduceTestParam =
std::pair<
	std::vector<std::pair<
		std::string, int>
	>,
	std::map<
		int, std::set<std::string>
	>
>;
class ReduceTest : public testing::TestWithParam<ReduceTestParam>{
public:

};

TEST_P(ReduceTest,Test){
	auto input = GetParam().first;
	auto expected = GetParam().second;

	IDictionary<std::string,int> *index = new HashTable<std::string,int>();
	for(auto &pair: input){
		index->set(pair.first, pair.second);
	}

	auto output = reduceIndex(index);

	auto it = output->iterator();
	while(it->hasNext()){
		auto key = it->next();
		auto list = output->get(key);

		ASSERT_EQ(expected.at(key).size(), list.getSize());
		auto listit = list.begin();
		while(listit.hasNext()){
			ASSERT_GE(expected.at(key).count(listit.next()), 1);
		}
	}

	delete index;
}

const ReduceTestParam reduceTestData[] = {
	{{{"a", 1}, {"b", 1}, {"c", 1}, {"d", 2}, {"e", 2}}, {{1, {"a", "b", "c"}}, { 2,{"d", "e"}}}},
	{{{"a", 1}, {"b", 2}}, {{1, {"a"}}, { 2,{"b"}}}},
	
};

INSTANTIATE_TEST_SUITE_P(, ReduceTest, testing::ValuesIn(reduceTestData));



using CreateIndexTestParam = 
std::pair<
	std::pair<
		std::pair<std::string,int>, //input
		std::map< //expected
			int, std::set<std::string>
		>
	>,
	std::unique_ptr<IDictionary<std::string, int>> (*)(const std::string &text, int max_count) 
>;
class CreateIndexTest : public testing::TestWithParam<CreateIndexTestParam>{
public:

};

TEST_P(CreateIndexTest,Test){
	auto output = reduceIndex( GetParam().second(GetParam().first.first.first, GetParam().first.first.second).get() );
	auto expected = GetParam().first.second;

	auto it = output->iterator();
	while(it->hasNext()){
		auto key = it->next();
		auto list = output->get(key);

		ASSERT_EQ(expected.at(key).size(), list.getSize());
		auto listit = list.begin();
		while(listit.hasNext()){
			ASSERT_GE(expected.at(key).count(listit.next()), 1);
		}
	}
}

const CreateIndexTestParam createIndexTestData[] = {
	{ {{"one two three four five", 3}, {{1, {"one", "two", "three"}}, { 2, {"four", "five"}}} }, createIndexW},
	{ {{"one two three four five", 10}, {{1, {"one", "two"}}, { 2, {"three", "four"}}, { 3, {"five"}}} }, createIndexS},
	{ {{"one two three four five", 13}, {{1, {"one", "two", "three"}}, { 2, {"four", "five"}} }}, createIndexS},
	{ {{"one two three four five", 12}, {{1, {"one", "two"}}, { 2, {"three", "four"}}, {3, {"five"}} }}, createIndexS}
	
};

INSTANTIATE_TEST_SUITE_P(, CreateIndexTest, testing::ValuesIn(createIndexTestData));


using CreateIndexTestFailParam = 
std::pair<
	std::pair<std::string,int>, //input
	std::unique_ptr<IDictionary<std::string, int>> (*)(const std::string &text, int max_count) 
>;
class CreateIndexTestFail : public testing::TestWithParam<CreateIndexTestFailParam>{
public:

};

TEST_P(CreateIndexTestFail,Test){
	ASSERT_ANY_THROW(std::get<1>(GetParam())(std::get<0>(GetParam()).first, std::get<0>(GetParam()).second));
}

CreateIndexTestFailParam data[] = {{{"one two three four five", 3}, createIndexS}};
INSTANTIATE_TEST_SUITE_P(, CreateIndexTestFail, testing::ValuesIn(data));



