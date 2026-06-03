#pragma once

#include <vector>
#include <cmath>
#include <iostream>

namespace polymorphic_power_of_templates {
	struct Coord {
		int x, y;
		size_t abs()const {
			return (size_t)sqrt(x * x + y * y);
		}
		Coord operator - (Coord const& rhs) {
			return { x - rhs.x, y - rhs.y };
		}
	};
	// 18.1 Dynamic Polymorphism
	namespace dynamic_polymorphism {

		class GeoObj {
		public:
			virtual void draw()const = 0;
			virtual Coord center_of_gravity()const = 0;
			virtual ~GeoObj() = default;
		};

		class Circle : public GeoObj {
		public:
			void draw()const override {
				std::cout << "Circle->Draw()\n";
			}
			Coord center_of_gravity()const override {
				return {};
			}
		};

		class Line : public GeoObj {
		public:
			void draw()const override {
				std::cout << "Line->Draw()\n";
			}
			Coord center_of_gravity()const override
			{
				return {};
			}
		};

		class Rectangle :public GeoObj {
		public:
			void draw()const override {
				std::cout << "Line->Draw()\n";
			}
			Coord center_of_gravity()const override {
				return {};
			}
		};

		// draw any GeoObj
		inline void my_draw(GeoObj const& obj) {
			obj.draw();
		}

		// compute distance of center of gravity between two GeoObjs
		inline size_t distance(GeoObj const& lhs, GeoObj const& rhs) {
			Coord const& c = lhs.center_of_gravity() - rhs.center_of_gravity();
			return c.abs();
		}

		// Draw heterogeneous collection of GeoObjs
		inline void drawElems(std::vector<GeoObj*> const& elems) {
			for (auto const& e : elems) {
				e->draw();
			}
		}

	}
	// 18.2 Static Polymorphism
	namespace static_polymorohism {

		class Circle {
		public:
			void draw()const {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
			Coord center_of_gravity()const {
				return {};
			}
		};

		class Line {
		public:
			void draw()const {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
			Coord center_of_gravity()const {
				return {};
			}
		};
		class Rectangle {
		public:
			void draw()const {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
			Coord center_of_gravity()const {
				return {};
			}
		};

		template<typename GeoObj>
		void my_draw(GeoObj const& obj) {
			obj.draw();
		}

		template<typename GeoObj1, typename GeoObj2>
		size_t distance(GeoObj1 const& go1, GeoObj2 const& go2) {
			polymorphic_power_of_templates::Coord c = go1.center_of_gravity() - go2.center_of_gravity();
			return c.abs();
		}
		template<typename GeoObj>
		void drawElems(std::vector<GeoObj> const& elems) {
			for (auto const& e : elems) {
				e.draw();
			}
		}
	}
	// 18.3 Dynamic versus Static Polymorhism
	// 18.4 Using Concepts
	namespace using_concepts {

		class Circle {
		public:
			void draw()const {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
			Coord center_of_gravity()const {
				return {};
			}
		};

		class Line {
		public:
			void draw()const {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
			Coord center_of_gravity()const {
				return {};
			}
		};
		class Rectangle {
		public:
			void draw()const {
				std::cout << __PRETTY_FUNCTION__ << "\n";
			}
			Coord center_of_gravity()const {
				return {};
			}
		};

		template<typename T>
		concept GeoObj = requires(T x) {
			{ x.draw() }-> std::same_as<void>;
			{ x.center_of_gravity() }-> std::same_as<Coord>;
		};

		template<typename T>
		requires GeoObj<T>
		void my_draw(T const& obj) {
			obj.draw();
		}

		template<typename T1, typename T2>
		requires GeoObj<T1>&& GeoObj<T2>
		size_t distance(T1 const& go1, T2 const& go2) {
			polymorphic_power_of_templates::Coord c = go1.center_of_gravity() - go2.center_of_gravity();
			return c.abs();
		}
		template<typename T>
		requires GeoObj<T>
		void drawElems(std::vector<T> const& elems) {
			for (auto const& e : elems) {
				e.draw();
			}
		}
	}
}

void polymorphic_power_of_templates_example();