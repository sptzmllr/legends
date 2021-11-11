#include "../math_tools.h"
#include <iostream>

int main()
{
	auto 	pitd = lgnds::math::pi<double>;
	auto 	pitf = lgnds::math::pi<float>;

	auto	eulerf = lgnds::math::euler<float>;
	auto	eulerd = lgnds::math::euler<float>;


	std::cout << "Pi is : " << pitd << std::endl;
	std::cout << "Pi is : " << pitf << std::endl;
	std::cout << "Euler is : " << eulerf << std::endl;
	std::cout << "Euler is : " << eulerf << std::endl;

	lgnds::math::statistics<double>		Number_Sink;
	lgnds::math::statistics<int>		Number_Sink_i;

	Number_Sink.push_back(12.0);
}

