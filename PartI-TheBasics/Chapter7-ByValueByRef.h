#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <cassert>

namespace by_value_or_by_ref {

	inline std::string retStr() {
		return "jack & rose";
	}
	inline const std::string retCStr() {
		return "const jack & rose";
	}
	// 7.1 Passing by Value
	namespace passing_by_value {

		template<typename T>
		void printV(T arg) {
			std::cout << arg << "\n";
		}
	}

	// 7.2 Passing by Reference
	namespace passing_by_ref 
	{
		// 7.2.1 Passing by Constant Reference
		namespace passing_by_const_ref 
		{
			template<typename T>
			void printR(T const& arg) {
				std::cout << arg << "\n";
			}
		}
		// 7.2.2 Passing by Nonconstant Reference
		namespace passing_by_nonconst_ref
		{
#if 0
			template<typename T>
			void outR(T& arg) {
				static_assert(!std::is_const_v<T>,"out parameter of outR<T>(T&) is const");
				if (std::is_array_v<T>) {
					std::cout << "got array of " << std::extent_v<T> << " elems\n";
				}
				else {
					std::cout << arg << "\n";
				}
			}
#else
#if 0
			template<typename T,
						typename = std::enable_if_t<!std::is_const_v<T>>>
#else
			template<typename T>
			concept not_const = !std::is_const_v<T>;

			template<typename T>
			requires not_const<T>
#endif
			void outR(T& arg) {				
				if (std::is_array_v<T>) {
					std::cout << "got array of " << std::extent_v<T> << " elems\n";
				}
				else {
					std::cout << arg << "\n";
				}
			}
#endif
		}
	}

	// 7.3 Passing by Forwarding Reference
	namespace passing_by_forwarding_ref 
	{
		template<typename T>
		void passR(T&& arg) {
#if 0
			T x;
#else
			T x = std::forward<T>(arg);
#endif
		}
	}

	// 7.4 Using std::ref() and std::cref()
	namespace using_ref_cref 
	{
		inline void printStr(std::string const& str) {
			std::cout << str << "\n";
		}

		template<typename T>
		void printT(T arg) {
			std::cout << __PRETTY_FUNCTION__ << "\n";
			printStr(arg);
		}

		template<typename T>
		void printV(T arg) {
			std::cout << arg << "\n";
		}

		template<typename T1,typename T2>
		bool isLess(T1 arg1, T2 arg2) {
			return arg1 < arg2;
		}
	}
	// 7.5 Dealing with String Literals and Raw Arrays
	namespace dealing_string_literals_and_raw_arrays 
	{
#if 0
		template<typename T>
		void foo(T const& arg1, T const& arg2) {

		}
#else
		template<typename T>
		void foo(T arg1,T arg2) {
			if (arg1 == arg2) {// compares address of passed arrays
				std::cout <<"'"<< arg1 << "' equal to '" << arg2 << "'\n";
			}
			else {
				std::cout << "'" << arg1 << "' not equal to '" << arg2 << "'\n";
			}
		}
#endif

		// 7.4.1 Special Implementations for String Literals and Raw Arrays
		namespace special_impl_string_and_arrays 
		{
			template<typename T,std::size_t L1,std::size_t L2>
			void foo(T(&arg1)[L1], T(&arg2)[L2]) {

				T* pa = arg1;// decay arg1
				T* pb = arg2;// decay arg2
#if 0
				if (compareArrays(pa, L1, pb, L2)) {

				}
#endif
			}


			template<typename T,
				typename = std::enable_if_t<std::is_array_v<T>>>
			void bar(T&& arg1, T&& arg2)
			{
			}
		}
	}
	// 7.5 Dealing with Return Value
	namespace dealing_ret_val
	{
#if 0
		template<typename T>
		T retR(T&& p) {// p is forwarding reference
			return T{};//OOPS: returns by reference when called for lvalues
		}

		template<typename T>
		T retV(T p) {//Note: p might become a reference
			return T{};//OOPS: returns a reference if T is a reference
		}

		// use std::remove_reference<>
		template<typename T>
		typename std::remove_reference_t<T> retV{
			return T{};// always return by value
		}
			// other traits, such as std::decay<>
			// use auto , becuase auto always decays		

			template<typename T>
		auto retV(T p) {
			return T{};// always return by value
		}
#endif
	}

	// 7.6 Recommanded Template Parameter Declaration
	namespace recommand_template_param_decl
	{
		/*
		* . Declare to pass the arguments by value:
		*   This approach is simple,it decays string literals and raw arrays, but it
		*   doesn't provide best performance for large objects,
		*/

	}
}

void by_value_or_by_ref_example();