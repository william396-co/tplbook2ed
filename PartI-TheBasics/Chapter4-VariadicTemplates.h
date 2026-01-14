#pragma once

#include <iostream>
#include <string>
#include <type_traits>

namespace VariadicTemplate 
{

	// 4.1 Variadic Templates
	namespace variadic_template 
	{
		// 4.1.1 Variadic Templates by Example
		namespace V1 {
			
			// to end the recursion, the nontype template overload of print()
			inline void print() {
				std::cout << "\n";
			}

			template<typename T,typename... Types>// Types specified by a template parameter pack
			void print(T firstArg, Types... args) // args...
			{
				std::cout << firstArg << '\t';
				print(args...);
			}
		}

		// 4.1.2 Overloading Variadic and NonVariadic Templates
		namespace V2 {
			template<typename T>
			void print(T arg) {
				std::cout << arg << "\t";
			}

			template<typename T,typename ...Args>
			void print(T firstArg, Args...args) {
				print(firstArg);
				print(args...);
			}
		}

		// 4.1.3 Operator sizeof...
		namespace V3 {

			inline void print() {
				std::cout << "\n";
			}

			template<typename T, typename ...Args>
			void print(T firstArg, Args...args) {
#if 0
				std::cout << sizeof...(Args) << "\n";
				std::cout << sizeof...(args) << "\n";
#endif
				std::cout << firstArg << "\t";
				if constexpr (sizeof...(args) >= 0) {
					print(args...);
				}
			}
		}
	}

	// 4.2 Fold Expression
	namespace fold_expression
	{
		template<typename... T>
		auto foldSum(T... s) {
			return (... + s);// ((s1+s2)+s3)...
		}
#if 0

		struct Node {
			int value;
			Node* left;
			Node* right;
			Node(int i = 0) :value(i), left{}, right{} {}
		};
		auto left = &Node::left;
		auto right = &Node::right;

		template<typename T, typename ...TP>
		Node* traverse(T np, TP...paths) {
			return (np ->* ...->*paths);
		}
#endif

		template<typename T>
		class AddSpace {
		public:
			AddSpace(T const& r) :ref{ r } {}
			friend std::ostream& operator<<(std::ostream& os, AddSpace<T> s) {
				return os << s.ref << '\t';
			}
		private:
			T const& ref;// refer to argument passed in constructor
		};


		template<typename...Types>
		void print(Types const&...args) {
			(std::cout << ... << AddSpace(args)) << "\n";
		}

		template<typename...Types>
		void printEx(Types const& ...args) {
			(std::cout << ... << args) << "\n";
		}
	}

	// 4.3 Application of Variadic Templates
	namespace app_of_variadic_template
	{
		template<typename T>
		class complex {
		public:
			complex(T real, double imag) :real{ real }, imag{ imag } {}
			friend std::ostream& operator<<(std::ostream& os, complex<T>& c) {
				return os << "[" << c.real << "," << c.imag << "]";
			}
			complex& operator+(complex<T> const other) {
				this->real = other.real;
				this->imag = other.imag;
				return *this;
			}
		private:
			T real;
			double imag;
		};

		inline void foo(int i, const char* str) {
			using namespace fold_expression;
			print(i, str);
		}	
	}

	// 4.4 Variadic Class Templates and Variadic Expressions
	namespace variadic_class_variadic_expression 
	{

		// 4.4.1 Variadic Expressions
		namespace variadic_expression
		{
			template<typename...T>
			void printDoubled(T const&...args) {
				using namespace fold_expression;
				print(args + args...);
			}

			template<typename...T>
			void addOne(T const&...args) {
				using namespace fold_expression;
#if 0
				print(args + 1...);//ERROR 1... is a literal with too many decimal point
#endif
				print(args + 1 ...);//OK
				print((args + 1)...);//OK
			}

			template<typename T1,typename ...TN>
			constexpr bool isHomogeneous(T1, TN...) {
				return (std::is_same_v<T1, TN> && ...);// Since C++17
			}
		}

		// 4.4.2 Variadic Indices
		namespace variadic_indices
		{
			template<typename C, typename...Idx>
			void printElems(C const& coll, Idx...idx) {
				using namespace fold_expression;
				print(coll[idx]...);
			}

			template<std::size_t...Idx, typename C>
			void printIdx(C const& coll) {
				using namespace fold_expression;
				print(coll[Idx]...);
			}
		}

		// 4.4.3 Variadic Class Template
		namespace variadic_class_template
		{
#if 0
			// This will discussed in Chapter25
			template<typename...Elements>
			class Tuple;

			// This will discussed in Chapter26
			template<typename ...Types>
			class Variant;


			// This will discussed in Chapter23
			template<std::size_t...>
			struct Indices {

			};
			template<typename T,std::size_t...Idx>
			void printByIdx(T t, Indices<Idx...>) {
				using fold_expression;
				print(std::get<Idx>(t)...);
			}
#endif
		}

		// 4.4.4 Variadic Deduction Guides
		namespace variadic_deduction_guides 
		{
#if 0
			namespace std {
				template<typename T, typename...U> array(T, U...)
					-> array(std::enable_if_t<(std::is_same_v<T, U> && ...), T>,
						(1 + sizeof...(U)) > ;
			}
#endif
		}

		// 4.4.5 Variadic Base Classes and using
		namespace variadic_base_class
		{
			class Customer {
			public:
				Customer(std::string const& n) :name{ n } {}
				std::string getName()const { return name; }
			private:
				std::string name;
			};

			struct CustomerEq {
				bool operator()(Customer const& lhs, Customer const& rhs)const {
					return lhs.getName() == rhs.getName();
				}
			};

			struct CustomerHash {
				std::size_t operator()(Customer const& obj)const {
					return std::hash<std::string>()(obj.getName());
				}
			};

			// define class that combines operator() for variadic base classs
			template<typename...Bases>
			struct Overloader : Bases...{
				using Bases::operator()...;// Ok, Since C++17
			};
		}
	}
}

/*
*   4.5 Summary
*  
* . By using parameter packs, templates can defined for an arbitrary number 
*   of template parameters of arbitrary type.
* 
* . To process the parameters, you need recursion and/or a matching 
*   novariadic function.
* 
* . Operator sizeof... yields the number of arguments provided for a parameter pack.
* 
* . A typical application of variadic templates is forwarding an arbitrary number
*   of arguments of arbitrary type
* 
* . By using fold expressions,you can apply operators to all arguments of a parameter pack.
*/

void variadic_template_example();
