#include "mapTest.h"
#include "../pair.h"
#include <string>
#include <iostream>

namespace EasySTL {
namespace MapTest {
   using string = std::string;
   void testCase1() {
   	  map<string, int> simap;
   	  simap[string("jihou")] = 1;
   	  simap[string("jerry")] = 2;
   	  simap[string("jason")] = 3;

   	  const pair<const string, int> value(string("david"),5);
   	  simap.insert(value);

   	  auto iter = simap.begin();
   	  for(;iter != simap.end();++iter) 
   	  	 std::cout<<iter->first <<' ' <<iter->second<<std::endl;

   	  int number = simap[string("jihou")];
   	  std::cout <<number<< std::endl;

   	  iter = simap.find(string("jerry"));
      if(iter==simap.end()) 
      	 std::cout<< "not found" <<std::endl;
      else
      	 std::cout<< "found!" <<std::endl;
   }
}
}