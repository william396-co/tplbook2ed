#include "Chapter10-BasicTemplateTerminology.h"


namespace Basic_template_terminology {

	namespace decl_vs_def {
		class C {// definition(and declaration) of class C

		};

		void f(int p) {// definition(and declaration) of function f()
			std::cout << "f(" << p << ")\n";
		}
		int v = 13;// an initializer makes this a definition for v

		int w;// global variable declarations not preceded by
		     // extern are also definitions
	}
}

void basic_template_terminology_example() {

	using namespace Basic_template_terminology;

	{ // 10.3 Declaration versus Definitions
		using namespace decl_vs_def;

		std::cout << v << "\n";


	}
	{
		using namespace templateArg_vs_templatePara;
		ArrayInClass<double, 10> ad;//<double,10> are template arguments
		ad.array[0] = 10.0;


		DoubleArrayInClass dd;
		dd.array[0] = 10.0;
	}
}