#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <typeinfo>
#include <type_traits>
#include <ranges>

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


	// Concepts and Generic Programming
	namespace concept_generic_programming {

		template<std::random_access_iterator iter>
		void my_advance(iter& p, int n) {
			p += n;
			std::cout << __FUNCTION__<<"(random_access_iterator)" << "\n";
		}
		
#if 1
		template<std::forward_iterator iter>
		void my_advance(iter& p, int n) {
			while (n--) {
				++p;
			}
			std::cout << __FUNCTION__ << "(forward_iterator)" << "\n";
		}
#else

		template<std::forward_iterator iter>
			requires requires(iter p, int i) { p[i], p + i; }
		void my_advance(iter& p, int n) {
			p += n;
			std::cout << __FUNCTION__ << "(forward_iterator requires())" << "\n";
		}
#endif

		// defintion of concepts

		template<typename B>
		concept Boolean =
			requires(B x, B y) {
				{ x == true };
				{ y = false };
				{ x = (x == y) };
				{ x = (x != y) };
				{ x = !x };
				{ x = (x = y) };
		};

		struct S {};
#if 0
		template<typename T>
		concept Equality_comparable =
			requires(T a, T b) {
				{ a == b } -> Boolean;
				{ a != b } -> Boolean;
		};
#else

		// handle nonhomogeneous comparision
		template<typename T,typename T2 = T>
		concept Equality_comparable =
			requires(T a, T2 b) {
				{ a == b }->Boolean;
				{ a != b }->Boolean;
				{ b == a }->Boolean;
				{ b != a }->Boolean;
		};
#endif

		template<typename T, typename U=T>
		concept Number =
			requires(T x, U y) {
			x + y;x - y;x* y;x / y;
			x += y; x -= y;x *= y;x /= y;
			x = x;
			x = 0;
		};

		template<typename T,typename U=T>
		concept Arithmetic = Number<T, U>&& Number<U, T>;

#if 0
		template<typename S>
		concept Sequence = requires(S a) {
			typename range_value_t<S>;
			typename iterator_t<S>;

			{ a.begin() }->std::same_as<iterator_t<S>>;
			{ a.end() }->std::same_as<iterator_t<S>>;

				requires std::input_iterator<iterator_t<S>>;
				requires std::same_as<range_value_t<S>, iter_value_t<S>>;
		};

		template<typename S>
		concept Sequence = std::input_range<S>;
#endif

	template<std::equality_comparable T>
	bool cmp(T a, T b) {
		return a < b;
	}
	template<std::equality_comparable T>
	bool equal(T a, T b) {
		return a == b;
	}

	auto twice(Arithmetic auto x) {// just for Arithmetic Number
		return x * x;
	}
	auto thrice(auto x) {// for anything with a+
		return x + x + x;
	}
	template<typename T>
	concept Channel =
		requires(T a){
		std::same_as<T, std::string>;
	};

	inline Channel auto open_channel(std::string const& name) {
		return std::string{ name + "channel" };
	}

	// Variadic template
	template<typename T>
	concept Printable = requires(T t) { std::cout << t; };// just one operation

	template<Printable T, Printable...Tail>
	void print(T head, Tail...tail) {
		std::cout << head << " ";
		if constexpr (sizeof...(tail) > 0) {
			print(tail...);
		}
		else
		{
			std::cout << "\n";
		}
	}

	// Fold Expression

	template<Printable...T>
	void print_f(T&&...args) {
		(std::cout << ...<< args) << "\n";
	}

	template<Number...T>
	int sum_f(T...v) {// right fold
		
		return (v + ... + 0);// add all elements of v starting with 0
		// the first element to be added is the "rightmost"
		// (v[0] + (v[1]+(v[2]+(v[3] +0)))
	}
	template<Number...T>
	int sum2(T...v) {// left fold
		return (0 + ... + v);//add all elements of v to 0
		// (((((0+v[0])+v[1])+v[2])+v[3])
	}

	// Forwarding argument

	// combine fold expression and forwarding
	//Scenario A: Logging/Validating each argument before forwarding
	template<typename... Args>
	void log_and_forward(Args&&... args) {
		// Fold expression with comma operator:
		// It calls log() for each argument IN ORDER (C++17 guarantees left-to-right),
		// while perfectly preserving rvalue/lvalue status via std::forward.
		(log(std::forward<Args>(args)), ...);

		// Then forward the whole pack to another function.
		target_function(std::forward<Args>(args)...);
	}
	//Scenario B: Pushing multiple perfectly-forwarded elements into a container
	template<typename T, typename... Args>
	void multi_push(std::vector<T>& vec, Args&&... args) {
		// Fold expression over the comma operator.
		// Calls vec.push_back(arg1), vec.push_back(arg2) ...
		// std::forward ensures if arg1 is a temporary, it gets moved into the vector.
		(vec.push_back(std::forward<Args>(args)), ...);
	}
	//Scenario C: Passing forwarded args to different functions
	template<typename... Args>
	void process_all(Args&&... args) {
		// Calls handler1 with arg1, handler2 with arg2, etc.
		(handler(std::forward<Args>(args)), ...);
	}

	constexpr auto foo(int v) {
		return v * v;
	}

	}
}

void implementing_traits_example();