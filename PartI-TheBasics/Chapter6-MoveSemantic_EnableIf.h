#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <type_traits>

namespace MoveSemantics_EnableIf
{

	// 6.1 Perfect Forwarding
	namespace perfect_forwarding
	{
		class X {};

		void g(X& x);
		void g(X const&);
		void g(X&&);

		namespace Case1 {
			// let f() forward argument val to g()
			void f(X& val);
			void f(X const& val);
			void f(X&& val);
		}
		namespace Case2 {
			template<typename T>
			void f(T&& val) {
				g(std::forward<T>(val));
			}
		}
	}

	// 6.2 Special Member Function Templates
	namespace special_mem_fun_templates
	{
		class Person {
		public:
			explicit Person(std::string const& name) :name{ name } {
				std::cout << "Copying string-Constructor for'" << name << "'\n";
			}
			explicit Person(std::string&& n) :name{ std::move(n) } {
				std::cout << "moving string-Constructor for'" << name << "'\n";
			}

			// copy and move constructor
			Person(Person const& other) :name{ other.name } {
				std::cout << "COPY-Constructor for'" << name << "'\n";
			}
			Person(Person&& other) :name{ std::move(other.name) } {
				std::cout << "MOVE-Constructor for'" << name << "'\n";
			}

		private:
			std::string name;
		};
	}
	// 6.3 Disable Templates with enable_if<>
	namespace disable_template_by_enableIf
	{
#if 0
		template<typename T>
		std::enable_if_t<(sizeof(T) > 4), T>
			foo() {
			std::cout << __PRETTY_FUNCTION__ << "\n";
		}
#else
#if __cplusplus >201403
		template<typename T>
		using EnableIfSizeGreater4 = std::enable_if_t < (sizeof(T) > 4)>;
#else
		template<typename T>
		using EnableIfSizeGreater4 = std::enable_if < (sizeof(T) > 4)>::type;
#endif

		template<typename T,
			typename = EnableIfSizeGreater4<T>>
			void foo()
		{
			std::cout << __PRETTY_FUNCTION__ << "\n";
		}
#endif
	}
	// 6.4 Using enable_if<>
	namespace using_enableIf
	{
#if __cplusplus > 201403
		template<typename T>
		using EnableIfString = std::enable_if_t <std::is_convertible_v<T, std::string>>;
#else
		template<typename T>
		using EnableIfString = std::enable_if<std::is_convertible<T, std::string>::value>::type;
#endif

		class Person {
		public:
			template<typename STR,
				typename = EnableIfString<STR>>
				explicit Person(STR&& n) :name(std::forward<STR>(n)) {
				std::cout << "TMPL-Constructo for'" << name << "'\n";
			}

			// copy and move constructor
			Person(Person const& other) :name{ other.name } {
				std::cout << "COPY-Constructor for'" << name << "'\n";
			}
			Person(Person&& other) :name{ std::move(other.name) } {
				std::cout << "MOVE-Constructor for'" << name << "'\n";
			}

		private:
			std::string name;
		};

		// Disabling Special Member Functions
		namespace disable_special_mem_fun
		{
			class C {
			public:
				C() {
					std::cout << "C constructor" << "\n";
				}
				C(C const volatile& T) = delete;

				template<typename T>
				C(T const& t) {
					std::cout << "tmpl copy constructor\n";
				}
			};
		}
	}
	// 6.5 Using Concepts to Simplify enable_if<> Expressions
	namespace using_concepts 
	{

		class Person {
		public:
#if 1
			template<typename STR>
			requires std::convertible_to<STR,std::string>
				explicit Person(STR&& n) :name(std::forward<STR>(n)) {
				std::cout << "TMPL-Constructo for'" << name << "'\n";
			}
#else
			template<typename T>
			concept Convertible2String = std::is_convertible_v<T, std::string>;

			template<Convertible2String STR>
			explicit Person(STR&& n) :name(std::forward<STR>(n)) {
				std::cout << "TMPL-Constructo for'" << name << "'\n";
			}
#endif

			// copy and move constructor
			Person(Person const& other) :name{ other.name } {
				std::cout << "COPY-Constructor for'" << name << "'\n";
			}
			Person(Person&& other) :name{ std::move(other.name) } {
				std::cout << "MOVE-Constructor for'" << name << "'\n";
			}

		private:
			std::string name;
		};
	}
}

/*
*  6.6 Summary
* 
* . In templates, you can "perfectly" forward parameters by declaring them 
*   forwarding reference(declared with a type formed with the name of a template
*   parameter followed by &&) and using std::forward<>() in the forwarded call.
* 
* . When using perfect forwarding member function templates, they might match
*   better than predefined special member function to copy or move objects.
* 
* . With std::enable_if<>, you can disable a function template when a compile-time
*   condition is false(the template is then ignored once that condition has 
*   been determined)
* 
* . By using std::enable_if<> you can avoid problems when constructor templates
*   or assignment operator templates that can be called for single argument are
*   a better match than implicity generated specail member functions.
* 
* . You can templify(and apply enable_if<>) to special member functions by deleting
*   the predefined special member functions for const volatile.
* 
* . Concepts will allow us to use a more intuitive syntax for requirements on 
*   function templates.
*/

void move_semantic_enable_if_example();