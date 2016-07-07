#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <new>

#include "typetraits.h"

namespace EasySTL {
   template<class T1, class T2>
   inline void construct(T1 *ptr1, const T2& value) {
   	  new(ptr1) T1(value); //placement new 在已获取的内存上创建对象
   }

   template<class T>
   inline void destroy(T *ptr) {
   	   ptr->~T();
   }

   template<class ForwardIterator>
   inline void _destory(ForwardIterator first, ForwardIterator last, _true_type) {}

   template<class ForwardIterator>
   inline void _destory(ForwardIterator first, ForwardIterator last, _false_type) {
   	   for (; first != last; ++first) {
   	   	   destroy(&*first);
   	   }
   }

   template<class ForwardIterator>
   inline void destroy(ForwardIterator first, ForwardIterator last) {
   	   typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD;
   	   _destory(first, last, is_POD());
   }
   
   //针对char* wchar_t*的特化版本
   inline void destroy(char*, char*) {}
   inline void destroy(wchar_t*, wchar_t*) {}
}

#endif