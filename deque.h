#include "allocator.h"

namespace EasySTL {
	template<class T, class Alloc = alloc, size_t BufSize = 0>
	class deque{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
    	typedef _deque_iterator<T, T&, T*, BufSize> iterator;
          
	protected:
		//指向map空间上的指针类型
		typedef pointer *map_pointer;
	protected:
		//配置一个元素大小
        typedef simple_alloc<value_type, Alloc> data_allocator;
        //配置一个指针大小
        typedef simple_alloc<pointer, Alloc> map_allocator;

        void fill_initialize(size_type n, const value_type& value);

        void push_back_aux(const value_type& t);

        void create_map_and_nodes(size_type num_elements);
    public:
        deque(int n, const value_type& value)
           : start(), finish(), map(0), map_size(0) {
               fill_initialize(n, value);
           }   
        
        void push_back(const value_type& t) {
        	if(finish.cur != finish.last - 1) {
        		construct(finish.cur, t);
        		++finish.cur;
        	} else { //需要配置新的缓冲区
        		push_back_aux(t);
        	}
        } 

        
    protected:
        iterator start;
        iterator finish;

		//data member
		map_pointer map;      //map首地址
		size_type map_size;   //map存储的大小

	public:
		iterator begin() { return start;}
        iterator end() {return finish;}
        reference operator[] (size_type n) {
        	return *(start + n);
        }

        reference front() {return *start;}
        reference back() {
        	return *(finish - 1);
        }

        size_type size() const { return finish - start;}

        size_type max_size() const { return size_type(-1);}
        bool empty() const { return finish == start;}
	};
}