#pragma once

#include <iostream>
#include <deque>
#include <cassert>
#include <bitset>
#include <array>
#include <type_traits>
#include <memory>

namespace Tricky_Basics {

	// 5.1 keyword typename
	namespace keyword_typename
	{
		// print elements of an STL container
		template<typename T>
		void printColl(T const& coll) {
			typename T::const_iterator pos;
			typename T::const_iterator end(coll.end());
			for (pos = coll.begin();pos != end;++pos) {
				std::cout << *pos << ' ';
			}
			std::cout << "\n";
		}
	}

	// 5.2 Zero Initialization
	namespace zero_initialization
	{
		template<typename T>
		void foo() {
			T x;// x has undefined value if T is built-in type
			T y{};// y is zero(or false) if T is built-in type
			T z = T();// C++11
		}
#if __cplusplus > 201703
		template<typename T>
		class MyClass {
		private:
			T x;
		public:
			MyClass() :x{} {// ensure that x is initialized even for build
			}
		};
		template<typename T>
		class MyClass2 {
		private:
			T x{}; //zero-initialize x unless otherwise specified
		};

#else		
		template<typename T>
		class MyClass {
		private:
			T x;
		public:
			MyClass() :x() {// ensure that x is initialized even for build
			}
		};
#endif

#if 0
		template<typename T>
		void bar(T p{}) {// ERROR

		}
#else
		template<typename T>
		void bar(T p = {}) {

		}
#endif
	}
	// 5.3 Using this->
	namespace using_this_arrow 
	{
		template<typename T>
		class Base {
		public:
			void bar() {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
		};

		inline void bar() {
			std::cout << __PRETTY_FUNCTION__ << "\n";
		}

		template<typename T>
		class Derived : Base<T> {
		public:
			void foo() {
				bar();//calls extends bar() or error
				Base<T>::bar();// call base bar()
				this->bar();// same as Base<T>::bar()
			}

#if 0
			void bar() {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
#endif
		};
	}

	// 5.4 Templates for Raw Arrays and String Literals
	namespace template_for_raw_array_and_string_literal
	{
		template<typename T,int N,int M>
		bool less(T(&a)[N], int(&b)[M]) {
			for (int i = 0; i < N && i < M;++i) {
				if (a[i] < b[i])return true;
				if (b[i] < a[i])return false;
			}
			return N < M;
		}

		template<int N, int M>
		bool less(char const(&a)[N], char const(&b)[M]) {
			for (int i = 0; i < N && i < M;++i) {
				if (a[i] < b[i])return true;
				if (b[i] < a[i])return false;
			}
			return N < M;
		}

		template<typename T>
		struct MyClass;//primary template(forward declaration)

		template<typename T,std::size_t SZ>
		struct MyClass<T[SZ]> {
			static void print() {
				std::cout << "print() for T[" << SZ << "]\n";
			}
		};
		template<typename T,std::size_t SZ>
		struct MyClass<T(&)[SZ]> {
			static void print() {
				std::cout << "print() for T(&)[" << SZ << "]\n";
			}
		};
		template<typename T>
		struct MyClass<T[]>
		{
			static void print() {
				std::cout << "print() for T[]\n";
			}
		};
		template<typename T>
		struct MyClass<T(&)[]> {
			static void print() {
				std::cout << "print() for T(&)[]\n";
			}
		};
		template<typename T>
		struct MyClass<T*> {
			static void print() {
				std::cout << "print() for T*\n";
			}
		};

		extern int x[];// forward declare array

		template<typename T1,typename T2,typename T3>
		void foo(int a1[7], int a2[],// pointer by language rules
			int(&a3)[42],//reference to array of known bound
			int(&x0)[],// reference to array of unknown bound
			T1 x1,//passing by value decays
			T2& x2, T3&& x3)// passing by reference
		{
			MyClass<decltype(a1)>::print();// use MyClass<T*> 
			MyClass<decltype(a2)>::print();// use MyClass<T*>
			MyClass<decltype(a3)>::print();// use MyClass<T(&)[SZ]>
			MyClass<decltype(x0)>::print();// use MyClass<T(&)[]>
			MyClass<decltype(x1)>::print();// use MyClass<T*>
			MyClass<decltype(x2)>::print();// use MyClass<T(&)[SZ]>
			MyClass<decltype(x3)>::print();// use MyClass<T(&)[SZ]>
		}
	}

	// 5.5 Member Templates
	namespace member_templates 
	{
		template<typename T>
		class Stack {
		public:
			void push(T const& elem) {
				elems.push_back(elem);
			}
			void pop() {
				assert(!empty());
				elems.pop_back();
			}
			T const& top()const {
				assert(!empty());
				return elems.back();
			}
			bool empty()const { return elems.empty(); }

			// need define default constructor
			Stack() = default;
			// assign stack of elements of type U
			template<typename U>
			Stack& operator=(Stack<U> const& other);

			template<typename U>
			Stack(Stack<U> const& other) {
				elems.clear();
				elems.insert(elems.begin(),
					other.elems.begin(),
					other.elems.end());
			}

			// to get access private member of Stack<U> for any type U:
			template<typename>friend class Stack;
		private:
			std::deque<T> elems;
		};

		template<typename T>
		template<typename U>
		inline Stack<T>& Stack<T>::operator=(Stack<U> const& other)
		{
#if 0
			elems.clear();
			while (!tmp.empty()) {
				elems.push_front(tmp.top());
				tmp.pop();
			}
#else
			Stack<U> tmp(other);
			elems.clear();
			elems.insert(elems.begin(),
				other.elems.begin(),
				other.elems.end());
#endif
			return *this;
		}

		namespace Specialization_member_fun_templates {

			class BoolString {
			public:
				BoolString(std::string const& s) :value{ s } {}

				template<typename T = std::string>
				T getValue()const { return value; }// get value(convert to T)
			private:
				std::string value;
			};

			// full specialization for BoolString::getValue<>() for bool
			template<>
			inline bool BoolString::getValue<bool>()const {
				return value == "true" || value == "1" || value == "on";
			}
		}

		// 5.5.1 The .template Construct
		namespace dot_template_construct
		{
			template<unsigned long N>
			void printBitset(std::bitset<N> const& bs) {
				std::cout << bs.template to_string<char, std::char_traits<char>, std::allocator<char>>();
				std::cout << "\n";
			}
		}
		// 5.5.2 Generic Lambdas and Member Templates
		namespace generic_lambda_memeber_templates
		{
			auto sum_lambda = [](auto x, auto y) {
				return x + y;
				};

			class Sum {
			public:
				template<typename T1, typename T2>
				auto operator()(T1 x, T2 y)const {
					return x + y;
				}
			};
		}
	}
	// 5.6 Variable Templates
	namespace variable_templates
	{
		template<typename T = long double>
		constexpr T pi{ 3.1415926535897932385 };

		template<int N>
		std::array<int, N> arr{};// array with N elements,zero-initialized

		template<auto N>
		constexpr decltype(N) dval = N;// type of dvalue depends on passed value

		// Variable Templates for Data Members
		template<typename T>
		class MyClass {
		public:
			static constexpr int max = 1000;
		};

		template<typename T>
		int myMax = MyClass<T>::max;

		// Type Traits Suffix _v 
		namespace mystd {
			template<typename T>
			constexpr bool is_const_v = std::is_const<T>::value;// Since C++17
		}
	}
	// 5.7 Template Template Parameters
	namespace template_template_param
	{
#if 0
		template<typename T,
#if __cplusplus > 201103
			template<typename Elem> class Cont = std::deque >
#else
			template<typename Elem> typename Cont = std::deque > // ERROR beforec C++17
#endif
		class Stack {
		public:
			void push(T const& elem);
			void pop();
			T const& top()const;
			bool empty()const { return elems.empty(); }
		private:
			Cont<T> elems;
		};

		template<typename T,
			template<typename> class Cont>
		void Stack<T, Cont>::push(T const& elem) {
			elems.push_back(elem);
		}
		template<typename T,
			template<typename> class Cont>
		void Stack<T, Cont>::pop() {
			assert(!elems.empty());
			elems.pop_back();
		}
		template<typename T,
			template<typename> class Cont>
		T const& Stack<T, Cont>::top()const {
			assert(!elems.empty());
			return elems.back();
		}
#else
		template<typename T,
			template<typename Elem,typename = std::allocator<Elem>>
					class Cont = std::deque>
		class Stack {
			// to get access to private members of any stack with elements of type U
			template<typename,template<typename,typename>class>
			friend class Stack;
		public:
			// assign stack of elements of type U
			template<typename U,
					template<typename Elem2, typename = std::allocator<Elem2>>
						class Cont2>
			Stack<T, Cont>& operator=(Stack<U, Cont2> const& other);						
		public:
			void push(T const& elem);
			void pop();
			T const& top()const;
			bool empty()const { return elems.empty(); }
		private:
			Cont<T> elems;
		};

		template<typename T,
			template<typename, typename > class Cont>
		void Stack<T, Cont>::push(T const& elem) {
			elems.push_back(elem);
		}

		template<typename T,
			template<typename, typename > class Cont>
		void Stack<T, Cont>::pop() {
			assert(!elems.empty());
			elems.pop_back();
		}

		template<typename T,
			template<typename, typename > class Cont>
		T const& Stack<T, Cont>::top()const {
			assert(!elems.empty());
			return elems.back();
		}

		template<typename T,
			template<typename, typename > class Cont>

		template<typename U,
			template<typename, typename > class Cont2>
		Stack<T, Cont>& Stack<T, Cont>::operator=(Stack<U, Cont2>const& other) 
		{
			elems.clear();
			elems.insert(elems.begin(),
				other.elems.begin(),
				other.elems.end());
			return *this;
		}
#endif
	}
} 

/*
*  5.8 Summary
* 
* . To access a type name that depends on a template parameter,you have to qualify
*   the name with a leading typename.
* 
* . To access members of base classes that depend on template parameters, you have 
*   to qualify the acces by this-> or their class name.
* 
* . Nested classes and member functions can also be template, One application is the
*   ability to implement generic operations with internal type conversions.
* 
* .Template version of constructors or assignment operators don't replace predefined
*  constructors or assignment operators.
* 
* . By using brace initialization or explicitly calling a default constructor, you can 
*   ensure that virable and member of templates are initialized with a default value 
*   even if they instantiated with a built-in type.
* 
* . You can provide specific template for raw arrays, which can also be applicable to 
*   string literals. when passing raw array or string literals, arguments decay(perform
*   an array-to-pointer coversion) during argument deduction if and only if the parameter
*   is not a reference.
* 
* . You can define variable templates(Since C++14)
* 
* . You can also use class templates as template parameters, as template template parameters.
* 
* . Template template argument must usually match their parameter exactly.
* 
*/
void tricky_basics_example();