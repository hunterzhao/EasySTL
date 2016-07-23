#include "listNode.h"
#include "iterator.h"
namespace EasySTL {
    //迭代器本身不是指针，因为list不是连续的区间
    template<class T, class Ref, class Ptr>
    struct _list_iterator {
        typedef _list_iterator<T, T&, T*>   iterator; //指向内部元素值得迭代器
        typedef _list_iterator<T, Ref, Ptr> self; //指向list节点的迭代器
        typedef bidirectional_iterator_tag iterator_category;
        typedef T   value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef _list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        link_type node; //普通指针指向节点
        _list_iterator(link_type x) : node(x) {}
        _list_iterator() {}
        _list_iterator(const iterator& x) : node(x.node) {}
        bool operator==(const self& x) const {return node == x.node;}
        bool operator!=(const self& x) const {return node != x.node;}
        
        //deference
        reference operator*() const {return (*node).data;}
        pointer   operator->() const {return &(operator*());} //???
        
        //迭代器向前移动一个位置(++i)
        self& operator++() {
            node = node->next;
            return *this;
        }
        
        //迭代器向前移动一个位置(i++)
        self operator++(int) {
        	self tmp = *this;
        	++*this;
            return tmp;
        }

        //对迭代器递减1 (--i)
        self& operator--() {
        	node = node->prev;
        	return *this;
        }

        //对迭代器递减1 (i--)
        self operator--(int) {
        	self tmp = *this;
        	--*this;
            return tmp;
        }

        self operator+(int dis){
            self tmp = *this;
            while(dis-- > 0) {
                tmp = tmp.node->next;
            }
            return tmp;
        }

        self operator-(int dis){
            self tmp = *this;
            while(dis-- > 0) {
                tmp = tmp.node->prev;
            }
            return tmp;
        }
    };
}
