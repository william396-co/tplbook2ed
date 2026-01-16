#include <iostream>

#include "../PartI-TheBasics/Chapter1-FunctionTemplates.h"
#include "../PartI-TheBasics/Chapter2-ClassTemplates.h"
#include "../PartI-TheBasics/Chapter3-NontypeTemplateParameters.h"
#include "../PartI-TheBasics/Chapter4-VariadicTemplates.h"
#include "../PartI-TheBasics/Chapter5-TrickyBasics.h"
#include "../PartI-TheBasics/Chapter6-MoveSemantic_EnableIf.h"
#include "../PartI-TheBasics/Chapter7-ByValueByRef.h"

//#include <cstdio>

int main() 
{
	std::cout << "C++ Template (second Edition)\n";

	//func_template_example();
	//class_template_example();
	//nontype_template_param_example();
	//variadic_template_example();
	//tricky_basics_example();
	//move_semantic_enable_if_example();
	by_value_or_by_ref_example();

	return 0;
}