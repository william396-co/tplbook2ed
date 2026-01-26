#pragma once

#include <iostream>
#include <string>

namespace Basic_template_terminology 
{

	// 10.1 "Class Template" or "Template Class"
	// 10.2 Subtitution, Instantiation, and Sepecialization
	namespace sub_ins_spec {
		template<typename T1,typename T2>// primary class template
		class MyClass {

		};

		template<>// explicit specialization
		class MyClass<std::string, float> {

		};

		template<typename T>// partial specialization
		class MyClass<T,T> {

		};
		template<typename T>// partial specialization
		class MyClass<bool,T> {

		};
	}

	// 10.3 Declaration versus Definitions
	namespace decl_vs_def 
	{
		class C;// a declaration of C as a class
		void f(int);// a declaration of f() as a function and int as a parameter type
		extern int v;// a declaration of v as a int variable

		// a declaration that is not definition
		template<typename T>
		void fun(T t);

		// a declaration also definition
		template<typename T>
		class S {};

		// 10.3.1. Complete versus InComplete Types
		namespace complete_vs_incomplete {
			/* 
			* Incomplete type are one of the following :
			*  . A class type that has been declared but not yet defined
			*  . An array type with an unspecified bound
			*  . An array type with an incomplete element type
			*  . void
			*  . An enumeration type as long as the underlying type or
			*    the enumeration values are no defined.
			*  . Any type above to which const/and or volatile are applied.			
			* 
			*/
			class CX;//CX is an incomplete type
#if 0
			CX const* cp;// cp is a pointer to an incomplete type
#endif
			extern CX elems[10];// elems has an incomplete type
			extern int arr[];// arr has an incomplete type

			class CX {};// CX now is a complete type(and therefore cp and elemes)
			          // no longer refer to incomplete type
		
		}
	}
	// 10.4 The One-Defintion Rule
	// 10.5 Template Argument versus Template Parameters
	namespace templateArg_vs_templatePara {
		template<typename T,int N>
		class ArrayInClass {
		public:
			T array[N];
		};
		class DoubleArrayInClass {
		public:
			double array[10];
		};

		/*
		*  It is essential to distinguish between "template parameters" and
		*   "template arguments". In short, you can say that "parameters are 
		*   initialized by arguments". Or more precisely:
		* 
		* . Template parameters are those names that are listed after the keyword
		*    template in the template declaration or definition(T and N int our example)
		* 
		* . Template arguments are the items that are substituted for template parameters
		*   (double and 10 in our example). Unlike template parameters, template arguments
		*   can be more than just "names".  
		*/

		template<typename T>
		class Dozen {
		public:
			ArrayInClass<T, 12> contents;// T is both template parameters and template arguments
		};
	}
}

/*
*  10.6 Summary
* 
* . Use class template, function template, and variable template for classes,functions,
*   and variables respectively, that are templates.
* 
* . Templates instantiation is the process of creating regular classes or function
*   by replacing template parameter with concrete arguments, The resulting entity
*   is a specialization.
* 
* . Types can be complete or incomplete.
* 
* . According to the one-defintion rule(ODR), nonline functions, member functions,
*   global variables, and static data members should be defined only once across
*   the whole program.
*/

void basic_template_terminology_example();