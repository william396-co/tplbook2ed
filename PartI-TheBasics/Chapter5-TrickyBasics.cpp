#include "Chapter5-TrickyBasics.h"

#include <vector>

namespace Tricky_Basics {

}
void tricky_basics_example() {

	using namespace Tricky_Basics;

	{	// 5.1 keyword typename

		using namespace keyword_typename;
		std::vector<int> vi{ 1,23,5,6 };
		printColl(vi);
	}
	{// 5.2 Zero Initialization
		using namespace zero_initialization;
		foo<std::string>();
		bar<int>();
	}
	{// 5.3 Using this->
		using namespace using_this_arrow;
		Derived<int> d;
		d.foo();
	}
	{// 5.4 Templates for Raw Arrays and String Literals
		using namespace template_for_raw_array_and_string_literal;


		int x[] = { 0,8,15 };//

		int x1[] = { 1,2,3 };
		int x2[] = { 1,2,3,4,5 };
		std::cout << less(x1,x2) << "\n";

		std::cout << less("abc", "ab") << "\n";

		int a[42];
		MyClass<decltype(a)>::print();//use MyClass<T[SZ]>

		MyClass<decltype(x)>::print();// use MyClass<T[]>


		std::cout << "=====================\n";
		foo(a, a, a, x, x, x, x);


	}
}