#ifndef LISTTEST_H_
#define LISTTEST_H_

#include "../list.h"
#include "testFun.h"

#include <list>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
namespace EasySTL {
    namespace ListTest{
		template<class T>
		using stdList = std::list < T >;

		template<class T>
		using easyList = EasySTL::list < T >;

		void testCase1();
	}
}
#endif