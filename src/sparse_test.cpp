#include <functional>
#include <utility>
#include <tuple>
#include <vector>
#include <map>
#include <set>

#include <gtest/gtest.h>

#include "dict.hpp"
#include "sparse.hpp"


using SparseTestParam =
std::vector<std::vector<int>>;

class SparseTest : public testing::TestWithParam<SparseTestParam>{
public:

};

TEST_P(SparseTest,Test){
	Matrix<int> *matrix	= new Matrix<int>(GetParam().size() == 0 ? 0 : GetParam().at(0).size(), GetParam().size());
	for(std::size_t y = 0; y < GetParam().size(); y++) for(std::size_t x = 0; x < GetParam().at(0).size(); x++){
		matrix->set(GetParam().at(y).at(x), x, y);
	}
	auto sparseData = SparseMatrix(*matrix).getData();

	for(std::size_t y = 0; y < GetParam().size(); y++) for(std::size_t x = 0; x < GetParam().at(0).size(); x++){
		int value = GetParam().at(y).at(x);
		if(value == 0)
			ASSERT_FALSE(sparseData->contains({x,y}));
		else
			ASSERT_TRUE(sparseData->contains({x,y}));
	}

	delete matrix;
}

const SparseTestParam sparseTestData[] = {{}, {{1,2,0},{0,3,4}}, {{1,2,0},{0,3,4},{0,0,0}}, {{0,0,0},{0,0,0},{0,0,0}}, {{0}}, {{1}}};
INSTANTIATE_TEST_SUITE_P(, SparseTest, testing::ValuesIn(sparseTestData));

