# EasySTL，实现自己的STL

学习C++离不开学习STL，除了阅读经典的《STL源码剖析》，也要自己动手编写代码。该项目将持续更新，这也是我未来几个月实习空闲时间要做的事，加油~

-------------
### 要点
- **c++11**
- **g++ makefile编写**
- **c++ google code style**
- **模板编程**
- **内存管理，数据结构**

-------------------
###STL文件关系树

![父子进程通信](https://github.com/hunterzhao/EasySTL/blob/master/pic/STL%E6%96%87%E4%BB%B6%E5%85%B3%E7%B3%BB%E6%A0%91.png?raw=true)

-------------------

### 环境
- ubuntu 14.04
- g++ 4.8.8
- sublime
- c++11

-------------------
###使用
1. 下载代码[Github][1]. 如果有帮助请帮我点star :)
2. main.cpp可以修改要测试的容器或算法
3. 根目录下运行 make
4. 运行test.exe

-------------------
###TODO Continue...

>基本

1. allocator 空间配置器 done 
2. typetraits 类型萃取器 done
3. iterator 迭代器 done
4. construct 对象构造器 done
5. alogritm 算法库
6. unitialized 容器构造器 done

>容器

1. vector done 2016.7.09 done
2. list done 2016.7.23 done
3. string
4. deque 2016.12.24 done
5. set
6. map
7. unordered_


>算法

1. Qsort
2. AVL tree
3. heap done

-------------------
###测试
1. vector 构造功能,列表初始化,插入功能,clear功能,迭代器功能 ok
2. list 构造功能,插入功能,clear功能,迭代器功能,reverse, merge, sort(插入排序) ok



---------
[1]: https://github.com/hunterzhao/EasySTL
