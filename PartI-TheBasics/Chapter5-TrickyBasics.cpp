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
	{// 5.5 Member Templates
		using namespace member_templates;
		Stack<int> iStk;
		iStk.push(1);
		iStk.push(2);

		Stack<double> dStk = iStk;		
		while (!dStk.empty()) {
			std::cout << dStk.top() << "\n";
			dStk.pop();
		}

		std::cout << "========================\n";

		Stack<float> fStk;
		fStk = iStk;
		while (!fStk.empty()) {
			std::cout << fStk.top() << "\n";
			fStk.pop();
		}

		Stack<std::string> sStk;
		Stack<std::string> sstk2;
		sstk2 = sStk;// default assigment operator still existed
#if 0
		fStk = sStk;//ERROR
#endif
		{
			using namespace Specialization_member_fun_templates;

			std::cout << std::boolalpha;

			BoolString s1("hello");
			std::cout << s1.getValue() << "\n";//print hello

			std::cout << s1.getValue<bool>() << "\n";// print false

			BoolString s2("on");
			std::cout << s2.getValue<bool>() << "\n";// print true

			BoolString s3("1");
			std::cout << s3.getValue<bool>() << "\n";// print true
		}
		{// 5.5.1 The .template Construct
			using namespace dot_template_construct;
			std::bitset<8> bs("010101");
			printBitset<8>(bs);
		}
		{// 5.5.2 Generic Lambdas and Member Templates
			using namespace generic_lambda_memeber_templates;
			auto ret = sum_lambda(3, 7);
			std::cout << ret << "\n";

			Sum sum;
			ret = sum(3, 4);
			std::cout << ret << "\n";
		}
	}
	{// 5.6 Variable Templates
		using namespace variable_templates;
		std::cout << pi<float> << "\n";
		std::cout << pi < float > << "\n";
		std::cout << pi<> << "\n";
		//std::cout << pi<int> << "\n";

		std::cout << dval<'c'> << "\n";
		arr<10>[0] = 42;
		for (size_t i = 0; i != arr<10>.size();++i) {
			std::cout << arr<10>[i] << "\n";
		}

		auto i = myMax<std::string>;
		std::cout << i << "\n";

		const int ii = 42;
		if constexpr (mystd::is_const_v<decltype(ii)>) {
			std::cout << "i is const value\n";
		}
		else {
			std::cout << "i is not const value\n";
		}
	}
	{// 5.7 Template Template Parameters
		using namespace template_template_param;

		Stack<int> iStack;
		Stack<float> fStack;

		iStack.push(1);
		iStack.push(2);
		std::cout << "iStack.top():" << iStack.top() << "\n";

		fStack.push(3.3);
		std::cout << "fStack.top():" << fStack.top() << "\n";

		fStack = iStack;
		fStack.push(4.4);
		std::cout << "fStack.top():" << fStack.top() << "\n";

		Stack<double, std::vector> vStack;
		vStack.push(5.5);
		vStack.push(6.6);
		std::cout << "vStack.top():" << vStack.top() << "\n";

		vStack = fStack;
		std::cout << "vStack:";
		while (!vStack.empty()) {
			std::cout << vStack.top() << "\t";
			vStack.pop();
		}
		std::cout << "\n";
	}
}
