#pragma once


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
	}
}

void implementing_traits_example();