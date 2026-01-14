#include "Chapter6-MoveSemantic_EnableIf.h"

namespace MoveSemantics_EnableIf
{
	namespace perfect_forwarding
	{
		void g(X& x) {
			std::cout << "g() for variable\n";
		}
		void g(X const&) {
			std::cout << "g() for const variable\n";
		}
		void g(X&&) {
			std::cout << "g() for moveable object\n";
		}

		namespace Case1 {
			// let f() forward argument val to g()
			void f(X& val) {
				g(val);
			}
			void f(X const& val) {
				g(val);
			}
			void f(X&& val) {
				g(std::move(val));
			}
		}
	}
}


void move_semantic_enable_if_example() 
{
	using namespace MoveSemantics_EnableIf;

	// 6.1 Perfect Forwarding
	{
		using namespace perfect_forwarding;
		X v;
		X const c;
		{
			using namespace Case1;
			std::cout << "------------Case1---------\n";
			f(v);
			f(c);
			f(X());
			f(std::move(v));
		}
		{
			using namespace Case2;
			std::cout << "------------Case2---------\n";
			f(v);
			f(c);
			f(X());
			f(std::move(v));
		}
	}	
	// 6.2 Special Member Function Templates
	{	
		std::cout << " 6.2 Special Member Function Templates\n";
		using namespace special_mem_fun_templates;
		std::string s = "jack";
		Person p(s);
		Person p2("tmp");
		Person p3(p);

		Person p4(std::move(p));
	}
	// 6.3 Disable Templates with enable_if<>
	{
		std::cout << "6.3 Disable Templates with enable_if<>\n";
		using namespace disable_template_by_enableIf;

#if 0
		foo<char>();
		foo<int>();//error substitution failure
#else
		foo<double>();
		foo<long double>();
		foo<size_t>();
#endif
	}
	// 6.4 Using enable_if<>
	{
		std::cout << "6.4 Using enable_if<>\n";
		using namespace using_enableIf;
		std::string s = "jack";
		Person p(s);
		Person p2("tmp");
		Person p3(p);
		Person p4(std::move(p));

		// Disabling Special Member Functions
		{
			std::cout << "Disabling Special Member Functions\n";

			using namespace disable_special_mem_fun;
			C x;
			C y{ x };// use the member template
		}
	}
	// 6.5 Using Concepts to Simplify enable_if<> Expressions
	{
		using namespace using_concepts;		
		std::string s = "jack";
		Person p(s);
		Person p2("tmp");
		Person p3(p);
		Person p4(std::move(p));
	}
}