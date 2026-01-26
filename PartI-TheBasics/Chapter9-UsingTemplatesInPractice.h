#pragma once
#include <iostream>
#include <typeinfo>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_set>

namespace Using_Templates_In_Practice {

	class X{};

	// 9.1 The Inclusion Model
	namespace the_inclusion_model {

		// 9.1.1 Linker Error
		namespace linker_error {
			template<typename T>
			void printTypeof(T const&);
		}

		// 9.1.2 Templates In Header(inclusion model)
		namespace tempaltes_in_header {
			template<typename T>
			void printTypeof(T const& t) {
				std::cout << typeid(t).name() << "\n";
			}
		}
	}
	// 9.2 Templates and inline
	// 9.3 Precompiled Header(create a header file that include all *.h file)
	// 9.4 Decoding the Error Novel
	namespace Decode_the_error_novel
	{
		class Customer
		{
		public:
			explicit Customer(std::string const&  n)
				:name{ n }
			{
			}
			std::string getName()const { return name; }
		private:
			std::string name;
		};
	}
}

/*
*  9.6 Summary
* 
* . The inclusion model of templates is the most widely used model for 
*   organizing template of code, Alternatives are discussed in Chapter 14.
* 
* . Only full specializations of function templates need inline when defined
*   in header files outside classes or structures.
* 
* . To take advantage of precompiled headers, be sure to keep the same order
*   for #include directives.
* 
* . Debugging code with templates can be challenging.
*/
void using_templates_in_pratice_example();
