#include "VectorTest.h"

namespace EasySTL {
	namespace VectorTest {
		void testCase1(){
			//std::string old_SGI_vector = "old_SGI_vector";
			//std::string new_EasySTL_vector = "new_EasySTL_vector";
			stdVec<std::string> v1(10, "zzz");
			easyVec<std::string> v2(10, "zzz");
			EasySTL::Test::print_container(v1, "SGI_vector");
			EasySTL::Test::print_container(v2, "EasySTL_vector");
			assert(EasySTL::Test::container_equal(v1, v2));
		}
	}
}