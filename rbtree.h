#ifndef RBTREE_H_
#define RBTREE_H_
#include "pair.h"
#include "RBtreeIterator.h"
#include "construct.h"
#include "allocator.h"
namespace EasySTL {
template <class Key, class Value, class KeyOfValue, class Compare,
          class Alloc = alloc>
class rb_tree {
protected:
	typedef void* void_pointer;
	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node; 
	typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type* pointer;
    typedef const value_type* const_pointer;
	typedef const value_type& const_reference;

	typedef rb_tree_node* link_type;
	typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __rb_tree_color_type color_type;
    typedef value_type& reference;

protected:
	link_type get_node() {return rb_tree_node_allocator::allocate();}
	void put_node(link_type p) {rb_tree_node_allocator::deallocate(p);}
    void destroy(Value* value_field) {}
    link_type create_node(const value_type& x) {
    	link_type tmp = get_node();  //配置空间
    	construct(&tmp->value_field, x); //构造内容
    	return tmp;
    }

    link_type clone_node(link_type x) {  //赋值一个node
    	link_type tmp = create_node(x->value_field);
    	tmp->color = x->color;
    	tmp->left = 0;
    	tmp->right= 0;
    	return tmp;
    }
    
    void destroy_node(link_type p) {
    	destroy(&p->value_field);    //析构内容,将 value_field 的地址传给该函数
    	put_node(p);                 //释放内存
    }
    
    void clear() {

    }
protected:
	//rbtree 只以三笔数据表现
	size_type node_count; //树上的节点个数
	link_type header;  //实现上的a trick，与root互为父节点，header的左右孩子都是root
	Compare key_compare; //传入的节点键值大小比较准则
    
    //方便获取header的成员
    link_type& root() const {return (link_type&) header->parent;}
    link_type& leftmost() const {return (link_type&) header->left;}
    link_type& rightmost() const {return (link_type&) header->right;}
    
    //以下6个函数用来方便取得节点x的成员
    static link_type& left(link_type x) 
      { return (link_type&)(x->left);}

    static link_type& right(link_type x) 
      { return (link_type&)(x->right);}

    static link_type& parent(link_type x) 
      { return (link_type&)(x->parent);}

    static reference value(link_type x)
      { return x->value_field;}

    static const Key& key(link_type x)
      { return KeyOfValue() (value(x));}

    static color_type& color(link_type x)
      { return (color_type&) (x->color);}

    //以下6个函数用来方便取得x的成员
    static link_type& left(base_ptr x)
      { return (link_type&)(x->left);}
    
    static link_type& right(base_ptr x)
      { return (link_type&)(x->right);}
    
    static link_type& parent(base_ptr x) 
      { return (link_type&)(x->parent);}

    static reference value(base_ptr x)
      { return ((link_type)x)->value_field;}

    static const Key& key(base_ptr x)
      { return KeyOfValue() (value(link_type(x)));}

    static color_type& color(base_ptr x)
      { return (color_type&) (link_type(x)->color);}

    static link_type minimum (link_type x) {
    	return (link_type) __rb_tree_node_base::minimum(x);
    }

    static link_type maximum(link_type x) {
    	return (link_type) __rb_tree_node_base::maximum(x);
    }
public:
	typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
    typedef __rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;

private:
	             //新值插入点         插入点的父节点    新值
    iterator __insert(base_ptr x_, base_ptr y_, const Value& v) {
    	link_type x = (link_type) x_;
    	link_type y = (link_type) y_;
    	link_type z;
    	if (y==header || x != 0 || key_compare(KeyOfValue()(v), key(y))) {
    		z = create_node(v);
    		left(y) = z; //这使得y即为header时，leftmost() = z
    		if(y==header) {
    			root() = z;
    			rightmost() = z;
    		} else if (y == leftmost())  //y 为最左节点
    		  leftmost() =z;
    	} else {
    		z = create_node(v);
    		right(y) = z;
    		if(y==rightmost()) rightmost() = z;
    	}
    	parent(z) = y;
    	left(z) = 0;
    	right(z) = 0;
            
    	__rb_tree_rebalance(z, header->parent);
    	++node_count;
    	return iterator(z);
    }

	link_type __copy(link_type x, link_type p);
	void __erase(link_type x);
	void init() {
		header = get_node(); //产生一个节点空间，令header指向它
		color(header) = __rb_tree_red; //header为红色，区分header与root

		root() = 0;
		leftmost() = header; //令header的左子节点为自己
		rightmost()= header; //令header的右节点为自己
	}

public:
	rb_tree(const Compare& comp = Compare())
	    : node_count(0), key_compare(comp) { init();}
	
	~rb_tree() {
        clear();
        put_node(header);
	}
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>&
	   operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);

public:
	Compare key_comp() const {return key_compare;}
	iterator begin() const {return leftmost();}
	iterator end() const {return header;} //RBtree的重点为header所指的位置
    bool empty() const { return node_count == 0;}
    size_type size() const {return node_count;}
    size_type max_size() const { return size_type(-1);}

public:
	//将想插入REtree中节点独一无二 如果插入失败返回的是指向该节点的迭代器·
    pair<iterator, bool> insert_unique(const value_type& v) {
    	link_type y  = header;
    	link_type x  = root();
    	bool comp = true;
    	while ( x != 0) {
    		y = x;
    		comp = key_compare(KeyOfValue()(v), key(x));
    		x = comp ? left(x) : right(x);
    	}
    	//离开while后，y所指插入点的父节点(此时的它必为叶节点)
    	iterator j = iterator(y);
    	if (comp)
    		if (j == begin())
    			return pair<iterator, bool>(__insert(x, y, v), true);
    	    else
    	    	--j;

    	if (key_compare(key(j.node), KeyOfValue()(v)))
    		return pair<iterator, bool>(__insert(x, y, v), true);

    	return pair<iterator, bool>(j, false);
    }
    
    template<class iterator>
    bool insert_unique(iterator first, iterator last) {
        for(auto it =first;it!=last;it++) {
            insert_unique(*it);
        }
    }
    //将想插入RB-tree中允许节点值重复
    iterator insert_equal(const value_type& v) {
    	link_type y = header;
    	link_type x = root(); //从根节点开始
    	while(x != 0) {
    		y = x;
    		x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
    	}
        return __insert(x, y, v);
    }
    
    
    //重新令树形平衡（颜色 旋转树形）
    //参数1 为新增节点， 参数2 为root
    inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
    	x->color = __rb_tree_red; //新节点为红色
    	while(x!=root && x->parent->color == __rb_tree_red) {//父节点为红
    		if (x->parent == x->parent->parent->left) {//父节点为祖父节点的左节点
    			//父节点为祖父节点之左子节点
    			__rb_tree_node_base* y = x->parent->parent->right;//令y为伯父节点
    			if (y && y->color == __rb_tree_red) { //伯父节点存在，且为红
    				x->parent->color = __rb_tree_black;//更改父节点为黑
    				y->color = __rb_tree_black; //更改伯父节点为黑
    				x->parent->parent->color = __rb_tree_red;//更改祖父节点为红
    				x = x->parent->parent;
    			} else {//无伯父节点或伯父节点为黑
    				if (x==x->parent->right) {//如果新节点为父节点之右节点
    					x=x->parent;
    					__rb_tree_rotate_left(x, root); //第一参数为左旋点
    				}
    				x->parent->color = __rb_tree_black;
    				x->parent->parent->color = __rb_tree_red;
    				__rb_tree_rotate_right(x->parent->parent, root); //第一参数为右旋点
    			}
			} else { //父节点为祖父节点之右子节点
				__rb_tree_node_base* y = x->parent->parent->left;//令y为伯父节点
				if(y&&y->color == __rb_tree_red) { //有伯父节点，且为红色
					x->parent->color = __rb_tree_black;//更改父节点为黑
					y->color=__rb_tree_black; //更改伯父节点为黑
					x->parent->parent->color=__rb_tree_red;//更改祖父节点为红
					x=x->parent->parent; //继续往上检查
				} else{ //无伯父节点，或伯父节点为黑
					if(x==x->parent->left) { //如果新节点为父节点之左子节点
						x = x->parent;
						__rb_tree_rotate_right(x, root);//第一参数为右旋点
					}
					x->parent->color = __rb_tree_black; //改变颜色
					x->parent->parent->color = __rb_tree_red;
					__rb_tree_rotate_left(x->parent->parent, root);//第一参数为左旋点
				}
			}
			    
		} //end of while
		root->color = __rb_tree_black; //root节点永远为黑
    }

    inline void
    __rb_tree_rotate_left(__rb_tree_node_base* x, 
    	                  __rb_tree_node_base*& root)
    {
    	//x 为旋转点
    	__rb_tree_node_base* y = x->right;
    	x->right = y->left;
    	if (y->left != 0)
    		y->left->parent = x;
    	y->parent = x->parent;
        
        if(x==root)
        	root = y;
        else if (x==x->parent->left)
        	x->parent->left = y;
        else
        	x->parent->right = y;
        y->left = x;
        x->parent = y;
    }
    
    inline void
    __rb_tree_rotate_right(__rb_tree_node_base* x,
    	                   __rb_tree_node_base*& root)
    {
    	//x为旋转点
    	__rb_tree_node_base* y = x->left;
    	x->left = y->right;
    	if(y->right != 0)
    		y->right->parent = x;
    	y->parent = x->parent;
        
        //令y完全顶替x的位置（必须将其父节点的关系完全接收过来）
    	if(x==root)
    		root = y;
    	else if(x==x->parent->right)
    		x->parent->right = y;
    	else
    		x->parent->left = y;
    	y->right = x;
    	x->parent = y;
    }

    iterator find(const Key& k) {
    	link_type y = header;  //last node which is not less than k
    	link_type x = root();  //current node
        
        while(x != 0)
        	if (!key_compare(key(x), k))  //该数是否比 k 大，是的话向左子树去
        		y = x, x = left(x); //注意语法！
        	else
        		x = right(x);
        iterator j = iterator(y);
        return (j==end() || key_compare(k, key(j.node))) ? end() : j;
    }

};
}
#endif