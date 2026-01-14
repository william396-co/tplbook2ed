#include "Chapter4-VariadicTemplates.h"

#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <tuple>
#include <array>
#include <unordered_set>
#include <algorithm>

void variadic_template_example()
{
	using namespace VariadicTemplate;

	{// 4.1 Variadic Templates
		std::cout << "4.1 Variadic Templates\n";
		using namespace variadic_template;

		{// 4.1.1 Variadic Templates by Example
			using namespace V1;
			std::string str = "world";
			print("hello", 7.5, 42, str);			
		}

		{// 4.1.2 Overloading Variadic and NonVariadic Templates
			using namespace V2;

			std::string str = "world";
			print("hello", 7.5, 42, str);
			std::cout << "\n";
		}

		{// 4.1.3 Operator sizeof...
			using namespace V3;
			print("hello", 443, 34.45, 100);
		}
	}
	
	{ // 4.2 Fold Expression
		using namespace fold_expression;
		std::cout << "4.2 Fold Expression\n";

#if 0

		auto root = new Node(0);
		root->left = new Node{ 1 };
		root->right = new Node{ 2 };

		auto node = traverse(root, left, right);
#endif

		std::cout << foldSum(1, 3, 4, 5, 6, 7) << "\n";

		print("hello", 2, " world", 3.14159);
	}

	{// 4.3 Application of Variadic Templates
		using namespace app_of_variadic_template;

		auto sp = std::make_shared<complex<float>>(4.3, 7.6);
		
		std::thread t(foo, 42, "hello");
		t.join();
	}

	// 4.4 Variadic Class Templates and Variadic Expressions
	{
		using namespace variadic_class_variadic_expression;
		{// 4.4.1 Variadic Expressions
			using namespace variadic_expression;
			using namespace app_of_variadic_template;
			printDoubled(7.6, std::string("hello"), 3.45);

			addOne(4, 5, 6);

			if constexpr (isHomogeneous(43, -1, "hello")) {
				std::cout << "all params are same type\n";
			}
			else {
				std::cout << "Not same type params\n";
			}
	
			if constexpr (isHomogeneous("4", "- 1","", "hello")) {
				std::cout << "all params are same type\n";
			}
			else {
				std::cout << "Not same type params\n";
			}
		}

		{// 4.4.2 Variadic Indices
			using namespace variadic_indices;
			
			std::vector<std::string> coll = { "good","times","say","bye" };
			printElems(coll,2,0,3);

			printIdx<2,0,3>(coll);
		}

		{// 4.4.3 Variadic Class Template
			using namespace variadic_class_template;

#if 0
			Tuple<int, std::string, char> t;	

			Variant<int, std::string, char>v;

			std::array<std::string, 5> arr = { "hello","my","new","!","World" };
			printByIdx(arr, Indices<0, 4, 5, 3>);
#endif		

		}
		{ // 4.4.5 Variadic Base Classes and using
			using namespace variadic_base_class;

			using CusterOp = Overloader<CustomerEq, CustomerHash>;
			std::unordered_set<Customer, CustomerHash, CustomerEq> coll1;

			coll1.emplace("hello");
			coll1.emplace("good");

			std::unordered_set<Customer, CusterOp, CusterOp> coll2;
			coll2.emplace("hello");
			coll2.emplace("good");

			std::for_each(coll1.begin(), coll1.end(), [](auto const& obj) {
				std::cout << obj.getName() << "\t";
				});
			std::cout << "\n";

			std::for_each(coll2.begin(), coll2.end(), [](auto const& obj) {
				std::cout << obj.getName() << "\t";
				});
			std::cout << "\n";
		}
	}
}
