#include "setTest.h"
#include "testFun.h"
#include "../algorithm.h"
#include <set>
namespace EasySTL {
namespace SetTest {

    void testCase1() {
    	int ia[5] = {0,1,3,6,2};
    	set<int> iset(ia, ia+5);
    	std::set<int> stdset(ia, ia+5);
    	std::cout<< "size=" << iset.size() <<std::endl;
    	if (Test::container_equal(iset, stdset)) std::cout<<"equal"<<std::endl;
    	iset.insert(4);
        iset.insert(10);
        
        Test::print_container(iset, "set");
         auto ite1 = find(iset.begin(), iset.end(), 3);
         if(ite1!=iset.end())
         	std::cout<< *ite1 <<" found "<<std::endl;
         else 
             std::cout<< "not found "<<std::endl;
    }
}
}