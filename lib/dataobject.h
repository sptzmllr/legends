#pragma once
//#include "projection.h"
//#include <cstddef>
#include <string>
#include <utility>

namespace lgnds{

class data_object
{
public:

private:
	
	std::size_t					m_max_samples;
	std::pair<double,double>	nodata_value;
	std::string 				m_file_name, m_name, m_description;
//	lgnds::projection			m_projection;
};

}
