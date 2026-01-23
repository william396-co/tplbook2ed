#include "Chapter11-GenericLibraries.h"

#include <thread>
#include <chrono>

void generic_lib_example() 
{
	using namespace Generic_Libraries;

	std::cout << __PRETTY_FUNCTION__ << "\n";

	{	// 11.1 Callables
		using namespace callables;

		{// 11.1.1 Supporting Function Objects
			using namespace supporting_func_obj;

			std::vector<int> primes = { 2,3,5,7,11,13,17,21,23 };

			foreach(primes.begin(), primes.end(), func);// function as callable(decay as pointer)
			foreach(primes.begin(), primes.end(), &func);// function pointer as callable
			foreach(primes.begin(), primes.end(), FuncObj());// function object as callable
			foreach(primes.begin(), primes.end(), [](auto i) {// lambda as callable
				std::cout << "lambda called for:" << i << "\n";
				});
		}

		{// 11.1.2 Dealing with Member Functions and Additional Arguments

			using namespace dealing_mem_fn_and_additional_args;

			std::vector<int> primes = { 2,3,5,7,11,13,17,21,23 };
			foreach(primes.begin(), primes.end(), [](std::string const& prefix,int i) {
				std::cout << prefix << i << "\n";
				},"-value:");

			MyClass obj;
			foreach(primes.begin(), primes.end(),
				&MyClass::memfunc,obj);
		}
		{// 11.1.3 Wrapping Function Calls

			using namespace wrapping_func_call;

			call([](std::string const&name,int i) {
				std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
				std::cout << name << " " << i << "\n";
				}, "hello", 42);

			auto ret = call([](std::string const& name, int i) {
				std::this_thread::sleep_for(std::chrono::milliseconds{ 300 });
				std::cout << name << " " << i << "\n";
				return name + std::to_string(i);
				}, "joe", 42);

			std::cout << ret << "\n";
		}
	}
	{// 11.2 Other Utilities to Implement Generic Libraries
		using namespace other_utilities_to_Impl_Generic_Libraries;
		{// 11.2.1 Type Traits
			using namespace type_traits;
			C<int> c;

			c.f(32);

		}
		{// 11.2.2 std::addressof()
			using namespace addressof_case;

		}
	}
	{// 11.3 Perfect Forwarding Temporaries
		using namespace perfect_forwarding_temporaries;
		std::string s = "hello";
		foo(s);
	}
	{	// 11.4 References as Template Parameters
		using namespace ref_as_template_param;
		int i;
		int& r = i;
		tmplParamIsReference(i);//false
		tmplParamIsReference(r);//false
		tmplParamIsReference<int&>(i);//true
		tmplParamIsReference<int&>(r);//true

		RefMem<int> rm1, rm2;
		rm2 = rm1;//Ok

#if 0
		RefMem<int&> rm3;// ERROR: invalid default value for N
		RefMem<int&, 0> rm4;
#else
		//RefMem<int&, null> rm5, rm6;
		//int null = 0;
		//rm5 = rm6;//ERROR: operator= is deleted due to reference memeber
#endif
	


		int size = 10;
#if 0
		Arr<int&, size> y;//compile-time ERROR deep in the code of class std::vector<>

		Arr<int, size> x;//ERROR: non-type template argument is not a constant expression
		x.print();
		size += 10; // OOP: modified SZ in Arr<>
		x.print();// run-time ERROR: invalid memory access: loops over 10 element;s
#endif
	}
}