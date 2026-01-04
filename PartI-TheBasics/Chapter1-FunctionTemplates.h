#pragma once

#include <cassert>
#include <iostream>

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
			template<typename T1,typename T2>
			auto max(T1 a, T2 b) {
				std::cout << __PRETTY_FUNCTION__ << "\n";
				return b < a ? a : b;
			}
		}
	}

}

void func_template_example();

