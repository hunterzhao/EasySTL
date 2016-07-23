#include "listTest.h"

namespace EasySTL {
	namespace ListTest {
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

            easyList<double> v1;
            v1.push_back(2);
            v1.push_back(5);
            v1.push_back(3);
            v1.push_back(9);

            easyList<double> v2;
            v2.push_back(1);
            v2.push_back(1.5);
            v2.push_back(4);
            v2.push_back(7);
            
            //v1.transfer(v1.begin()+2, v2.begin(), v2.end());
            //v1.reverse();
            //std::cout<<v1.size()<<std::endl;
            v1.sort();
            EasySTL::Test::print_container(v1,"v1");
               
		}
	}
}