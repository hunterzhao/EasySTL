#ifndef FUNCTIONAL_H_
#define FUNCTIONAL_H_
#include "pair.h"
namespace EasySTL {
template <class Arg, class Result>
struct unary_function {
	typedef Arg argumant_type;
	typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};


template <class T>
struct identity : public unary_function<T, T> {
	const T& operator()(const T& x) const {return x;}  //函数调用操作符
};

template <class T>
struct less : public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x < y;}
};

// template <class T>
// bool less(const T& x, const T& y) const {
//     return x < y;
// }

template <class T>
struct select1st : public unary_function<T, typename T::first_type> {
	const typename T::first_type& operator()(const T& x) const {return x.first;}
};
}
#endif