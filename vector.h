#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>
#include <type_traits>
#include <iostream>
#include <initializer_list>

#include "allocator.h"
#include "algorithm.h"
#include "iterator.h"
//#include "construct.h"
#include "uninitialized.h"

namespace EasySTL {
	/******** vector ***********/
	template<class T, class Alloc = alloc>
	class vector {
	public:
		//vector的嵌套型别定义
		typedef T         value_type;
		typedef T*        pointer;
		typedef T*        iterator;
		typedef const T*  const_pointer;
		typedef T&        reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;  
    	
    protected:
    	//simple_alloc 是空间配置器
    	typedef simple_alloc<value_type, Alloc> data_allocator;

		iterator start_; //目前使用空间头
		iterator finish_;//目前使用空间尾
		iterator end_of_storage_;//目前可用空间的尾

		void insert_aux(iterator position, const T& x);
        //void insert(iterator position, size_type n, const T& x);

		void deallocate() {
			if (start_) {
				data_allocator::deallocate(start_, end_of_storage_ - start_);
			}
		}
        
        void fill_initialize(size_type n, const T& value) {
        	start_ = allocate_and_fill(n, value);
        	finish_ = start_ + n;
        	end_of_storage_ = finish_;
        }

    public:
        iterator begin() const { return start_;}
        iterator end() const  { return finish_;}
        size_type size() const { return size_type(end() - begin());}
        size_type capacity() const { return size_type(end_of_storage_ - begin());}
        bool empty() const { return begin() == end();}
        reference operator[](size_type n) {return *(begin() + n);}
        bool operator ==(const vector& other) const {
            auto first1 = begin(), last1 = end();
            auto first2 = other.begin(), last2 = other.end();
            for (; first1 != last1 && first2 != last2; ++first1, ++first2){
                if (*first1 != *first2)
                    return false;
            }
            return (first1 == last1 && first2 == last2);
             
        }

        vector() : start_(0), finish_(0), end_of_storage_(0) {}
        vector(size_type n, const T& value) { fill_initialize(n, value);}
        vector(int       n, const T& value) { fill_initialize(n, value);} 
        vector(long      n, const T& value) { fill_initialize(n, value);}
        vector(const std::initializer_list<T> v) {
            auto start_v = v.begin();
            auto end_v = v.end();
            size_type n = v.size();
            fill_initialize(n, T());
            finish_ = EasySTL::copy(start_v, end_v, start_);            
        }
        explicit vector(size_type n) {fill_initialize(n, T());}

        ~vector() {
        	destroy(start_, finish_); //construct.h中的函数
        	deallocate();  //vector的成员函数
        }

        reference front() { return *begin();}
        reference back() { return *end();}
        void push_back(const T& x) {
            if (finish_ != end_of_storage_) {
            	construct(finish_, x);
            	finish_++;
            } else {
            	insert_aux(end(), x);
            }
        }

        void pop_back() {
        	--finish_;
        	destroy(finish_);
        }
        
        void insert(iterator position, size_type n, const T& x);
 
        iterator erase(iterator position) {
        	if (position + 1 != end())
        		EasySTL::copy(position + 1, finish_, position);
            finish_--;
        	destroy(finish_);
        	return position;
        }

        iterator erase(iterator start_earse, iterator end_earse) {
	        size_type erase_size = end_earse - start_earse; //总共去掉多少元素

        	if (end_earse + 1 != end()) {  	
        		size_type left = finish_ - end_earse;   //去掉中间一段后，尾巴上还有多少元素
	        	EasySTL::copy(end_earse, finish_, start_earse);
	        	destroy(start_earse + left, finish_);
	        } else {
	        	destroy(start_earse, finish_);
	        }
	        finish_ = finish_ - erase_size;
        	return start_earse;
        }
        
        //调整容器大小，如果newsize小于原大小，则清空多余部分
        //如果大于原大小，则从尾部插入
        void resize(size_type new_size, const T& x) {
        	if (new_size < size()) 
        		erase(begin() + new_size, end());
        	else
        		insert(end(), new_size - size(), x);
        }

        void resize(size_type new_size) { resize(new_size, T());}
        void clear() { erase(begin(), end());}

    protected:
    	//分配n个元素大小空间，并以x初始化
        iterator allocate_and_fill(size_type n, const T& x) {
        	//获取内存空间
        	iterator result = data_allocator::allocate(n);
            //在获取到的内存上创建对象
            unitialized_fill_n(result, n, x);
            return result;
        }
	};

    template<class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, size_type n, const T& x) {
        //从position的位置插入n个元素，元素初始值为x
        std::cout << "i'm in" <<std::endl;
        T x_copy = x;
        if (n != 0) {
            //n必须不为空
            if (size_type(end_of_storage_ - finish_) >= n) {
                //内存的空间可以装下新增加的元素
                const size_type elems_after = finish_ - position;
                unitialized_fill_n(finish_, n, x_copy);
                
                EasySTL::copy(position, finish_, position + n);
               
                EasySTL::fill(position, position + n, x_copy);
               
                finish_ += n;
            } else {
                //内存空间不足以装下新增加的元素
                const size_type old_size = size();
                const size_type new_size = old_size + std::max(old_size, n);

                iterator new_start = data_allocator::allocate(new_size);
                if (!new_start) {
                    std::cout << "out_of_memory" <<std::endl;
                    return;
                }
                std::cout << new_size <<std::endl;
                iterator new_finish = new_start;
                try {
                    new_finish = uninitialized_copy(start_, finish_, new_start);                   
                    size_type m = position - start_;
                    auto new_position = new_start + m;
                    unitialized_fill_n(new_finish, n, x_copy);
                    EasySTL::copy(new_position, new_finish, new_position + n);
                    EasySTL::fill(new_position, new_position + n, x_copy);
                } catch(...) {
                    destroy(new_start, new_finish);
                    data_allocator::deallocate(new_start, new_size);
                    throw;
                }
                clear();
                deallocate();
                start_ = new_start;
                finish_ = new_finish + n;
                end_of_storage_ = new_start + new_size;
            }
        }
    }

    template<class T, class Alloc>
    void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
        if (finish_ != end_of_storage_) {
            //还有备用空间
            //在备用空间开始处创建一个对象，并以vector的最后一个对象为初始值
            construct(finish_, *(finish_ - 1));
            ++finish_;
            T x_copy = x;
            copy_backward(position, finish_ - 2, finish_ - 1);
            *position = x_copy; //position上是已经有构造好的对象，直接赋值就可以
        } else {
            //没有可用空间
            const size_type old_size = size();
            //内存不足则申请原来两倍的新内存
            const size_type new_size = old_size != 0 ? 2 * old_size : 1;

            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish = uninitialized_copy(start_, position, new_start);
                construct(new_finish ,x);  //未构造的内存，需要调用construct
                new_finish++;
                new_finish = uninitialized_copy(position, finish_, new_finish);
            } catch (...) {
                //出现异常，回滚
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }

            destroy(begin(), end());//销毁原来的vector内存空间
            deallocate();

            start_ = new_start;
            finish_ = new_finish;
            end_of_storage_ = new_start + new_size; 
        }
    }
}

#endif