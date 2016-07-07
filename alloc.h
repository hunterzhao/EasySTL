#ifndef _ALLOC_H_
#define _ALLOC_H_
/*
* 简单的空间配置器
*/

#include <cstdlib>

namespace EasySTL {
  /*
  * 空间配置器
  */
  class alloc {
  private:
    enum {_ALIGN = 8}; //小型区块的上调边界
    enum {_MAX_BYTES = 128}; //小型区块的上限
    enum {_NFREELIST = _MAX_BYTES / _ALIGN}; //freelist的个数
    enum {_NOBJS = 20};//每次增加的节点数量

    union obj { //free list 节点
      union obj* free_list_next;
      char client[1];
    };

    static obj * volatile free_list[_NFREELIST];

    static char *start_free; //内存池起始地址
    static char *end_free; //内存池结束地址
    static size_t heap_size; 

    //根据需要的区块大小，选择freelist编号
    static size_t FREELIST_INDEX(size_t bytes) {
    	return ((bytes + _ALIGN - 1) / _ALIGN - 1);
    }
   
    //将bytes 上调至8的倍数
    static size_t ROUND_UP(size_t bytes) {
        return ((bytes + _ALIGN - 1) & ~(_ALIGN - 1));
    }

    //返回一个大小为n的对象，并可能加入大小为n的其他区块到free-list
    static void *refill(size_t bytes);

    //配置一大块空间，可容纳_NOBJS个大小为size的区块
    static char *chunk_alloc(size_t bytes, size_t& nobjs);

  public:
  	static void *allocate(size_t bytes);

  	static void deallocate(void *ptr, size_t bytes);

  	static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
  };
  
} //end of namespace EasySTL

#endif 