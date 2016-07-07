#ifndef VECTORTEST_H_
#define VECTORTEST_H_

#include "../vector.h"
#include "testFun.h"

#include <vector>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
namespace EasySTL {
    namespace VectorTest{
		template<class T>
		using stdVec = std::vector < T >;

		template<class T>
		using easyVec = EasySTL::vector < T >;

		void testCase1();
	}
}
#endif