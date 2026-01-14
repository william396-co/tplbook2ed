#pragma once

#include <array>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace NontypeTemplateParameters 
{
	// 3.1 Nontype Class Template Parameters
	namespace nontype_class_template_param 
	{
		template<typename T,std::size_t MaxSize>
		class Stack {
		public:
			Stack();
			void push(T const& elem);
			void pop();
			T const& top()const;
			bool empty()const { return 0 == numElems; }
			std::size_t size()const { return numElems; }
		private:
			std::array<T, MaxSize> data;// elements
			std::size_t numElems;// current number of elements
		};

		template<typename T, std::size_t MaxSize>
		Stack<T, MaxSize>::Stack() :numElems{ 0 }
		{
		}

		template<typename T, std::size_t MaxSize>
		void Stack<T, MaxSize>::push(T const& elem) 
		{
			assert(numElems < MaxSize);
			data[numElems++] = elem;
		}

		template<typename T, std::size_t MaxSize>
		void Stack<T, MaxSize>::pop() 
		{
			assert(numElems > 0);
			--numElems;
		}

		template<typename T, std::size_t MaxSize>
		T const& Stack<T, MaxSize>::top()const 
		{
			assert(numElems > 0);
			return data[numElems - 1];
		}
	}

	// 3.2 Nontype Function Template Parameters
	namespace nontype_function_template_param 
	{
		template<int Val,typename T>
		T addVal(T x) {
			return x + Val;
		}

		template<auto Val,typename T = decltype(Val)>
		T foo(T x) {
			return Val *x;
		}
	}

	// 3.3 Restriction for Nontype Template Parameters
	namespace restriction_nontype_template_param
	{
		// Floating-point number and class-type objects are not 
		// allowed as nontype template parameters
#if 0
		template<double VAT>
		double process(double v) {
			return v * VAT;
		}

		template<typename std::string>
		class MyClass {

		};
#endif
#if __cplusplus > 201703
		template<char const* name>
		class MyClass2 {

		};
#endif
		extern char const s03[];//external linkage



		template<int I, bool B>
		class C {};	
	}

	// 3.4 Template Parameter Type auto
	namespace template_param_type_auto 
	{
		template<typename T,auto MaxSize>
		class Stack {
		public:
			using size_type = decltype(MaxSize);
			Stack();
			void push(T const& elem);
			void pop();
			T const& top()const;
			bool empty()const { return 0 == numElems; }
#if __cplusplus > 201403
			auto size()const { return numElems; }
#else
			size_type size()const { return numElems; }
#endif
		private:
			std::array<T, MaxSize> data;
			size_type numElems;
		};
		template<typename T, auto MaxSize>
		Stack<T,MaxSize>::Stack():numElems{0}
		{ }

		template<typename T, auto MaxSize>
		void Stack<T, MaxSize>::push(T const& elem)
		{
			assert(numElems < MaxSize);
			data[numElems++] = elem;
		}

		template<typename T, auto MaxSize>
		void Stack<T, MaxSize>::pop()
		{
			assert(numElems > 0);
			--numElems;
		}

		template<typename T, auto MaxSize>
		T const& Stack<T, MaxSize>::top()const
		{
			assert(numElems > 0);
			return data[numElems - 1];
		}

		template<auto T>// take valuee of any possible nontype parameter(Since C++17)
		class Message {
		public:
			void print() {
				std::cout << T << "\n";
			}
		};
	}
}

/*
*  3.5 Summary
* 
* . Templates can have template parameters that are values rather than types.
* 
* . You cannot use floating-point numbers or class-type objects as arguments 
*   for nontype template parameters. For pointer/reference to string literals, 
*   temporiaries, and subobjects, restriction applys.
* 
* . Use auto enables template to have nontype template parameters that
*   values of generic types.
* 
*/
void nontype_template_param_example();