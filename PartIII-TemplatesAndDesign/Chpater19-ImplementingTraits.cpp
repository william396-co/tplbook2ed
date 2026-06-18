#include "Chpater19-ImplementingTraits.h"

#include <complex>


namespace implementing_traits {

	namespace value_trais {

#ifdef USE_VALUE_TRAITS
#if __cplusplus < 201703L//C++17
		BigInt const AccumulationTraits<BigInt>::zero = BigInt{ 0 };// initliazer here
#endif
#endif
	}
}

void implementing_traits_example() {
	using namespace implementing_traits;

	// 19.1 Am Example: Accumulating a Sequence
	{
		using namespace accumulating_a_sequeunce;
		// 19.1.1 Fixed Traits
		{
			using namespace fixed_traits;
			int num[] = { 1,2,3,4,5,6 };
			char name[] = "templates";
			int length = sizeof(name) - 1;

			{
				using namespace sample_1;
				std::cout << "the average value of the integer value is "
					<< accum(num, num + 6) / 6 << "\n";

				
				// (try to) print average character value
				std::cout << "the average value of the character in \""
					<< name << "\" is "
					<< accum(name, name + length) / length
					<< "\n";
			}
			{

				using namespace sample_2;
				std::cout << "the average value of the integer value is "
					<< accum(num, num + 6) / 6 << "\n";


				// (try to) print average character value
				std::cout << "the average value of the character in \""
					<< name << "\" is "
					<< accum(name, name + length) / length
					<< "\n";
			}
		}
		// 19.1.2 Value Traits
		{
			using namespace value_traits;
			int num[] = { 1,2,3,4,5,6 };
			char name[] = "templates";
			int length = sizeof(name) - 1;
			std::cout << "the average value of the integer value is "
				<< accum(num, num + 6) / 6 << "\n";


			// (try to) print average character value
			std::cout << "the average value of the character in \""
				<< name << "\" is "
				<< accum(name, name + length) / length
				<< "\n";
		}
		// 19.1.3 Parameterized Traits
		{
			using namespace parameterize_traits;
			int num[] = { 1,2,3,4,5,6 };
			char name[] = "templates";
			int length = sizeof(name) - 1;
			std::cout << "the average value of the integer value is "
				<< accum(num, num + 6) / 6 << "\n";


			// (try to) print average character value
			std::cout << "the average value of the character in \""
				<< name << "\" is "
				<< accum(name, name + length) / length
				<< "\n";
		}
	}

	// 19.2 Traits Versus Policies and Policy Classes
	{
		using namespace traits_vs_policies;

		int num[] = { 1,2,3,4,5 };
		std::cout << "the product of the integer values is "
			<< accum<int, MultiPolicy>(num, num + 5) // is 0, because init value is 0
			<< "\n";

		std::cout << "the summation of the integer values is "
			<< accum<int, SumPolicy>(num, num + 5) // is 0, because init value is 0
			<< "\n";

		// 19.2.2 Member Templates Versus Template Template Parameters
		{
			using namespace mem_tpl_vs_tpl_tpl_param;

			int num[] = { 1,2,3,4,5 };
			std::cout << "the summation of the integer values is "
				<< mem_tpl_vs_tpl_tpl_param::accum(num, num + 5) 
				<< "\n";
		}

		// 19.2.4 Accumulation with General Iterators
		{
			using namespace accum_with_general_iterators;

			int num[] = { 1,2,3,4,5,6,7 };
			std::cout << "the summation of the integer values is "
				<< accum(num, num + 5)
				<< "\n";
		}
	}
	// 19.3 Type Functions
	{
		using namespace type_function;

		std::cout << "TypeSize<int>::value = " << TypeSize<int>::value << "\n";
		// 19.3.1 Element Types
		{
			using namespace elem_types;
			std::vector<bool> s;
			printElementType(s);
			int arr[2];
			printElementType(arr);

			std::vector<int> vi = { 1,23,3,4 };
			std::cout << "SumOfElments(vi) = " << sumOfElements(vi) << "\n";
		}
		// 19.3.2 Transformation Traits
		{
			using namespace transformation_traits;

		}
	}

	// Concepts and Generic Programming
	{
		using namespace concept_generic_programming;

		std::list<int> l = { 1,2,2,3,4,5,6,76,7,7,8,8,8 };
		auto curl = l.begin();
		my_advance(curl, 4);

		std::cout << *curl << "\n";

		std::vector<int> v = { 1,2,2,3,4,5,6,76,7,7,8,8,8 };
		auto curv = v.begin();
		my_advance(curv, 4);
		std::cout << *curv << "\n";

#if 1
		static_assert(Equality_comparable<int>,"int is not comparable");
		static_assert(Equality_comparable<int, double>);
		static_assert(std::equality_comparable<int>);
		static_assert(std::equality_comparable_with<int, double>, "int is not comparable double");
#else
		//static_assert(Equality_comparable<S>, "S is not comparable");// fails
		//static_assert(Equality_comparable<int, std::string>, "int is not comparable to string");// fails
#endif

#if 1
		auto b1 = cmp(2, 3);// ok
		auto b3 = equal(2 + 3i, 3 + 4i); // ok
#else
		auto b0 = cmp(std::cout, std::cin);//error,ostream doesn't support ==
		auto b2 = cmp(2 + 3i, 3 + 4i);//error,complex<double> doesn't support<
#endif

		auto x1 = twice(5);
		std::string s= "Hello";
		//auto x2 = twice(s);// error
		auto x3 = thrice(s);//ok

		std::cout << x1 << " " << x3 << "\n";
	
		auto ch1 = open_channel("foo");// works with whatever open_channel() returns
		//Arithmetic auto ch2 = open_channel("foo");// error: a channel is not arithmetic
		Channel auto ch3 = open_channel("foo");// Ok, assuming Channel is an appropriate concept
											// and open_channel() returns one

		std::cout << ch1 << "  " << ch3 << "\n";


		print("hello", 3, 4);
		print_f("hello",',', "world",',', 2017);

		auto total = sum_f(2, 3, 4, 4, 5, 65.6);
		std::cout << total << "\n";

		auto xxx = foo(3);

	}
}	
