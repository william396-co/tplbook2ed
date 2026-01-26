#include "Chpater8-CompileTimeProgramming.h"

#include <array>
#include <string>
#include <vector>
#include <thread>

void compile_time_programming_example() {

	using namespace Compile_Time_Programming;
	{// 8.1 Template MetaProgramming
		using namespace template_meta_programming;

		std::cout << std::boolalpha;
		std::cout << "IsPrime<9> = " << IsPrime<9>::value << "\n";
		std::cout << "IsPrime<7> = " << IsPrime<7>::value << "\n";
		std::cout << "IsPrime<27> = " << IsPrime<27>::value << "\n";
	}
	{// 8.2 computing with constexpr
		using namespace computing_with_constexpr;
		std::cout << std::boolalpha;

		std::cout << "isPrime(9) = " << isPrime(9) << "\n";
		std::cout << "isPrime(7)= " << isPrime(7) << "\n";
		std::cout << "isPrime(27) = " << isPrime(27) << "\n";

		int x = 42;
		std::cout << "isPrime(" << x << ")=" << isPrime(x) << "\n";
	}
	{// 8.3 Execution Path Selection with Partial Specialization
		using namespace exe_path_select_with_partial_specialization;


	}
	{
		// 8.4 SFINAE(Substitution Failure Is Not An Error)
		using namespace SFINAE;
		int a[10];
		std::cout << len(a) << "\n";
		std::cout << len("emp") << "\n";


		std::array<int, 3> ar;
		len(ar);
		//std::cout << len(ar) << "\n";

		std::vector<int> vi;
		len(vi);
		//std::cout << len(vi) << "\n";

#if 0
		int* p;
		std::cout << len(p) << "\n";// ERROR: no matching len() function found		

		std::allocator<int> x;
		std::cout << len(x) << "\n";//ERROR: len() function found,  but can't size()
#endif
	}
	{// 8.5 Compile-Time if
		using namespace Compile_time_if;

		print("gello", 1, "goe", 4.5);

		print("hello", "world", "jacl");	

#if 1
		foo(1);
#else
		foo("hello");
#endif

		// constexpr can be used in any function, not only in templates
		if constexpr (std::numeric_limits<char>::is_signed) {
			foo(42);
		}
		else {
#if 0
			static_assert(false, "unsigned");//always asserts(event if discarded)
			static_assert(!std::numeric_limits<char>::is_signed, "char is unsigned");// OK
#endif
		}
	}
}