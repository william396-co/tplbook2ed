#pragma once

#include <iostream>

namespace fundamental_in_depth {
	// 12.1 Parameterizaed Declarations
	namespace parameterized_decl {

		// class template
		template<typename T>
		class Data {
		public:
			static constexpr bool copyable = true;
		};

		// function template
		template<typename T>
		void log(T x) {

		}
		// variable template(Since C++14)
		template<typename T>
		T zero = 0;

		//alias template
		template<typename T>
		using DataList = Data<T*>;


		class Collection {
		public:
			template<typename T>// an in-class member class template definition
			class Node {

			};
			
			template<typename T>// an in-class(and therefor implicit inline)
			T* alloc() {         // member function template definition

			}

			template<typename T>// a member variable template
			static T zero = 0;

			template<typename T>// a member alias template
			using NodePtr = Node<T*>;
		};

		template<typename T>
		class List {
		public:
			List() = default;// because a template constructor is defined

			template<typename U>
			class Handle;// another member class template without definition

			template<typename U>
			List(List<U> const&);// a member function template (constructor)

			template<typename U>
			static U zero;// a member variable template(Since C++14)
		};
		
		template<typename T>
		template<typename U>
		inline List<T>::List(List<U> const&)// out-of-class member function template definition
		{
		}

		template<typename T>
		template<typename U>
		class List<T>::Handle {// out-of-class member class template definition

		};

		template<typename T>
		template<typename U>
		U List<T>::zero = 0;// out-of-class member variable template definition

		// Union Templates
		template<typename T>
		union AllockChunk {
			T Object;
			unsigned char bytes[sizeof(T)];
		};

		template<typename T>
		class Stack {};

		// Default Call Arguments
		template<typename T>
		void report_top(Stack<T> const&, int number = 0) {

		}

		template<typename T>
		class Array {};
		template<typename T>
		void fill(Array<T>&, T const & n= T()) {

		}

		class Value {
		public:
			explicit Value(int i) :val_{ i } {// no default constructor
			}
			Value() = default;
		private:
			int val_{};
		};

		inline void init(Array<Value>& array) {
			Value zero(0);
			fill(array, zero);//OK, default constructor not used
#if 1
			fill(array);// ERROR: undefine default constructor for Value is used
#endif
		}

		// Nontemplate Members of Class Templates
		template<int I>
		class CupBoard {
			class Shelf;// ordinary class in class template
			void open();// ordinary function in class template
			enum Wood : unsigned char;// ordinary enumeration type in class template
#if __cplusplus > 201703
			inline static double totalWeight = 0.0;
#else
			static double totalWeight;// ordinary static data member in class template
#endif
		};
		template<int I>
		class CupBoard<I>::Shelf {// definition of ordinary class in class template

		};

		template<int I>
		inline void CupBoard<I>::open()// definition of ordinary function in class template
		{
		}
		template<int I>
		enum CupBoard<I>::Wood: unsigned char {// definition of ordinary enumeration type in class template
			Maple,Cherry,Oak
		};


#if __cplusplus < 201703
		template<int I>// definition of ordinary static member in class template
		double CupBoard<I>::totalWeight = 0.0;
#endif
	}
}

void fundamental_in_depth_example();