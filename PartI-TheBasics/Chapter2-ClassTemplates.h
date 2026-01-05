#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <deque>

namespace ClassTemplate {

	namespace V1 {
		template<typename T>
		class Stack {
		public:
			void push(T const& elem);
			void pop();
			T const& top()const;
			bool empty()const { return data.empty(); }
			void printOn(std::ostream& os)const;
			template<typename U>
			friend std::ostream& operator<<(std::ostream& os, Stack<U> const& stk);
		private:
			std::vector<T> data;
		};

		template<typename T>
		std::ostream& operator<<(std::ostream& os, std::pair<T, T> const& p) {
			os << "[" << p.first << "," << p.second << "]";
			return os;
		}

		template<typename U>
		std::ostream& operator<<(std::ostream& os, Stack<U> const& stk) {
			stk.printOn(os);
			return os;
		}

		template<typename T>
		inline void Stack<T>::push(T const& elem)
		{
			data.push_back(elem);
		}

		template<typename T>
		inline void Stack<T>::pop()
		{
			assert(!data.empty());
			data.pop_back();
		}

		template<typename T>
		inline T const& Stack<T>::top() const
		{
			assert(!data.empty());
			return data.back();
		}

		template<typename T>
		inline void Stack<T>::printOn(std::ostream& os) const
		{
			for (T const& elem : data) {
				os << elem << ' ';
			}
		}

		// 2.3 Concepts
		namespace Check_Constraints {
			template<typename T>
			class C {
				static_assert(std::is_default_constructible<T>::value,
					"Class C Requires default-constructible elements");
			};
		}

		// 2.5 Specialization of class Temples
		template<>
		class Stack<std::string> {
		public:
			void push(std::string const& elem);
			void pop();
			std::string const& top()const;
			inline bool empty()const { return data.empty(); }
		private:
			std::deque<std::string> data;
		};

		inline void Stack<std::string>::push(std::string const& elem)
		{
			data.push_back(elem);
		}
		inline void Stack<std::string>::pop() {
			assert(!data.empty());
			data.pop_back();
		}
		inline std::string const& Stack<std::string>::top()const {
			assert(!data.empty());
			return data.back();
		}

		//2.6 Partial Specialization
		template<typename T>
		class Stack<T*> {
		public:
			void push(T* elem);
			T* pop();
			T* top();
			bool empty()const { return data.empty(); }
		private:
			std::vector<T*> data;
		};

		template<typename T>
		inline void Stack<T*>::push(T* elem) {
			data.push_back(elem);
		}

		template<typename T>
		inline T* Stack<T*>::pop() {
			assert(!data.empty());
			T* p = data.back();
			data.pop_back();
			return p;
		}

		template<typename T>
		inline T* Stack<T*>::top() {
			assert(!data.empty());
			return data.back();
		}
	}

	namespace V2 {
		// Partial Specialization with Multiple Parameters
		template<typename T1, typename T2>
		class MyClass {

		};

		template<typename T>
		class MyClass<T, T> {

		};
		template<typename T1, typename T2>
		class MyClass<T1*, T2*> {

		};
	}

	namespace V3{
		// 2.7 Default Class Template Arguments
		template<typename T, typename Cont = std::vector<T>>
		class Stack {
		public:
			void push(T const& elem);
			void pop();
			T const& top();
			bool empty()const { return data.empty(); }
		private:
			Cont data;
		};

		template<typename T, typename Cont>
		void Stack<T, Cont>::push(T const& elem) {
			data.push_back(elem);
		}
		template<typename T, typename Cont>
		void Stack<T, Cont>::pop() {
			assert(!data.empty());
			data.pop_back();
		}
		template<typename T, typename Cont>
		T const& Stack<T, Cont>::top() {
			assert(!data.empty());
			return data.back();
		}

		// Alias Templates
		template<typename T>
		using DequeStack = Stack<T, std::deque<T>>;
	}
}

void class_template_example();