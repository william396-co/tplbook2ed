#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <typeinfo>
#include <type_traits>
#include <ranges>
#include <cctype>
#include <regex>
#include <fstream>
#include <cstring>
#include <string>
#include <string_view>
#include <memory_resource>
#include <span>
#include <variant>
#include <any>
#include <source_location>
#include <bit>
#include <coroutine>
#include <optional>



namespace implementing_traits {

	namespace accumulation_trais {

		template<typename T>
		struct AccumulationTraits;

		class BigInt {
		public:
			BigInt(long long l) {}
		};

//#define USE_VALUE_TRAITS
#ifdef USE_VALUE_TRAITS
		template<>
		struct AccumulationTraits<char> {
			using AccT = int;
			static AccT const zero = 0;
		};

		template<>
		struct AccumulationTraits<short> {
			using AccT = int;
			static AccT const zero = 0;
		};

		template<>
		struct AccumulationTraits<int> {
			using AccT = long;
			static AccT const zero = 0;
		};

		template<>
		struct AccumulationTraits<unsigned int> {
			using AccT = unsigned long;
			static AccT const zero = 0;
		};

		template<>
		struct AccumulationTraits<float> {
			using AccT = double;
			static AccT constexpr zero = 0.0f;// float-point or literal types need use constexpr
		};

		template<>
		struct AccumulationTraits<BigInt> {
			using AccT = BigInt;
#if __cplusplus > 201703L//C++17
			inline static  AccT  const zero = BigInt{ 0 };// use inline variable Since C++17
#else
			static BigInt const zero;// declaration only
#endif
		};
#else	
		template<>
		struct AccumulationTraits<char> {
			using AccT = int;
			static AccT const zero() { return 0; }
		};

		template<>
		struct AccumulationTraits<short> {
			using AccT = int;
			static AccT const zero() { return 0; }
		};

		template<>
		struct AccumulationTraits<int> {
			using AccT = long;
			static AccT const zero() { return 0; }
		};

		template<>
		struct AccumulationTraits<unsigned int> {
			using AccT = unsigned long;
			static AccT const zero() { return 0; }
		};

		template<>
		struct AccumulationTraits<float> {
			using AccT = double;
			static AccT constexpr zero() { return 0; }
		};

		template<>
		struct AccumulationTraits<BigInt> {
			using AccT = BigInt;
			static AccT zero() {
				return BigInt{ 0 };
			}
		};
#endif
	}
	// 19.1 Am Example: Accumulating a Sequence
	namespace accumulating_a_sequeunce {

		// 19.1.1 Fixed Traits
		namespace fixed_traits {
			namespace sample_1 {
				template<typename T>
				T accum(T const* beg, T const* end)
				{
					T total{};// assume this actually create a zero value
					while (beg != end) {
						total += *beg;
						++beg;
					}
					return total;
				}
			}

			template<typename T>
			struct AccumulationTraits;

			template<>
			struct AccumulationTraits<char> {
				using AccT = int;
			};

			template<>
			struct AccumulationTraits<short> {
				using AccT = int;
			};

			template<>
			struct AccumulationTraits<int> {
				using AccT = long;
			};

			template<>
			struct AccumulationTraits<unsigned int> {
				using AccT = unsigned long;
			};

			template<>
			struct AccumulationTraits<float> {
				using AccT = double;
			};

			namespace sample_2 {
				template<typename T>
				auto accum(T const* beg, T const* end) {
					// return type is traits of the element type
					using AccT = typename AccumulationTraits<T>::AccT;

					AccT total{};// assume this actually create a zero value
					while (beg != end) {
						total += *beg;
						++beg;
					}
					return total;
				}
			}
		}
		// 19.1.2 Value Traits
		namespace value_traits {

			using namespace accumulation_trais;

			template<typename T>
			auto accum(T const* beg, T const* end) {
				// return type is traits of the element type
				using AccT = typename AccumulationTraits<T>::AccT;

#ifdef USE_VALUE_TRAITS
				AccT total= AccumulationTraits<T>::zero;// assume this actually create a zero value
#else
				AccT total = AccumulationTraits<T>::zero();
#endif
				while (beg != end) {
					total += *beg;
					++beg;
				}
				return total;
			}
		}
		// 19.1.3 Parameterized Traits
		namespace parameterize_traits {
			using namespace accumulation_trais;

			template<typename T,typename AT = AccumulationTraits<T>>
			auto accum(T const* beg, T const* end) {
				typename AT::AccT total = AT::zero();
				while (beg != end) {
					total += *beg;
					++beg;
				}
				return total;
			}
		}
	}
	// 19.2 Traits Versus Policies and Policy Classes
	namespace traits_vs_policies {
		using namespace accumulation_trais;

		class SumPolicy;//forward declaration

		template<typename T,
			typename Policy = SumPolicy,
			typename AT=AccumulationTraits<T>>
		auto accum(T const* beg, T const* end) {
			typename AT::AccT total = AT::zero();
			while (beg != end) {
				//total += *beg;
				Policy::accumulate(total, *beg);
				++beg;
			}
			return total;
		}

		class SumPolicy {
		public:
			template<typename T1,typename T2>
			static void accumulate(T1& total, T2 const& val) {
				total += val;
			}
		};

		class MultiPolicy {
		public:
			template<typename T1, typename T2>
			static void accumulate(T1& total, T2 const& val) {
				total *= val;
			}
		};

		// 19.2.1 Traits and Policies: What's the Difference?
		// 19.2.2 Member Templates Versus Template Template Parameters
		namespace mem_tpl_vs_tpl_tpl_param {
			template<typename T1,typename T2>
			class SumPolicy {
			public:
				static void accumulate(T1& total, T2 const& val) {
					total += val;
				}
			};

			template<typename T,
				template<typename,typename> class Policy = SumPolicy,
				typename Traits = AccumulationTraits<T>>
				auto accum(T const* beg, T const* end) {
				using AccT = typename Traits::AccT;
				AccT total = Traits::zero();
				while (beg != end) {
					Policy<AccT, T>::accumulate(total, *beg);
					++beg;
				}
				return total;
			}
		}
		// 19.2.3 Combing Multiple Policies and/or Traits
		// 19.2.4 Accumulation with General Iterators
		namespace accum_with_general_iterators {
			template<typename Iter>
			auto accum(Iter start, Iter end) {
				using VT = typename std::iterator_traits<Iter>::value_type;
				VT total{};//assume this actually create a zero value
				while (start != end) {
					total += *start;
					++start;
				}
				return total;
			}
		}
	}
	// 19.3 Type Functions
	namespace type_function {

		template<typename T>
		struct TypeSize {
			static std::size_t const value = sizeof(T);
		};

		// 19.3.1 Element Types
		namespace elem_types {
			template<typename T>
			struct ElementT;// primary template


			template<typename T>
			struct ElementT<std::vector<T>> {// partial specialization for std::vector
				using Type = T;
			};

			template<typename T>
			struct ElementT<std::list<T>> {// partial specialization for std::list
				using Type = T;
			};

			template<typename T, std::size_t N>
			struct ElementT<T[N]> {// partial specialization for array of known bounds
				using Type = T;
			};
			template<typename T>
			struct ElementT<T[]> {// partial specialization for array of known bounds
				using Type = T;
			};

			template<typename T>
			void printElementType(T const& c) {
				std::cout << "Container of " << typeid(typename ElementT<T>::Type).name()
					<< " element\n";
			}

			template<typename T>
			using ElementType = typename ElementT<T>::Type;

			template<typename C>
			ElementType<C> sumOfElements(C const& c) {
				ElementType<C> total{};
				for (auto const& i : c) {
					total += i;
				}
				return total;
			}
		}
		// 19.3.2 Transformation Traits
		namespace transformation_traits {

			// Removing References
			template<typename T>
			struct RemoveReferenceT {
				using Type = T;
			};
			template<typename T>
			struct RemoveReferenceT<T&> {
				using Type = T;
			};
			template<typename T>
			struct RemoveReferenceT<T&&> {
				using Type = T;
			};
			template<typename T>
			using RemoveReference = typename RemoveReferenceT<T>::Type;

			// Adding References
#if 0
			template<typename T>
			struct AddLValueReferenceT {
				using Type = T&;
			};

			template<typename T>
			struct AddRValueReferenceT {
				using Type = T&&;
			};

			template<typename T>
			using AddLValueReference = typename AddLValueReferenceT<T>::Type;


			template<typename T>
			using AddRValueReference = typename AddRValueReferenceT<T>::Type;
#else
			// apply reference collapsing rule(either if lvalue result it lvalue, both rvalue result is rvalue)
			template<typename T>
			using AddLValueReference = T&;
			template<typename T>
			using AddRvalueReference = T&&;
#endif


			inline void might_throw(bool b)noexcept
			{
				if (b) {
					throw 42;
				}
			}
		}
	}
}

void implementing_traits_example();
