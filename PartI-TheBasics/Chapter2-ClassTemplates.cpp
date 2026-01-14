#include "Chapter2-ClassTemplates.h"

#include <string>

namespace ClassTemplate {


}

void class_template_example() 
{
	std::cout << __PRETTY_FUNCTION__ << "\n";
	using namespace ClassTemplate;

	{ // 2.3 Partial Usage of Class Templates
		using namespace V1;
		std::cout << "2.3 Partial Usage of Class Templates\n";
		Stack<int> intStack;
		Stack<std::string> strStack;

		strStack.push("hello");
		std::cout << strStack.top() << "\n";
		strStack.pop();

		intStack.push(1);
		intStack.push(2);
		std::cout << intStack << "\n";
		
	}
	{  // 2.4 Friends
		using namespace V1;
		std::cout << "2.4 Friends\n";

		Stack<std::pair<int, int>> pStack;
		pStack.push({ 1,2 });
		pStack.push({ 3,4 });
		std::cout << pStack << "\n";
	}


	{// 2.5 Specialization of Class Templates
		std::cout << "2.5 Specialization of Class Templates\n";
		using namespace V1;
		Stack<std::string> strStk;
		strStk.push("good");
		std::cout << strStk.top() << "\n";
		strStk.pop();
	}

	{// 2.6 Partial Specialization
		using namespace V1;
		std::cout << "2.6 Partial Specialization\n";
		Stack<int*> ptrStk;
		ptrStk.push(new int{ 42 });
		std::cout << *ptrStk.top() << "\n";
		delete ptrStk.pop();
	}

	{// 2.7 Default Class Template Arguments
		std::cout << "2.7 Default Class Template Arguments\n";
		using namespace V3;
		Stack<int> intStk;

		Stack<double, std::deque<double>> dblStk;

		intStk.push(7);
		std::cout << intStk.top() << "\n";
		intStk.pop();

		dblStk.push(42.3);
		std::cout << dblStk.top() << "\n";
		dblStk.pop();
	}

	{// 2.8 Type Aliases
		std::cout << "2.8 Type Aliases\n";
		using namespace V3;
		using IntStack = Stack<int>;
		IntStack istack[10];
	}

	{// 2.9 Class Template Argument Deduction

		using namespace tmpl_Arg_Deduc;
		{
			using namespace Sub_V1;
			Stack<int> intStk1;
			Stack<int> intStk2 = intStk1;
#if __cplusplus > 201703L//C++17
			Stack intStk3 = intStk1;// deduce templater parameter

			Stack intStk = 0;

			//Stack strStk = "hello";//Stack<const char[6]> deduced Since C++17
			Stack strStk2 = std::string("hello");//Stack<std::string> deduced Since C++17			
#else
			Stack<int> intStk3 = intStk1;//C++11 C++14
#endif
		}
		{
			using namespace Sub_V2;				
			Stack<int> intStk1;
			Stack<int> intStk2 = intStk1;
#if __cplusplus > 201703L//C++17
			Stack intStk3 = intStk1;// deduce templater parameter

			Stack intStk = 0;

			Stack strStk = "hello";//Stack<const char*> deduced Since C++17
			Stack strStk2 = std::string("hello");//Stack<std::string> deduced Since C++17
			
#else
			Stack<int> intStk3 = intStk1;//C++11 C++14
#endif			
		}
		{// Deduction Guides
			using namespace Sub_V3;		
#if 0
			Stack strStack{ "bottom" };
			Stack strStk = "Bottom";
			//Stack stk2{ strStack };
			//Stack stk3 = { strStack };
#endif
		}
	}

	{// 2.10 Templatized Aggregates

		using namespace Templatized_Aggregates;
		ValueWithComment<int> vc;
		vc.value = 42;
		vc.comment = "initial value";

		ValueWithComment vc2 = { "hello","initial value" };

		std::cout << vc.value << " " << vc.comment << "\n";
		std::cout << vc2.value << " " << vc2.comment << "\n";
	}
}