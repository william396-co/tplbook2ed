#include "aTourOfCpp.h"
#include <complex>
#include <ranges>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <memory>
#include <bitset>
#include <tuple>
#include <chrono>
#include <format>
#include <utility>
#include <functional>

namespace a_tour_of_cpp {

	namespace utilities {
		// source location
		void log(std::string const& mess, const std::source_location loc) {
			std::cout << loc.file_name()
				<< "(" << loc.line() << ":" << loc.column() << ")"
				<< loc.function_name() << ":"
				<< mess << "\n";
		}
	}
}

void a_tour_of_cpp_example() {
	using namespace a_tour_of_cpp;

	// Concepts and Generic Programming
	{
		using namespace concept_generic_programming;

		std::list<int> l = { 1,2,2,3,4,5,6,76,7,7,8,8,8 };
		auto curl = l.begin();
		my_advance(curl, 4);

		std::cout << *curl << "\n";

		std::vector<int> v = { 1,2,2,3,4,5,6,76,7,7,8,8,8 };
		auto curv = v.begin();
		my_advance(curv, 4);
		std::cout << *curv << "\n";

#if 1
		static_assert(Equality_comparable<int>, "int is not comparable");
		static_assert(Equality_comparable<int, double>);
		static_assert(std::equality_comparable<int>);
		static_assert(std::equality_comparable_with<int, double>, "int is not comparable double");
#else
		//static_assert(Equality_comparable<S>, "S is not comparable");// fails
		//static_assert(Equality_comparable<int, std::string>, "int is not comparable to string");// fails
#endif

#if 1
		auto b1 = cmp(2, 3);// ok
		auto b3 = equal(2 + 3i, 3 + 4i); // ok
#else
		auto b0 = cmp(std::cout, std::cin);//error,ostream doesn't support ==
		auto b2 = cmp(2 + 3i, 3 + 4i);//error,complex<double> doesn't support<
#endif

		auto x1 = twice(5);
		std::string s = "Hello";
		//auto x2 = twice(s);// error
		auto x3 = thrice(s);//ok

		std::cout << x1 << " " << x3 << "\n";

		auto ch1 = open_channel("foo");// works with whatever open_channel() returns
		//Arithmetic auto ch2 = open_channel("foo");// error: a channel is not arithmetic
		Channel auto ch3 = open_channel("foo");// Ok, assuming Channel is an appropriate concept
		// and open_channel() returns one

		std::cout << ch1 << "  " << ch3 << "\n";


		print("hello", 3, 4);
		print_f("hello", ',', "world", ',', 2017);

		auto total = sum_f(2, 3, 4, 4, 5, 65.6);
		std::cout << total << "\n";

		auto xxx = foo(3);
	}
	// Library Overview
	{

	}
	// String and Regular Expression
	{
		using namespace str_regular_exp;
		auto const ints = { 0, 1, 2, 3, 4, 5 };
		auto even = [](int i) { return 0 == i % 2; };
		auto square = [](int i) { return i * i; };

#if 1
		// the "pipe" syntax of composing the views:
		for (int i : ints | std::views::filter(even) | std::views::transform(square))
			std::cout << i << ' ';

		std::cout << '\n';
#else

		// a traditional "functional" composing syntax:
		for (int i : std::views::transform(std::views::filter(ints, even), square))
			std::cout << i << ' ';
#endif
		using namespace std::literals::string_literals;
		auto cat = "Cat"s;// a std::string
		auto dog = "Dog";//a C-style string: const char*

		using namespace std::literals::string_view_literals;

		auto s1 = cat_str(cat, dog);
		auto s2 = cat_str(cat, "william");
		auto s3 = cat_str(cat, cat);
		auto s4 = cat_str("Edward", "Stephen"sv);
		auto s5 = cat_str("Canute"sv, cat);
		auto s6 = cat_str({ &cat[0],2 }, "Henry"sv);
		auto s7 = cat_str({ &cat[0],2 }, { &cat[1],4 });

		std::cout << s1 << ", "
			<< s2 << ", "
			<< s3 << ", "
			<< s4 << ", "
			<< s5 << ", "
			<< s6 << ", "
			<< s7 << "\n";

		print_lower("HelloWord");


		// raw string literarls start with R"( and terminated by ")"
		std::regex pat{ R"(\w{2}\s*\d{5}(-\d{4})?)" };// U.S postal code pattern: XXdddd-dddd and variants

		std::regex pat2{ "\\w{2}\\s*\\d{5}(-\\d{4})?" };// same as before


		use();

		std::string s = "2332";
		std::cout << std::boolalpha << "[" << s << "] is " << is_identifier(s) << "\n";

		test();

		std::forward_list<int> flist;

		std::unordered_map<std::string, int> ump;
		auto i = ump["jac"];

		std::map<std::string, int> mp;
		auto j = mp["good"];
	}
	// Algorithm
	{
		using namespace algorithms;

		std::vector<int> vi = { 1,67,3,5,566,89 };
		std::ranges::sort(vi);// use ranges algorithm
		std::for_each(vi.begin(), vi.end(), [](auto x) {std::cout << x << ",";});
		std::cout << "\n";

		std::string m{ "Mary had a little lamb" };
		for (auto p : find_all(m, 'a')) {
			if (*p != 'a') {
				std::cerr << "A bug\n";
			}
			else
				std::cout << "correct found a\n";
		}

		{
			// ostream_iterator example code

			using namespace std::ranges;

#if 0
			std::ostream_iterator<std::string> oo{ std::cout };
			*oo = "Hello";
			++oo;
			*oo = "World\n";

			std::vector<std::string> v{ "good",",", "Evening\n" };
			copy(v, oo);// range copy version
#endif
		}
		{
			// istream_iterator example code

			using namespace std::ranges;

#if 0
			std::string from, to;
			std::cin >> from >> to;// get source and target file names

			std::ifstream is{ from };// input stream for file "from"
			std::istream_iterator<std::string> ii{ std::cin };// input iterator for stream
			std::istream_iterator<std::string> eos{};// input sentinel

			std::ofstream os{ to };// output stream for file "to"
			std::ostream_iterator<std::string> oo{ os,"\n" };// output iterator for stream plus a sperator

			std::vector<std::string> b{ ii,eos };// b is a vector initialize from input
			sort(b);//  sort the buffer(ranges sort version)

			unique_copy(b, oo);// copy the buffer to output, discard replicated values( ranges unique_copy version)
			//#else 
						// more elegant solution
						// It is a matter of taste and expericence whether or not this last simplication improves readablility
			std::ifstream is{ from };
			std::ofstream os{ to };

			std::set<std::string> b{ std::istream_iterator<std::string>{is},std::istream_iterator<std::string>{} };// read input
			copy(b, std::ostream_iterator<std::string>{os, "\n"});// copy to output

#endif
			//return !is.eof() || !os;
		}
	}
	// Concepts
	{
		//#define TEST_ASAN 
#ifdef TEST_ASAN
		int* p = new int(42);
		std::cout << *p << "\n";
		delete p;
		p = nullptr;
		std::cout << *p << "\n";
#endif

		using namespace concepts;


		// Views
		std::vector<int> vi{ 1,3,4,5,7,78,678 };
		user(vi);

		for (int x : take_view{ vi,3 }) {
			std::cout << x << "\t";
		}
		std::cout << "\n";
		for (int x : take_view{ filter_view{ vi,[](int x) {return x % 2;}},3 }) {
			std::cout << x << "\t";
		}
		std::cout << "\n";

		// Generators
		for (int x : iota_view(42, 53)) {
			std::cout << x << "\t";
		}
		std::cout << "\n";

#if 0
		for (auto x : istream_view<std::complex<double>>(std::cin)) {
			std::cout << x << "\t";
		}
		std::cout << "\n";

		auto cplx = istream_view<std::complex<double>>(std::cin);
		for (auto x : transform_view(cplx, [](auto z) {return z * z;})) {
			std::cout << x << "\t";
		}
		std::cout << "\n";
#endif

		// Pipelines(filter operator |)
		// filter() yields a filter_view
		auto vx = { 2,4,6,8,10,3,5,7,9,11,13,45 };
		auto odd = [](int x) {return x % 2;};
		for (int x : vx | views::filter(odd) | views::take(3)) {
			std::cout << x << "\t";
		}
		std::cout << "\n";


	}
	// Pointers and Containers
	{
		using namespace pointers_and_containers;

		auto sp = std::make_shared<X>();
		auto sp2 = sp->shared_from_this();


		int a[100];
		constexpr int x = 42;
		fpn(a);
		//fpn(a, 100);// error ,span expected
		print_fpn({ a + 10,90 });
		print_fpn({ a,x });

		std::bitset<122> bit;

		std::cout << bit.to_string() << "\n";

		std::pair<int, double> pd;

		std::tuple<int, double>tp = { 1,3.14 };
		auto const& [first, second] = tp;
		std::cout << first << " " << second << "\n";

		Node n = Expression{};
		check(&n);
		n = Statement{};
		check(&n);
		n = Declaration{};
		check(&n);
		n = Type{};
		check(&n);

		auto m = compose_message(true);
		const std::string& s = std::any_cast<std::string>(m);
		std::cout << s << "\n";
	}
	// Utilities
	{
		using namespace utilities;
		using namespace std::chrono;
		using namespace std::chrono_literals;

		// calendars
		auto spring_day = April / 7 / 2026;
		std::cout << weekday(spring_day) << "\n";//Tue
		std::cout << std::format("{:%A}\n", weekday(spring_day));// Tuesday ":%A" means week's full name

		auto bad_day = January / 0 / 2026;
		if (!bad_day.ok()) {
			std::cout << bad_day << " is not valid day\n";
		}

		sys_days t = sys_days{ February / 25 / 2022 };
		t += days{ 7 };
		auto d = year_month_day(t);
		std::cout << d << "\t";//2022-03-04
		std::cout << std::format("{:%B}/{}/{}\n", d.month(), d.day(), d.year()) << "\n";		//March/04/2022

		// timeZone

		auto tp = system_clock::now();
		std::cout << tp << "\n";//2026-07-06 09:35:09.3646677

		std::chrono::zoned_time ztp{ current_zone(),tp };
		std::cout << ztp << "\n";//2026-07-06 17:35:09.3646677 GMT+8

		const auto* est = std::chrono::locate_zone("Europe/Copenhagen");
		std::cout << std::chrono::zoned_time{ est,tp } << "\n";//2026-07-06 11:35:09.3646677 GMT+2

#if 0
		// Function Adapation
		std::vector<std::thread> ts;
		for (int i = 0; i != 10;++i) {
			ts.emplace_back([](auto i) {std::cout << std::this_thread::get_id() << "(" << i << ")\n";});
		}
		// lambdas as Adatptors
		std::for_each(ts.begin(), ts.end(), [](auto&& t) {t.join();});
		// mem_fn
		std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));
		//#else
				// function
		auto tt = [](std::thread& t) { t.join();};
		std::function<void(std::thread&)> fct1{ tt };
		std::for_each(ts.begin(), ts.end(), std::move(fct1));
#endif
		// source location
		log("Hello");

		// move and forward
		std::string s = "hello";
		auto p = std::move(s);

		std::vector<std::string> vi;
		vi.emplace_back(std::move(p));

		// bit Manipulation

		double val = 7.2;
		auto x = std::bit_cast<uint64_t>(val);
		auto y = std::bit_cast<uint64_t>(&val);
		std::cout << x << " " << y << "\n";

		auto [left, right] = GetRectRange(1);
		std::cout << left << " " << right << "\n";
	}

	// Concurrency
	{
		using namespace concurrency;
#if 0
		for (auto i : range(1, 100)) {
			std::cout << i << "\n";
		}
#endif
		int64_t x = 3;
		for (int i = 0; i != 10;++i) {
			if (--x < 1) {
				std::cout << x << "\n";
				break;
			}
			else
			{
				std::cout << x << "\n";

			}
		}
	}
}