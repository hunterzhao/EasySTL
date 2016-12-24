#ifndef _DEQUE_IMP_H_
#define _DEQUE_IMP_H_
#include "../uninitialized.h"

namespace EasySTL {
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::fill_initialize(size_type n,
		const value_type& value) {
		create_map_and_nodes(n); //安排好deque的结构，获取内存
		map_pointer cur;
		for (cur = start.node; cur < finish.node; ++cur)
			//已经获得了内存，构造buffer的开始节点，结束节点，初始值
			unitialized_fill(*cur, *cur + buffer_size(), value);
		unitialized_fill(finish.first, finish.cur, value);
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements) {
	    //如果刚好整除会多分配一个节点
		size_type num_nodes = num_elements / buffer_size() + 1;
		map_size = max(initial_map_size(), num_nodes + 2);
		map = map_allocator::allocate(map_size);

		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;
		map_pointer cur;

		for(cur = nstart; cur <= nfinish; cur++) {
			*cur = allocate_node();
		}
	    start.set_node(nstart);
	    finish.set_node(nfinish);
	    start.cur = start.first;
	    finish.cur = finish.first + num_elements % buffer_size();
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_back_aux(const value_type& t) {
		value_type t_copy = t;
		reserve_map_at_back(); //是否需要重换一个map
		*(finish.node + 1) = allocate_node(); //配置新的map节点

		construct(finish.cur, t_copy);
		finish.set_node(finish.node + 1);
		finish.cur = finish.first;
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_front_aux(const value_type& t) {
	    value_type t_copy = t;
	    reserve_map_at_front();
	    *(start.node - 1) = allocate_node();

	    start.set_node(start.node - 1);
	    start.cur = start.last - 1;
	    construct(start.cur, t_copy);
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reserve_map_at_back(size_type node_to_add) {
	    if (node_to_add + 1 > map_size - (finish.node - map)) {
	    	reallocate_map(node_to_add, false);
	    }
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reserve_map_at_front(size_type node_to_add) {
	    if (node_to_add > start.node - map) {
	    	reallocate_map(node_to_add, true);
	    }
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reallocate_map(size_type node_to_add, 
		                                          bool add_at_front) {
	    size_type old_num_nodes = finish.node - start.node + 1;
	    size_type new_num_nodes = old_num_nodes + node_to_add;

	    map_pointer new_nstart;
	    if (map_size > 2 * new_num_nodes) {
	    	//偏到一边去了，把他移到正中间来
	    	new_nstart = map + (map_size - new_num_nodes) / 2 
	    	             + (add_at_front ? node_to_add : 0);
	    	if (new_nstart < start.node)
	    		copy(start.node, finish.node + 1, new_nstart);
	    	else
	    		copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
	    } else {
	    	size_type new_map_size = map_size + max(map_size, node_to_add) + 2;
	    	map_pointer new_map = map_allocator::allocate(new_map_size);
	    	new_nstart = new_map + (new_map_size - new_num_nodes) / 2
	    	             + (add_at_front ? node_to_add : 0);
	    	copy(start.node, finish.node + 1, new_nstart);
	    	map_allocator::deallocate(map, map_size);
	    	map = new_map;
	    	map_size = new_map_size;
	    }

	    start.set_node(new_nstart);
	    finish.set_node(new_nstart + old_num_nodes - 1);
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_back_aux(){
		deallocate_node(finish.first);
		finish.set_node(finish.node - 1);
		finish.cur = finish.last - 1;
		destroy(finish.cur);
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_front_aux(){
		deallocate_node(start.last);
		start.set_node(start.node + 1);
		start.cur = start.first;
		destroy(start.cur);
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::clear() {
		for (map_pointer node = start.node + 1; node < finish.node; ++node) {
			destroy(*node, *node + buffer_size());
			data_allocator::deallocate(*node, buffer_size());
		}

		if (start.node != finish.node) {
			destroy(start.cur, start.last);
			destroy(finish.first, finish.cur);
			data_allocator::deallocate(finish.first, buffer_size()); //保留头缓冲区
		} else {
	        destroy(start.cur, finish.cur); //将缓冲区内的元素全部析构
		}
		finish = start;// 调整状态
	}
}

#endif