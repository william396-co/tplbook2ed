#pragma once
#include <iostream>


namespace Compile_Time_Programming {

	// 8.1 Template MetaProgramming
	namespace template_meta_programming 
	{
		template<unsigned p,unsigned d>// p: number to check, d: current divisor
		struct DoIsPrime {
			static constexpr bool value = (p % d != 0) && DoIsPrime<p, d - 1>::value;
		};

		template<unsigned p>
		struct DoIsPrime<p, 2> {// end recursion if divisor is 2
			static constexpr bool value = (p % 2 != 0);
		};

		template<unsigned p>
		struct IsPrime {
			// start recursion with divisor from p/2
			static constexpr bool value = DoIsPrime<p, p / 2>::value;
		};

		// special case(to avoid endless recursion with template instantiation)
		template<>
		struct IsPrime<0> { static constexpr bool value = false; };
		template<>
		struct IsPrime<1> { static constexpr bool value = false; };
		template<>
		struct IsPrime<2> { static constexpr bool value = true; };
		template<>
		struct IsPrime<3> { static constexpr bool value = true; };
	}

	// 8.2 computing with constexpr
	namespace computing_with_constexpr {

#if __cplusplus > 201403
		constexpr bool isPrime(unsigned p) {
			for (unsigned d = 2; d < p / 2;++d) {
				if (p % d == 0)
					return false;
			}
			return p > 1;// no divisor without remainder found
		}
#else
		constexpr bool doIsPrime(unsigned p, unsigned d) {
			return d != 2 ? (p % d != 0) && doIsPrime(p, d - 1)
				: (p % 2 != 0);
		}
		constexpr bool isPrime(unsigned p) {
			return p < 4 ? !(p < 2)
				: doIsPrime(p, p / 2);
		}


#endif
	}

	// 8.3 Execution Path Selection with Partial Specialization
	namespace exe_path_select_with_partial_specialization 
	{
#if 0
		template<typename SZ,bool b>
		struct Helper{

		};

		template<int SZ,bool isPrime(SZ)>
		struct Helper;

		template<int SZ>
		struct Helper<SZ, true>
		{

		};
		template<typename T,std::size_t SZ>
		long foo(std::array<T, SZ> const& coll) {
			Helper<SZ> h;
		}
#endif
	}

	// 8.4 SFINAE(Substitution Failure Is Not An Error)
	namespace SFINAE
	{
		template<typename T,unsigned N>
		std::size_t len(T(&)[N]) {
			return N;
		}
#if 1
		template<typename T>
		typename T::size_type len(T const& t) {
			return t.size();
		}
#else
		template<typename T>// decltype and comma operator
		auto len(T const& t) -> decltype( (void)t.size()), T::size_type() ) 
		{
			return t.size();
		}
#endif
	}

	// 8.5 Compile-Time if
	namespace Compile_time_if 
	{

		template<typename T,typename ...Args>
		void print(T const& firstArg, Args&&...args) 
		{
			std::cout << firstArg << "\t";
			if constexpr (sizeof...(args) > 0) {
				print(std::forward<Args>(args)...);
			}
			else {
				std::cout << "\n";
			}
		}

		template<typename T>
		void foo(T t) {
			if constexpr (std::is_integral_v<T>) {
				if (t > 0) {
					foo(t - 1);
				}
			}
			else {
				
				static_assert(false, "no intergral");// always asserts(even is discarded)
				static_asset(!std::is_integral_v<T>, "no intergral");// OK
			}
		}

	}
}

/*
*   8.6 Summary
*
* . Templates provide the ability to compute at compile time(using recursion
*    to iterate and partial specialization or operator ? : for slections).
*
* . With constexpr functions, we can replace most compile-time computation
*   with "ordinary functions" that are callable in compile-time contexts.
*
* . With partial specialization, we can choose between different implementation
*   of class templates based on certain compile-time constraints.
*
* . Templates are used only if needed and substitions in function template
*   declarations do not result in invalid code. This principle is called SFINAE
*   (substitution failure is not an error)
*
* . SFINAE can be used to provide function template only for certain types
*   and/or constraints.
*
* . Since C++17, a compile-time if allows us to enable or discard statements
*   according to compile-time conditions(even outside templates)
*
*/
void compile_time_programming_example();