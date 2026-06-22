#include <iostream>

#include "../PartI-TheBasics/Chapter1-FunctionTemplates.h"
#include "../PartI-TheBasics/Chapter2-ClassTemplates.h"
#include "../PartI-TheBasics/Chapter3-NontypeTemplateParameters.h"
#include "../PartI-TheBasics/Chapter4-VariadicTemplates.h"
#include "../PartI-TheBasics/Chapter5-TrickyBasics.h"
#include "../PartI-TheBasics/Chapter6-MoveSemantic_EnableIf.h"
#include "../PartI-TheBasics/Chapter7-ByValueByRef.h"
#include "../PartI-TheBasics/Chpater8-CompileTimeProgramming.h"
#include "../PartI-TheBasics/Chapter9-UsingTemplatesInPractice.h"
#include "../PartI-TheBasics/Chapter10-BasicTemplateTerminology.h"
#include "../PartI-TheBasics/Chapter11-GenericLibraries.h"

#include "../PartII-TemplatesInDepth/Chapter12-FundamentalsInDepth.h"

#include "../PartIII-TemplatesAndDesign/Chapter18-ThePolymorphicPowerOfTemplates.h"
#include "../PartIII-TemplatesAndDesign/Chpater19-ImplementingTraits.h"

//#include <cstdio>

int main() 
{
	std::cout << "C++ Template (second Edition)\n";

#if 0
	// PartI
	func_template_example();
	class_template_example();
	nontype_template_param_example();
	variadic_template_example();
	tricky_basics_example();
	move_semantic_enable_if_example();
	by_value_or_by_ref_example();
	compile_time_programming_example();
	using_templates_in_pratice_example();
	basic_template_terminology_example();
	generic_lib_example();
	// PartII
	fundamental_in_depth_example();
	// PartIII
	polymorphic_power_of_templates_example();
#else
	implementing_traits_example();
#endif

	getchar();

	return 0;
}