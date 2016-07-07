#include "vector.h"

namespace EasySTL {

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