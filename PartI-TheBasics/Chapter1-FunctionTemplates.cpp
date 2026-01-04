#include "Chapter1-FunctionTemplates.h"

#include <string>
#include <utility>

namespace FuncTamplate {

}

void func_template_example()
{
	std::cout << __FUNCTION__ << "\n";

	using namespace FuncTamplate;

	// 1.1 Using the Template
	{
		using namespace Case1;
		int i = 42;
		std::cout << "max(7,i)=" << max(7, i) << "\n";

		double f1 = 3.4;
		double f2 = -6.7;
		std::cout << "max(f1,f2)=" << max(f1, f2) << "\n";

		std::string s1 = "mathematics";
		std::string s2 = "math";
		std::cout << "max(s1,s2)=" << std::max(s1, s2) << "\n";

		f(nullptr);
		//f(i);
		f(f1);
		f(s1);
	}

	// 1.2 Template Argument Deduction
	{
		using namespace Case2;
		int i = 7;
		int const c = 42;
		max(i, c);// T = int
		max(c, c);// T = int
		int& r = i;
		max(i, r);
		int arr[4];
		foo(&i, arr);// T = int*

#if 0
		max(5, 7.3);//error
#else
		// spcifiy(or Qualify) explicitly the type of T to prevent
		// the compiler from attempting type deduction
		max<double>(5, 7.3);
		// Cast the argument so that they both match
		max(static_cast<double>(5), 7.3);
#endif
		std::string s;
#if 0
		foo("hello", s);//error
#else
		foo<std::string>("hello", s);
#endif
	}

	// 1.3 Multiple Template Parameters
	{
		using namespace Case3;
		{
			using namespace V1;
			auto m = max(5, 7.3);//T1 = int, T2 = double
		}

		{
			using namespace V2;
			auto m = max<int, double, double>(3, 8.6);//Ok,but tedious			
		}

		{
			using namespace V3;

			auto m = max<double>(1, 5.2);// ok, return type is double, T1 and T2 are deduced
		}

		// 1.3.2 Deducing the Return Type
		{
			using namespace V4;
			auto m = max(3.3, 8);// double=(double,double)

		}
	}
}
