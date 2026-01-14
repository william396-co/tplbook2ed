#include "Chapter1-FunctionTemplates.h"


namespace FuncTamplate {

}

void func_template_example()
{
	std::cout << __FUNCTION__ << "\n";

	using namespace FuncTamplate;

	// 1.1 Using the Template
	{
		std::cout << "1.1 Using the Template\n";
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
		std::cout << "1.2 Template Argument Deduction\n";
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
		std::cout << "1.3 Multiple Template Parameters\n";
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
			auto m = max(3.3, 8);// double=(double,int)

		}

		{
			using namespace V5;
			int i = 42;
			int const& ir = i;//ir ir reference to i
			// auto always decays(ÍË»¯)
			auto a = ir;//a is declared as new object of tye int

			auto b = max(ir, 4.5);// double(int,double)
		}

		// 1.3.3 Return Type as Common Type
		{
			using namespace V6;
			auto m = max(37, 3.14);
		}

	}

	// 1.4 Default Template Argument
	{
		std::cout << " 1.4 Default Template Argument\n";
		using namespace Case4;
		{
			using namespace V1;
			auto a = max(4, 7.2);
		}
		{
			using namespace V2;
			auto b = max<double, int, long double >(7.2, 4);
		}
		{
			using namespace V3;
			int i = 3;
			long l = 5;
			max(i, l);// long(int,long)
			max<int>(4, 42);//int(int,int)
		}
	}

	// 1.5 Overloading Function Templates
	{
		std::cout << "1.5 Overloading Function Templates\n";
		using namespace Case5;
		{
			using namespace V1;
			// prefers the nontemplate over one generated from the template
			max(7, 42);//call the nontemplate for two ints
			max(7.0, 4.2);
			max('a', 'b');
			max<>(7, 42);
			max<double>(7, 42);
			max('a', 43.7);//call the nontemplate for two ints
		}

		{
			using namespace V2;
			auto a = max(4, 7.5);// use first version
			auto b = max<long, double>(7.3, 5);// use second version
#if 0
			auto c = max<int>(4, 7.5); // ERROR: both function templates match
#endif
		}

		{
			using namespace V3;
			int a = 7;
			int b = 42;
			auto m1 = max(a, b);

			std::string s1 = "hey";
			std::string s2 = "you";
			auto m2 = std::max(s1, s2);

			int* p1 = &b;
			int* p2 = &a;
			auto m3 = max(p1, p2);

			char const* x = "hello";
			char const* y = "world";
			auto m4 = max(x, y);
		}

		{
			using namespace V4;

			auto m1 = max(7, 42, 28);
			
			char const* s1 = "frederic";
			char const* s2 = "anica";
			char const* s3 = "lucas";
			auto m2 = max(s1, s2, s3);// run-time ERROR
		}

		{			
			using namespace V5;
			// ensure that all overloaded versions of a 
			// functions are visible when a corresponding is called
			max(45, 66, 67);//OOPS: use max<T>() instead of max(int,int)
		}
	}
}
