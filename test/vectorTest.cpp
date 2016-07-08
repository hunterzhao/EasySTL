#include "VectorTest.h"

namespace EasySTL {
	namespace VectorTest {
		void testCase1(){
			//std::string old_SGI_vector = "old_SGI_vector";
			//std::string new_EasySTL_vector = "new_EasySTL_vector";
			//stdVec<std::string> v1(10, "zzz");
			easyVec<std::string> v2(3, "zm");
			//EasySTL::Test::print_container(v1, "SGI_vector");
			EasySTL::Test::print_container(v2, "construct");
            
            std::string a = "huyun";
			v2.push_back(a);

			EasySTL::Test::print_container(v2, "push_back");
            
            v2.pop_back();

            EasySTL::Test::print_container(v2, "pop_back");

            auto p = v2.begin();

            p = p + 2;

            std::cout << "the second one" <<*p <<std::endl;
            
            
			//assert(EasySTL::Test::container_equal(v1, v2));

		}
	}
}