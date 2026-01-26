#include "Chapter9-UsingTemplatesInPractice.h"



void using_templates_in_pratice_example() 
{
	using namespace Using_Templates_In_Practice;
	{// 9.1 The Inclusion Model		
		using namespace the_inclusion_model;

		{// 9.1.1 Linker Error
			using namespace linker_error;
#if 0
			double ice = 3.0;
			printTypeof(ice);// linker error; undefined symbol printTypeof<double> 

			printTypeof(X{});// linker error; undefined symbol printTypeof<X>
#endif
		}

		{// 9.1.2 Templates In Header
			using namespace tempaltes_in_header;

			double ice = 3.2;
			printTypeof(ice);
			printTypeof(X{});
		}
	}
	{ // 9.4 Decoding the Error Novel
		using namespace Decode_the_error_novel;

#if 0
		std::map<std::string, double> coll;
		auto pos = std::find_if(coll.begin(), coll.end(),
			[](std::string const& s) {
				return s == "";
			});
#endif

		struct MyCustomerHash {
			std::size_t operator()(Customer const& c)const {
				return std::hash<std::string>()(c.getName());
			}
		};
		std::unordered_set<Customer, MyCustomerHash> coll;
#if 0
		//coll.emplace(std::string("jack"));
		Customer c("jaclk");
		coll.insert(std::move(c));
#endif
	}
}