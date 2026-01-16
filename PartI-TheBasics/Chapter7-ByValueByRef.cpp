#include "Chapter7-ByValueByRef.h"



void by_value_or_by_ref_example() {

	using namespace by_value_or_by_ref;

	
	{// 7.1 Passing by Value
		using namespace passing_by_value;

		std::string s = "hi";
		printV(s);                   //[lvalue] copy constructor
		printV(std::string("jeo"));  //[prvalue] copying usually optimized away(if not, move constructor)
		printV(retStr());            //[prvalue] copying usually optimized away(if not, move constructor)
		printV(std::move(s));        //[xvalue] move constructor

		// Passing by Values Decays
		int arr[4];
		printV(arr);// printV(int*)
		printV("hello");// printV(const char*) decays to pointers so that arg has type char const*
	}
	{// 7.2 Passing by Reference
		using namespace passing_by_ref;

		{// 7.2.1 Passing by Constant Reference
			using namespace passing_by_const_ref;

			std::string s = "hi";
			printR(s);                   //no copy
			printR(std::string("jeo"));  //no copy
			printR(retStr());            //no copy
			printR(std::move(s));        //no copy

			int i = 42;
			printR(i);//passes reference instead of just copying i

			// Passing by Reference Does Not Decay
			printR("hi");// T deduced as char[3], arg is char const(&)[3]
			int arr[4];
			printR(arr);// T deduced as int[4], arg is int const(&)[4]
		}
		{// 7.2.2 Passing by Nonconstant Reference
			using namespace passing_by_nonconst_ref;


			std::string s = "hi";
#if 1
			outR(s);                   //Ok
#else
			outR(std::string("jeo"));  //ERROR
			outR(retStr());            //ERROR
			outR(std::move(s));        //ERROR
#endif

			int arr[4];
			outR(arr);//Ok, T deduce as int[4], arg is int(&)[4]

			// If you pass a const argument,
			const std::string c = "hi";
#if 0
			outR(c);
			outR(retCStr());
			outR(std::move(c));//OK T deduced as std::string const
			outR("hi");// OK T deduced as char const[3]
#endif
		}
	}
	{// 7.3 Passing by Forwarding Reference
		using namespace passing_by_forwarding_ref;
		
		std::string s = "hi";
		passR(s);                   //
		passR(std::string("jeo"));  //
		passR(retStr());            //
		passR(std::move(s));        //

		int arr[4];
		passR(arr);

		std::string c = "j";
		passR(c);
		passR("hi");
		
		int i = 42;
		passR(i);
		passR(42);
	}
	{// 7.4 Using std::ref() and std::cref()

		using namespace using_ref_cref;

		std::string s = "hello";
		printT(s);// print s pass by value
		printT(std::cref(s));// print s pass "as if by reference"

		printV(s);
#if 0
		printV(std::cref(s));//ERROR, no operator<< for reference wrapper defined
#endif

#if 0

		if (isLess(std::cref(s), "world")) {//ERROR

		}
		if (isLess(std::cref(s), std::string("world"))) {

		}
#else

		if (isLess(s, "world")) {//Ok
			std::cout <<"'"<< s << "' is Less than 'world'\n";
		}
		if (isLess(s, std::string("world"))) {
			std::cout << "'" << s << "' is Less than 'world'\n";
		}
#endif
	}
	{// 7.5 Dealing with String Literals and Raw Arrays
		using namespace dealing_string_literals_and_raw_arrays;

#if 0
		foo("hi", "guy");// ERROR
#else
		foo("hi", "hi");// compiles, but result not correct
#endif
		// 7.4.1 Special Implementations for String Literals and Raw Arrays
		{
			using namespace special_impl_string_and_arrays;

#if 0
			bar("hi", "guy");
			int arr1[4];
			int arr2[5];
			bar(arr1, arr2);
#endif
		}
	}
	{ // 7.5 Dealing with Return Value
		using namespace dealing_ret_val;
		auto ps = new std::string("whatever");
		auto& c = (*ps)[0];
		delete ps;
		std::cout << c << "\n";// run-time ERROR

		auto ss = std::make_shared<std::string>("whatever");
		auto& c2 = (*ss)[0];
		ss.reset();
		std::cout << c2 << "\n";// run-time ERROR

#if 0
		std::string s;
		auto retS = retR(s);//return is string&

		int x;
		auto retX = retV<int&>(x); // retT() instantiated for T as int&
#endif
	}
}