#include "Chapter18-ThePolymorphicPowerOfTemplates.h"

#include <iostream>

namespace polymorphic_power_of_templates::dynamic_polymorphism {
	
}

void polymorphic_power_of_templates_example() 
{
	using namespace polymorphic_power_of_templates;

	{
		// 18.1 Dynamic Polymorphism
		using namespace dynamic_polymorphism;
		Line l;
		Circle c, c1, c2;

		my_draw(c1);
		my_draw(l);
	
		std::vector<GeoObj*> coll;
		coll.emplace_back(&l);
		coll.emplace_back(&c);
		drawElems(coll);			

	}

	{
		using namespace static_polymorohism;
		Line l;
		Circle c;
		Rectangle rc;

		my_draw(c);
		my_draw(l);
		my_draw(rc);

		//std::vector<GeoObj*> coll;// no heterogeneous collection possible
		std::vector<Line> coll;
		coll.emplace_back(l);
		drawElems(coll);
	}
	{
		using namespace using_concepts;
		Line l;
		Circle c;
		Rectangle rc;

		my_draw(c);
		my_draw(l);
		my_draw(rc);

		//std::vector<GeoObj*> coll;// no heterogeneous collection possible
		std::vector<Line> coll;
		coll.emplace_back(l);
		drawElems(coll);
	}
}
