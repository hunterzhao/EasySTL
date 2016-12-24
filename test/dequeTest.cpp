#include "dequeTest.h"

namespace EasySTL {
	namespace DequeTest {
		void testCase1(){
			//std::string old_SGI_vector = "old_SGI_vector";
			//std::string new_EasySTL_vector = "new_EasySTL_vector";
			//stdVec<std::string> v1(10, "zzz");
			// easyList<std::string> v1;
   //          v1.push_back("abc");
   //          v1.push_back("def");
   //          v1.push_back("ghi");
   //          v1.push_back("def");
            

            // stdList<std::string> v2;
            // v2.push_back("abc");
            // v2.push_back("def");
            // v2.push_back("ghi");
            // v2.push_back("def");

            stdDeque<double> v1;
            
            v1.push_back(2);
            v1.push_back(5);
            v1.push_back(3);
            v1.push_back(9);

            easyDeque<double> v2;

            v2.push_back(2);
            v2.push_back(5);
            v2.push_back(3);
            v2.push_back(9);
            EasySTL::Test::print_container(v2,"deque");
            if (EasySTL::Test::container_equal(v1, v2)){
                std::cout <<"equel"<<std::endl;
            }
            //v1.transfer(v1.begin()+2, v2.begin(), v2.end());
            //v1.reverse();
            //std::cout<<v1.size()<<std::endl;
            //v1.sort();
            //EasySTL::Test::print_container(v1,"v1");
               
		}
	}
}