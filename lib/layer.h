#include "table.h"
#include <saga_api/saga_api.h>

namespace lgnds{




template<typename T = float>
	requires std::integral<T> || std::floating_point<T>
struct point
{
	point( T x, T y);
	T x;
	T y;
};


class layer : public table
{
public:

public:

	layer( void )
	{
		m_table = std::make_shared<lgnds::table>();
	};

	layer( CSG_Shapes* pShapes )
	{
		//m_table = std::make_shared<lgnds::table>( pShapes->asTable() );
	};
	
	~layer() {};	
private:
	std::shared_ptr<lgnds::table> m_table = nullptr;
};
}


