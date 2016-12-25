#include "heapTest.h"

namespace EasySTL {
	namespace HeapTest {
		void testCase1(){
			int ia[9] = {0,2,1,3,6,9,7,8,5};
			stdVec<int> vec(ia, ia+9);
			EasySTL::make_heap(vec.begin(), vec.end());
            EasySTL::Test::print_container(vec, "make_heap");
            
            vec.push_back(4);
            EasySTL::push_heap(vec.begin(), vec.end());
            EasySTL::Test::print_container(vec, "push_heap");

            EasySTL::pop_heap(vec.begin(), vec.end());
            std::cout<< vec.back() <<std::endl;
            vec.pop_back();
 		}
	}
}