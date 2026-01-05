#pragma once

#include <cassert>
#include <iostream>
#include <type_traits>
#include <cstring>
#include <string>
#include <utility>

namespace FuncTamplate {


	namespace Case1 
	{
		template<typename T>
		T max(T a, T b)
		{
			// if b < a then yield a else yield b
			return b < a ? a : b;
		}

		template<typename T>
		void f(T t) {

		//	static_assert(sizeof(int) > 10, "int too small");
			static_assert(sizeof(T) > 4, "T too small");
		}
	}

	namespace Case2 {
		template<typename T>
		T max(T a, T b) {
			std::cout << __PRETTY_FUNCTION__ << "\n";
			return b < a ? a : b;
		}

		template<typename T>
		void foo(T a, T b) {
			std::cout << __PRETTY_FUNCTION__ << "\n";
		}
	}

	namespace Case3 {

		namespace V1 {
			template<typename T1, typename T2>
			T1 max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}
		namespace V2 {
			template<typename T1,typename T2,typename RT>
			RT max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}
		namespace V3 {
			template<typename RT,typename T1,typename T2>
			RT max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}
		namespace V4 {
#if __cplusplus > 201103
			template<typename T1, typename T2>
			auto max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
#else
			template<typename T1, typename T2>
			auto max(T1 a, T2 b) -> decltype(b < a ? a : b)
			{
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}

			template<typename T1, typename T2>
			auto max(T1 a, T2 b) -> decltype(true ? a : b)// use true declaration is enough
			{
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
#endif		
		}

		namespace V5 {
			template<typename T1, typename T2>
			auto max(T1 a, T2 b) -> typename std::decay<decltype(true ? a : b)>::type
			{
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}
		namespace V6 {
			// std::common_type<>::type
#if __cplusplus > 201103
			template<typename T1,typename T2>
			std::common_type_t<T1, T2> max(T1 a, T2 b) {// Since C++14
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
#else
			template<typename T1, typename T2>
			typename std::common_type<T1, T2>::type max(T1 a, T2 b) {// Since C++11
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
#endif

		}
	}

	namespace Case4 {
		namespace V1 {
			template<typename T1,typename T2,
					typename RT = std::decay_t<decltype(true?T1():T2())>>
			RT max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ?  a : b;
			}
		}
		namespace V2 {
			template<typename T1, typename T2,
					typename RT = std::common_type_t<T1,T2>>
			RT max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ?  a : b;
			}
		}
		namespace V3 {
			template<typename RT = long, typename T1,typename T2>
			RT max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a? a:b;
			}
		}
	}

	namespace Case5 {
		namespace V1 {
			inline int max(int a, int b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}

			template<typename T>
			T max(T a, T b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}

		namespace V2 {
			template<typename T1,typename T2>
			auto max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}

			template<typename RT, typename T1, typename T2>
			RT max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}

		namespace V3 {
			template<typename T>
			T max(T a, T b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}

			template<typename T>
			T* max(T* a, T* b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return *b < *a ? a : b;
			}

			inline char const* max(char const* a, char const* b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return strcmp(b, a) < 0 ? a : b;
			}
		}

		namespace V4 {
			template<typename T>
			T const& max(T const&a,T const& b){
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return  b < a ? a : b;
			}

			inline char const* max(char const* a, char const* b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return std::strcmp(b, a) < 0 ? a : b;
			}

			template<typename T>
			T const& max(T const& a, T const& b, T const&c) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return max(max(a, b), c);
			}
		}

		namespace V5 {
			template<typename T>
			T max(T a, T b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}

			template<typename T>
			T max(T a, T b, T c) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return max(max(a, b), c);
			}

			inline int max(int a, int b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}

		}
	}

}

/*
*  1.7 Summary
* 
* . Function templates define a family of functions for different template arguments
* 
* . When you pass arguments to function parameters depending on template parameters,
*   function templates deduce the template parameters to be instantiated the corressponding
*   parameter types
* 
* . You can explicity qualify the leading template parameters
* 
* . You can define default arguments for template parameters. These may refer to previous
*   template parameters and be followed by parameters not having default arguments.
* 
* . You can overload function templates
* 
* . When overloading function templates with other function templates, you should ensure
*   that only one of them matches for any call
* 
* . When you overload function templates. limit your changes to specifying template
*   parameter explicitly
* 
* . Ensure the compiler sees all overloaded version of function templates before you call them
* 
* 
*/
void func_template_example();

