#include "../length.h"
#include <iostream>

int main()
{
	lgnds::length<double, lgnds::length_unit::meter>	Abstand(12.2);
	lgnds::length<double, lgnds::length_unit::meter>	Abstand1;
	Abstand = 42.;

	std::string_view 	Einhaitname = Abstand.print_unit();
	std::string 		Einhaitname2 = Abstand.print_unit();

	auto AbstandInMeilen = Abstand.convert(lgnds::length_unit::kilometer);

	//int test = 42;
	std::cout << "Printing Enum meter : " << AbstandInMeilen << Einhaitname2 << Einhaitname<< std::endl;
	return 0;
}
