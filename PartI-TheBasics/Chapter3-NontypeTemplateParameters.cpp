#include "Chapter3-NontypeTemplateParameters.h"

void nontype_template_param_example()
{

	using namespace NontypeTemplateParameters;

	{// 3.1 Nontype Class Template Parameters
		std::cout << "3.1 Nontype Class Template Parameters";
		using namespace nontype_class_template_param;

		Stack<int, 20> int20Stk;
		Stack<int, 40> int40Stk;
		Stack<std::string, 10> str10Stk;

		int20Stk.push(3);
		std::cout << int20Stk.top() << "\n";
		int20Stk.pop();

		str10Stk.push("hello");
		str10Stk.push("world");
		while (!str10Stk.empty()) {
			std::cout << str10Stk.top() << "\n";
			str10Stk.pop();
		}
	}

	{ // 3.2 Nontype Function Template Parameters
		using namespace nontype_function_template_param;
		std::cout << "3.2 Nontype Function Template Parameters\n";
		
		std::vector<int> vi{ 1,2,3,4,5,6 };
		auto v2 = vi;
//#define USE_LAMBDA
#ifndef USE_LAMBDA
		std::transform(vi.begin(), vi.end(), vi.begin(),
			addVal<5, int>);
		std::transform(v2.begin(), v2.end(), v2.begin(),
			foo<3>);
#else
		std::transform(vi.begin(), vi.end(), vi.begin(),
			[](auto x) {return x + 5;});

		std::transform(v2.begin(), v2.end(), v2.begin(),
			[](auto x) {return x * 3;});
#endif
		std::for_each(vi.begin(), vi.end(),
			[](auto& i) {std::cout << i << "\t";});
		std::cout << "\n";


		std::for_each(v2.begin(), v2.end(),
			[](auto& i) {std::cout << i << "\t";});
		std::cout << "\n";
	}

	{// 3.3 Restriction for Nontype Template Parameters
		using namespace restriction_nontype_template_param;
		std::cout << "3.3 Restriction for Nontype Template Parameters\n";
#if 0
		MyClass2<"hello"> x;// const char[6] not match const char*

		char const s03[] = "hi";
		const char s11[] = "hi";// internal linkage
		MyClass2<s11> x1;// internal linkage
		MyClass2<s03> x3;// external linkage
#endif

#if __cplusplus > 201703
		static char const s17[] = "hello";
		MyClass2<s17> y17;// Ok, no linkage
#endif

		// Avoiding Invalid Expressions
		C<sizeof(int) + 4, sizeof(int) == 4> c;
#if 0
		C< 42, sizeof(int)> 4 > c1;// Error
#else
		C<42, (sizeof(int) > 4)> c2;//
#endif
	}

	{// 3.4 Template Parameter Type auto
		std::cout << "3.4 Template Parameter Type auto\n";

		using namespace template_param_type_auto;

		Stack<int, 20u> int20Stk;
		Stack<std::string, 40> str40Stk;

		int20Stk.push(3);
		std::cout << int20Stk.top() << "\n";
		auto size1 = int20Stk.size();

		str40Stk.push("hello");
		std::cout << str40Stk.top() << "\n";
		auto size2 = str40Stk.size();

#if __cplusplus > 201703
		if (!std::is_same_v<decltype(size1), decltype(size2)>) {
			std::cout << "size type differ\n";
		}
#else
		if (!std::is_same<decltype(size1), decltype(size2)>::value) {
			std::cout << "size type differ\n";
		}
#endif

#if 0
		Stack<int, 3.14> stk;//Error: Floating-point nontype argument
#endif

		Message<42> msg1;
		msg1.print();// initialize with int 42 and print that value

		static char const s[] = "hello";
		Message<s> msgs;// initialize with char const[6] "hello"
		msgs.print();// and print that value
	}
}
