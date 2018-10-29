#ifndef h_ch1_3
#define h_ch1_3
#include "prelude.h"

template<typename T>
const T& max_elem(const T* lis, unsigned const size)
{
	const T* max_val(lis);
	for (unsigned i = 1; i < size; ++i) {
		if (lis[i] > *max_val) { max_val = &(lis[i]);  };
	}
	return *max_val;
}


//?  Ctrl+H  :  替换T 到 特化的类型   <———— 逻辑未变，无需特化： 这就是实例化后的样子。
/*
template<> inline
const int& max_elem(const int* lis, unsigned const size)
{
	const int* max_val(lis);
	for (unsigned i = 1; i < size; ++i) {
		if (lis[i] > *max_val) { max_val = &(lis[i]);  };
	}
	return *max_val; 
}
*/

//? Haskell
/*
max :: (Ord a) => [a] -> a
max [x] = x
max (x:xs) = let omax = max xs in if x > omax then x else omax
*/

//x===========================================================================================================*/
template<typename T0,
         typename T1,
         typename T2,
         typename T3,
         typename T4>
T2 func(T1 v1, T3 v3, T4 v4)  //? 如果T1， T3，T4 一样的话，那就是同一个函数？ 函数内static变量就是同一个？
{
    T0 static sv0 = T0(0);
    T2 static sv2 = T2(0);

    std::cout << "\tv1: " << v1
              << "\tv3: " << v3
              << "\tv4: " << v4
              << "\t|| sv0: " << sv0;
    T2 v2 = sv2;

    sv0 -= 1;
    sv2 -= 1;

    return v2;
}

inline void use_Fuc() {

    double sv2 = func<double, int, int>(1, 2, 3);  // d i i i i
    cout << "\tsv2: " << sv2 << endl;              

    sv2 = func<double, int, int>(1, 2, 3);         // d i i i i 
    cout << "\tsv2: " << sv2 << endl;                        // 将实例化出   int      f  (int, int ,int)

	sv2 = func<double, int, double>(1, 2, 3);      //?* i * i i   
    cout << "\tsv2: " << sv2 << endl;                        //todo 将实例化出   double   f  (int, int, int)  .. 这两个函数不算重载、但又不是同一个函数！
	                                                         //todo  会共享函数体内的static变量吗？？
	                                                         //?  模板实例化出来的就不管重载了，只要模板参数不都一样，就是不同的函数！

    sv2 = func<double, int, int>(1, 0.1, 0.1);     // d i i d d
    cout << "\tsv2: " << sv2 << endl;

    sv2 = func<int, double, double>(0.1, 0.1, 0.1);// i d d d d 
    cout << "\tsv2: " << sv2 << endl;
}


#endif

