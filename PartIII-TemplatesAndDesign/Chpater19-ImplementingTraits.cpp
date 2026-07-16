#include "Chpater19-ImplementingTraits.h"

#include <complex>
#include <ranges>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <memory>
#include <bitset>
#include <tuple>
#include <chrono>
#include <format>
#include <utility>
#include <functional>

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
}	

