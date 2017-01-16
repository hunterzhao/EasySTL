#include "rbtreeTest.h"
#include "../functional.h"
#include "testFun.h"
#include <iostream>
namespace EasySTL {
	namespace RbtreeTest {
		void testCase1() {

			rb_tree<int, int, identity<int>, less<int> > itree;
			//std::cout<<itree.size()<<std::endl;
			itree.insert_unique(10);
			itree.insert_unique(7);
			itree.insert_unique(12);
            std::cout<<itree.size()<<std::endl;
			Test::print_container(itree, "rbtree");
		}
	}
}