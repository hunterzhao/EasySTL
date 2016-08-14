#ifndef DEQUETEST_H_
#define DEQUETEST_H_

#include "../deque.h"
#include "testFun.h"

#include <deque>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
namespace EasySTL {
    namespace DequeTest{
        template<class T>
        using stdDeque = std::deque < T >;

        template<class T>
        using easyDeque = EasySTL::deque < T >;

        void testCase1();
    }
}
#endif