// #include "array.hpp"
#include "list.hpp"

#define BOOST_TEST_MODULE tests
#include <boost/test/included/unit_test.hpp>

// BOOST_TEST_DONT_PRINT_LOG_VALUE( DynamicArray<int> )
BOOST_TEST_DONT_PRINT_LOG_VALUE( LinkedList<int> )



// BOOST_AUTO_TEST_CASE(dynamic_array){
// 	int initArr1[] = {1,2,3,4,5};
// 	int initArr2[] = {0,2,3,4,5,6};
// 	int initArr3[] = {0,2,3,4};

// 	DynamicArray<int> arr1(initArr1, 5);

// 		BOOST_CHECK_THROW(DynamicArray<int>(-1), std::exception);
// 		BOOST_CHECK_THROW(arr1.get(-1), std::exception);
// 		BOOST_CHECK_THROW(arr1.get(5), std::exception);

// 		BOOST_TEST(arr1 == DynamicArray<int>(arr1));
// 		BOOST_TEST(arr1 == DynamicArray<int>(arr1, 5));
// 		BOOST_TEST(DynamicArray<int>() == DynamicArray<int>((int*)0, 0));
// 		BOOST_TEST(arr1.get(0) == 1);
// 		BOOST_TEST(arr1.get(3) == 4);
// 		BOOST_TEST(arr1.get(4) == 5);
// 		BOOST_TEST(arr1.getSize() == 5);


// 		BOOST_REQUIRE_THROW(arr1.set(5, 5), std::exception);
// 		BOOST_REQUIRE_THROW(arr1.resize(-6), std::exception);

// 	arr1.resize(6);
// 	arr1.set(0, 0);
// 	arr1.set(6, 5);
// 		BOOST_TEST(arr1 == DynamicArray<int>(initArr2, 6));
// 	arr1.resize(4);
// 		BOOST_TEST(arr1 == DynamicArray<int>(initArr3, 4));
// }

BOOST_AUTO_TEST_CASE(linked_list){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,0};
	int initArr5[] = {0,1,2,3,5,0,-1};
	int initArr6[] = {0,1,2,3,5,0,1,2,3,5};

	LinkedList<int> list1(initArr1, 4);	

		BOOST_CHECK_THROW(list1.get(4), std::exception);
		BOOST_CHECK_THROW(LinkedList<int>().getFirst(), std::exception);
		BOOST_CHECK_THROW(LinkedList<int>().getLast(), std::exception);

		BOOST_TEST(list1 == LinkedList<int>(list1));
		BOOST_TEST(LinkedList<int>() == LinkedList<int>((int*)0, 0));
		BOOST_TEST(list1.get(0) == 1);
		BOOST_TEST(list1.getFirst() == 1);
		BOOST_TEST(list1.get(2) == 3);
		BOOST_TEST(list1.get(3) == 5);
		BOOST_TEST(list1.getLast() == 5);
		BOOST_TEST(list1.getSize() == 4);

		BOOST_REQUIRE_THROW(list1.insertAt(4, 5), std::exception);

	list1.prepend(0);
	list1.append(6);
	list1.insertAt(-1,0);
	list1.insertAt(7,7);
	list1.insertAt(4,5);
		BOOST_TEST(list1 == LinkedList<int>(initArr2,9));

		BOOST_CHECK_THROW(list1.getSublist(3, 1), std::exception);
		BOOST_CHECK_THROW(list1.getSublist(1, 10), std::exception);
		BOOST_CHECK_THROW(list1.getSublist(-1, 3), std::exception);

	LinkedList<int> *list2 = list1.getSublist(0,0).release();
	LinkedList<int> *list3 = list1.getSublist(0,1).release();
	LinkedList<int> *list4 = list1.getSublist(0,9).release();
		BOOST_TEST(*list2 == LinkedList<int>());
		BOOST_TEST(*list3 == LinkedList<int>(initArr3,1));
		BOOST_TEST(*list4 == list1);

		BOOST_REQUIRE_THROW(list1.set(4, 10), std::exception);

	list1.set(-2,0);
	list1.set(8,8);
	list1.set(0,7);
		BOOST_TEST(list1 == LinkedList<int>(initArr35,9));

		BOOST_REQUIRE_THROW(list1.removeAt(-1), std::exception);
		BOOST_REQUIRE_THROW(list1.removeAt(10), std::exception);

	list1.removeAt(0);
	list1.removeAt(7);
	list1.removeAt(4);
		BOOST_TEST(list1 == LinkedList<int>(initArr4,6));


	// delete list2;
	// delete list3;
	// delete list4;
}
