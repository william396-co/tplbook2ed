#include "Chapter9-UsingTemplatesInPractice.h"

#include <iostream>
#include <typeinfo>

namespace Using_Templates_In_Practice {

	// 9.1 The Inclusion Model
	namespace the_inclusion_model {

		// 9.1.1 Linker Error
		namespace linker_error {
			template<typename T>
			void printTypeof(T const& t) {
				std::cout << typeid(t).name() << "\n";
			}
		}
	}
}