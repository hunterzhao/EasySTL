#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "dequeIterator.h"
#include "allocator.h"
#include "construct.h"
#include "algorithm.h"
enum {_min_map_num = 8};
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
		//配置一个元素大小,value
        typedef simple_alloc<value_type, Alloc> data_allocator;
        //配置一个指针大小,map
        typedef simple_alloc<pointer, Alloc> map_allocator;
        
        pointer allocate_node() {
            return data_allocator::allocate(buffer_size());
        }

        static size_t buffer_size() {return _deque_buf_size(BufSize, sizeof(T));}
        
        static size_t _deque_buf_size(size_t n, size_t sz) {
            return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
        }
        
        int initial_map_size() {
            return _min_map_num;
        }
        
        void fill_initialize(size_type n, const value_type& value);

        void push_back_aux(const value_type& t);

        void push_front_aux(const value_type& t);

        void create_map_and_nodes(size_type num_elements);

        void reserve_map_at_back(size_type node_to_add = 1);
        void reserve_map_at_front(size_type node_to_add = 1);
        void reallocate_map(size_type node_to_add, bool add_at_front);
        void pop_back_aux(); //finish.cur == finish.first 释放该缓冲区
        void pop_front_aux();

    public:
        deque() :start(), finish(), map_size(0), map(0){
            create_map_and_nodes(0);
        }
        deque(int n, const value_type& value)
           : start(), finish(), map(0), map_size(0) {
               fill_initialize(n, value);
           }   
        
        ~deque(){

        }
        void push_back(const value_type& t) {
        	if(finish.cur != finish.last - 1) {
        		construct(finish.cur, t);
        		++finish.cur;
        	} else { //需要配置新的缓冲区
        		push_back_aux(t);
        	}
        } 

        void push_front(const value_type& t){
            if (start.cur != start.first) {
                construct(start.cur - 1, t);
                --start.cur;
            } else {//第一缓冲区已经没有备用空间了
                push_front_aux(t);
            }
        }

        void pop_back() {
            if (finish.cur != finish.first) {
                --finish.cur;
                destroy(finish.cur);
            } else {
                pop_back_aux();
            }
        }

        void clear();

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
#include "impl/deque.impl.h"
#endif