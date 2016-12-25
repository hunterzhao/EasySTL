#ifndef HEAP_TEST_H
#define HEAP_TEST_H
#include "../algorithm.h"
#include <vector>
#include "../vector.h"
#include "testFun.h"
namespace EasySTL {
	namespace HeapTest {
        template<class T>
		using stdVec = std::vector < T >;

		template<class T>
		using easyVec = EasySTL::vector < T >;

		void testCase1();
	}
}

#endif