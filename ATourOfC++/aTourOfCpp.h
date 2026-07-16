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

namespace a_tour_of_cpp {

	// Concepts and Generic Programming
	namespace concept_generic_programming {

		template<std::random_access_iterator iter>
		void my_advance(iter& p, int n) {
			p += n;
			std::cout << __FUNCTION__ << "(random_access_iterator)" << "\n";
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
		template<typename T, typename T2 = T>
		concept Equality_comparable =
			requires(T a, T2 b) {
				{ a == b }->Boolean;
				{ a != b }->Boolean;
				{ b == a }->Boolean;
				{ b != a }->Boolean;
		};
#endif

		template<typename T, typename U = T>
		concept Number =
			requires(T x, U y) {
			x + y;x - y;x* y;x / y;
			x += y; x -= y;x *= y;x /= y;
			x = x;
			x = 0;
		};

		template<typename T, typename U = T>
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
			requires(T a) {
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
			(std::cout << ... << args) << "\n";
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
	// Library Overview
	namespace lib_overview {

	}
	//String and Regular Expression
	namespace str_regular_exp {

		inline std::string cat_str(std::string_view sv1, std::string_view sv2) {
			std::string res(sv1);
			return res += sv2;
		}

		inline void print_lower(std::string_view sv) {
			for (auto const& c : sv) {
				std::cout << static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
			}
		}

		// regular expression sample
		inline void use() {

			std::ifstream in("file.txt");
			if (!in) {
				std::cerr << "no file\n";
				return;
			}

			std::regex pat{ R"(\w{2}\s*\d{5}(-\d{4})?)" };

			int lineno = 0;
			for (std::string line; std::getline(in, line);) {
				++lineno;
				std::smatch matches;
				if (std::regex_search(line, matches, pat)) {
					std::cout << lineno << ": " << matches[0] << "\n";
					if (1 < matches.size() && matches[1].matched) {
						std::cout << "\t" << matches[1] << "\n";
					}
				}
			}

		}

		inline bool is_identifier(std::string const& s) {
			std::regex pat{ "[_[:alpha:]]\\w*" };
			return std::regex_match(s, pat);
		}
		inline void test() {
			std::string input = "aa as; asd+ee^asdf asdfg";
			std::regex pat{ R"(\s+(\w+))" };
			for (std::sregex_iterator p(input.begin(), input.end(), pat); p != std::sregex_iterator{};++p) {
				std::cout << (*p)[1] << "\n";
			}

		}
	}
	// Containers
	namespace containers {
		// Allocator

#if 0
		extern std::pmr::synchronized_pool_resource pool;
		struct Event {
			std::vector<int> data = std::vector<int>{ 512,&pool };
			std::pmr::vector<int> data{ 512,std::pmr::polymorphic_allocator<int>(pool) };
		};
		std::list<std::shared_ptr<Event>> q{ &pool };
#endif
	}
	// Algorithms
	namespace algorithms {

		template<typename C, typename V>
		std::vector<typename C::iterator> find_all(C& c, V v) {
			std::vector<typename C::iterator> res;
			for (auto p = c.begin(); p != c.end();++p) {
				if (*p == v) {
					res.push_back(p);
				}
			}
			return res;
		}
	}
	// Concepts
	namespace concepts {
		using namespace std::ranges;
		inline void user(forward_range auto& r) {

			filter_view v{ r,[](int x) {return x % 2;} };
			std::cout << "odd numbers:";
			for (auto const& i : v) {
				std::cout << i << " ";
			}
			std::cout << "\n";
		}

		struct Reading {
			int location{};
			int temperature{};
			int humidity{};
			int air_pressure{};
		};

	}
	// Pointers and Containers
	namespace pointers_and_containers {
		class X : public std::enable_shared_from_this<X> {
		public:
			X() {
				std::cout << __FUNCTION__ << "\n";
			}
			~X() {
				std::cout << __FUNCTION__ << "\n";
			}
		};

		inline void fpn(std::span<int> p) {
			for (int i = 0; i != p.size();++i)
			{
				p[i] = i * i;
			}
		}
		inline void print_fpn(std::span<int> p) {
			for (auto const& i : p) {
				std::cout << i << "\t";
			}
			std::cout << "\n";
		}

		struct Expression {};
		struct Statement {};
		struct Declaration {};
		struct Type {};
		using Node = std::variant<Expression, Statement, Declaration, Type>;

		template<typename...Ts>
		struct overloaded :public Ts...{// variadic template
			using Ts::operator()...;
		};
		template<typename...Ts>
		overloaded(Ts...) -> overloaded<Ts...>;// deduction guide

		inline void check(Node* p) {
			std::visit(overloaded{
				[](Expression& e) {std::cout << " p is Expression\n";},
				[](Statement& s) {std::cout << " p is Statement\n";},
				[](Declaration& d) {std::cout << " p is Declaration\n";},
				[](Type& t) {std::cout << " p is Type\n";}
				}, *p);
		}

		inline std::any compose_message(bool no_problem) {
			if (no_problem) {
				return std::string("no problem");
			}
			else {
				return 42;
			}
		}
	}
	// Utilities
	namespace utilities {

		// source location
		void log(std::string const& mess = "", const std::source_location loc = std::source_location::current());

		inline  std::pair<int, int> GetRectRange(int x)
		{
			std::pair<int, int> ret = { -x / 2,x / 2 };
			if (x % 2 != 0) { // ÆæÊý
				return ret;
			}
			else {
				return{ ret.first + 1,ret.second };
			}
		}
	}
	// Concurrency
	namespace concurrency {
#if 0

		template<std::movable T>
		class Generator
		{
		public:
			struct promise_type
			{
				Generator<T> get_return_object()
				{
					return Generator{ Handle::from_promise(*this) };
				}
				static std::suspend_always initial_suspend() noexcept
				{
					return {};
				}
				static std::suspend_always final_suspend() noexcept
				{
					return {};
				}
				std::suspend_always yield_value(T value) noexcept
				{
					current_value = std::move(value);
					return {};
				}
				// Disallow co_await in generator coroutines.
				void await_transform() = delete;
				[[noreturn]]
				static void unhandled_exception() { throw; }

				std::optional<T> current_value;
			};

			using Handle = std::coroutine_handle<promise_type>;

			explicit Generator(const Handle coroutine) :
				m_coroutine{ coroutine }
			{
			}

			Generator() = default;
			~Generator()
			{
				if (m_coroutine)
					m_coroutine.destroy();
			}

			Generator(const Generator&) = delete;
			Generator& operator=(const Generator&) = delete;

			Generator(Generator&& other) noexcept :
				m_coroutine{ other.m_coroutine }
			{
				other.m_coroutine = {};
			}
			Generator& operator=(Generator&& other) noexcept
			{
				if (this != &other)
				{
					if (m_coroutine)
						m_coroutine.destroy();
					m_coroutine = other.m_coroutine;
					other.m_coroutine = {};
				}
				return *this;
			}

			// Range-based for loop support.
			class Iter
			{
			public:
				void operator++()
				{
					m_coroutine.resume();
				}
				const T& operator*() const
				{
					return *m_coroutine.promise().current_value;
				}
				bool operator==(std::default_sentinel_t) const
				{
					return !m_coroutine || m_coroutine.done();
				}

				explicit Iter(const Handle coroutine) :
					m_coroutine{ coroutine }
				{
				}

			private:
				Handle m_coroutine;
			};

			Iter begin()
			{
				if (m_coroutine)
					m_coroutine.resume();
				return Iter{ m_coroutine };
			}

			std::default_sentinel_t end() { return {}; }

		private:
			Handle m_coroutine;
		};
		template<std::integral T>
		Generator<T> range(T first, const T last)
		{
			while (first < last)
				co_yield first++;
		}

		Generator<long long> fib() {

			long long a = 0;
			long long b = 1;
			while (a < b) {
				auto next = a + b;
				co_yield next;
				a = b;
				b = next;
			}
			co_yield 0;
		}
#endif

	}
}


void a_tour_of_cpp_example();