#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <type_traits>

namespace Generic_Libraries {

	// 11.1 Callables
	namespace callables {

		// 11.1.1 Supporting Function Objects
		namespace supporting_func_obj 
		{
			template<typename Iter, typename Callable>
			void foreach(Iter current, Iter end, Callable op) {
				while (current != end) {
					op(*current);
					++current;
				}
			}

			inline void func(int i) {
				std::cout << "func() called for:" << i << "\n";
			}

			struct FuncObj {
				void operator()(int i)const {// surrogate call function(代理调用)
					std::cout << "FuncObj::op() called for:" << i << "\n";
				}
			};
		}

		// 11.1.2 Dealing with Member Functions and Additional Arguments
		namespace dealing_mem_fn_and_additional_args 
		{
			template<typename Iter, typename Callable,typename ...Args>
			void foreach(Iter current, Iter end, Callable op,Args const&...args) 
			{
				while (current != end) {
					std::invoke(op, // call passed callable with 
						args...,    // any additional args(first arg as the this obj)
						*current);  // and the current element
					++current;
				}
			}

			class MyClass {
			public:
				void memfunc(int i)const {
					std::cout << "MyClass::memfunc() called for:" << i << "\n";
				}
			};
		}
		// 11.1.3 Wrapping Function Calls
		namespace wrapping_func_call {

			template<typename Callable,typename ...Args>
			decltype(auto) call(Callable&& op, Args...args) {

				std::cout << "start run----\n";
				if constexpr (std::is_same_v<std::invoke_result_t<Callable, Args...>, void>) {
					std::invoke(std::forward<Callable>(op),
						std::forward<Args>(args)...);
					std::cout << "finished run----\n";
				}
				else {
					decltype(auto) ret{ std::invoke(std::forward<Callable>(op),
						std::forward<Args>(args)...) };
					std::cout << "finished run----\n";
					return ret;
				}
			}
		}
	}

	// 11.2 Other Utilities to Implement Generic Libraries
	namespace other_utilities_to_Impl_Generic_Libraries {
		// 11.2.1 Type Traits
		namespace type_traits {

			template<typename T>
			class C {
				// ensure that T is not void(ignoring const or volatile)
				static_assert(!std::is_same_v<std::remove_cv_t<T>, void>,
					"invalid instantiation of class C for void type");
			public:
				template<typename V>
				void f(V&& v) {
					if constexpr (std::is_reference_v<T>) {
						// special code if T is a reference type
					}
					if constexpr (std::is_convertible_v<std::decay_t<V>, T>) {
						// special code if V is convertible to T
					}
					if constexpr (std::has_virtual_destructor_v<V>) {
						// special code if V has virtual destructor
					}
				}
			};
		}
		// 11.2.2 std::addressof()
		namespace addressof_case {
			template<typename T>
			void f(T&& x) {
				auto p = &x;// might fail with overload operator&
				auto q = std::addressof(x);// works even with overloaded operator&
			}
		}
		// 11.2.3 std::declval()
		// the std::declval() function template can be used as a placeholder for an object
		// reference of specific type.
		namespace declval_case {

			template<typename T1, typename T2,
				typename RT = std::decay_t<decltype(true ? std::declval<T1>() : std::declval<T2>())>>
			RT max(T1 a, T2 b)
			{
				return b < a ? a : b;
			}
		}
	}
	// 11.3 Perfect Forwarding Temporaries
	namespace perfect_forwarding_temporaries {

		inline const std::string& get(std::string const& str) {
			return str;
		}

		template<typename T>
		void set(T&& t) {
			std::cout << __PRETTY_FUNCTION__ << "\n";
		}

		template<typename T>
		void foo(T x) {

			auto&& val = get(x);

			// perfectly forward the return value of get() to set()
			set(std::forward<decltype(val)>(val));
		}
	}
	// 11.4 References as Template Parameters
	namespace ref_as_template_param {
		template<typename T>
		void tmplParamIsReference(T) {
			std::cout << std::boolalpha << "T is reference:" << std::is_reference_v<T> << "\n";
		}

		template<typename T, T N = T{}>
		class RefMem {
		public:
			RefMem() :zero{ N } {}
		private:
			T zero;
		};			

		extern int null;

		template<typename T,int& SZ>// Note: size is reference
		class Arr {
		public:
			Arr() :elems(SZ) {//use current SZ as initial vector size
			}
			void print()const {
				for (int i = 0; i != SZ;++i) {
					std::cout << elems[i] << " ";
				}
			}
		private:
			std::vector<T> elems;
		};
	}
	// Defer Evaluations
	namespace defer_evaluations 
	{
		template<typename T>
		class Cont {
		private:
			T* elems;

		public:
#if 0
			typename std::conditional_t<std::is_move_constructible_v<T>, T&&, T&>
				foo() {

			}
#else
			template<typename D = T>
			typename std::conditional_t<std::is_move_constructible_v<D>, T&&, T&>
				foo() {
				return T{};
			}
#endif
		};

		struct Node {
			std::string value;
			Cont<Node> next;// only possible if Cont accepts incomplete types
		};
	}

	/*
	*   11.6 Things to Consider When Writing Generic Libraries
	* 
	* . Use forwarding reference to forward values in templates. If the values 
	*   do not depend on template parameters,use auto&&
	* 
	* . When parameters are declared as forwarding references, be prepared that
	*   a template parameter has a reference type when passing lvalues
	* 
	* . Use std::addressof() when you need the address of an object depending on 
	*   a template parameter to avoid surprises when it binds to a type with 
	*   overloaded operator&
	* 
	* . For member fucntion templates, ensure that they don't match better than 
	*   the predefined copy/move constructor or assignment operator
	* 
	* . Consider using std::decay when template parameters might be string literals
	*   and not passed situation that const template arguments may be specified.
	* 
	* . If you have out or inout parameters depending on template parameters, be
	*   prepared to deal with the situation that const template arguments may be 
	*   specified
	* 
	* . Be prepared to deal with the side effects of template parameters being 
	*   references. In particual, you might want to ensure that the return type 
	*   can't become a reference.
	* 
	* . Be prepared to deal with incomplete types to support, for example, recursive
	*   data structures
	* 
	* . Overload for all array types and not just T[SZ]
	*/
}

/*
*   11.7 Summary
* 
* . Templates allow you to pass functions, function pointers, function objects, functors,
*   and lambdas as callables
* 
* . When defining classes with an overloaded operator(), declare it as const(unless the 
*   call changes its state).
*
* . With std::invoke(), you can implement code that can handle all callables,including 
*   member functions
* 
* . Use decltype(auto) to forward a return value perfectly.
* 
* . Type traits are type functions that check for properties and capablilities of types.
* 
* . Use std::addressof() when you need the address of an object in a template.
* 
* . Use std::declval() to create values of specific types in unevaluated expressions.
* 
* . Use auto&& to perfectly forward objects in generic code if their type does not depend
*   on template parameters.
* 
* . Be prepared to deal with the side effects of template parameters being references.
* 
* . You can use templates to defer the evaluation of expression(e.g., to support using
*   incomplete types in class templates). 
* 
*/

void generic_lib_example();