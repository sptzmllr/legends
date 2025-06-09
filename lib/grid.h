#pragma once
#include "dataobject.h" 
#include <saga_api/saga_api.h>
//#include "grid_system.h"
#include <vector>
#include <memory>
//#include <iostream>
//#include <initializer_list>

namespace lgnds{

template <typename grid>
class grid_iterator
{
public:
	using ValueType = typename grid::ValueType;
	using PointerType = typename std::vector<ValueType>::iterator;
	using ReferenceType = typename std::vector<ValueType>::reference;
public:
	grid_iterator( PointerType ptr )
		: m_ptr(ptr) {}

	grid_iterator& operator++()
	{
		m_ptr++;
		return *this;
	}
	
	grid_iterator operator++(int)
	{
		grid_iterator iterator = *this;
		++(*this);
		return iterator;
	}

	grid_iterator& operator--()
	{
		m_ptr--;
		return *this;
	}
	
	grid_iterator operator--(int)
	{
		grid_iterator iterator = *this;
		--(*this);
		return iterator;
	}
	
	PointerType operator->()
	{
		return m_ptr;
	}

	ReferenceType operator*()
	{
		return *m_ptr;
	}

	bool operator==(const grid_iterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const grid_iterator& other) const
	{
		return !(*this == other);
	}

private:
	PointerType m_ptr;
};

template<typename grid_row>
class grid_row_iterator
{
public:
	using ValueType = typename grid_row::ValueType;
	using PointerType = typename std::vector<ValueType>::iterator;
	using ReferenceType = typename std::vector<ValueType>::reference;

public:
	grid_row_iterator(PointerType ptr)
		: m_ptr{ptr} {}

	grid_row_iterator& operator++()
	{
		m_ptr++;
		return *this;	
	}

	grid_row_iterator operator++(int)
	{
		grid_row_iterator iter = *this;
		++(*this);
		return iter;	
	}

	grid_row_iterator& operator--()
	{
		m_ptr--;
		return *this;	
	}

	grid_row_iterator operator--(int)
	{
		grid_row_iterator iter = *this;
		--(*this);
		return iter;	
	}

	ReferenceType operator[](int index)
	{
		return *(m_ptr + index);	
	}

	PointerType operator->()
	{
		return m_ptr;
	}

	ReferenceType operator*()
	{
		return *m_ptr;	
	}

	bool operator==(const grid_row_iterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const grid_row_iterator& other) const
	{
		return m_ptr != other.m_ptr;
	}

private:
	PointerType m_ptr;

};

template<typename T>
class grid_row{
public:
	using ValueType = T;
	using iterator = grid_row_iterator<grid_row<ValueType>>;
public:
	grid_row(  void ) {};
	grid_row(  std::vector <T> row ) 
	{	
		m_row = row;
	}


	grid_row( std::vector<T>::iterator first, std::vector<T>::iterator last )
		: m_row( std::vector<T>( first, last ) ) {};

	~grid_row( void ) {};

	T& operator[] (size_t col_pos)
	{
		return m_row[col_pos];
	}

	T& at(std::size_t col_pos)
	{
		return m_row.at( col_pos );
	}

	std::size_t	size()
	{
		return m_row.size();
	}

	iterator begin()
	{
		return iterator( std::begin(m_row));	
	}

	iterator end()
	{
		return iterator( std::end(m_row));	
	}

private:
	std::vector <T> m_row;
};

template<typename T>
class grid : public data_object {
public:
	using ValueType = T;	
	using iterator = grid_iterator<grid<ValueType>>;
	//sing PointerType = typename std::vector<ValueType>::iterator;
	//using ReferenceType = typename std::vector<ValueType>::reference;
public:
	grid( void ) {};
	grid( std::size_t rows, std::size_t columns )
	{
		m_row = rows;
		m_col= columns;
		m_data = std::vector<T>( rows * columns );
	}
	grid( std::size_t rows, std::size_t columns , const T& default_val)
	{
		m_row = rows;
		m_col= columns;
		m_data = std::vector<T>( rows * columns , default_val);
		default_value_ = default_val;
	}

	grid( CSG_Grid* grid_ptr )
	{
		m_row = (std::size_t) grid_ptr->Get_NX();
		m_col = (std::size_t) grid_ptr->Get_NY();
		m_data = std::vector<T>( grid_ptr->Get_NCells());

		for( int y = 0; y<grid_ptr->Get_NY(); y++ )
		{
			for( int x = 0; x<grid_ptr->Get_NX(); x++ )
			{
				switch ( grid_ptr->Get_Type() ) {
					case SG_DATATYPE_Int: 	m_data[(y*m_row)+x] = (T) grid_ptr->asInt(x,y);		break;
					default: 				m_data[(y*m_row)+x] = (T) grid_ptr->asDouble(x,y);	break;
				
			
				}
			}
		}
	}

	~grid( void ) {};

	T& at( std::size_t x, std::size_t y)
	{
		return m_data.at((y*m_row)+x);
	}

	T& at( std::size_t it)
	{
		return m_data.at(it);
	}


	std::size_t rows()
	{
		return m_row;	
	}

	std::size_t columns()
	{
		return m_col;	
	}

	std::size_t size()
	{
		return m_row * m_col;
	}

	lgnds::grid_row<T>	row( std::size_t row_index )
	{
		return lgnds::grid_row<T>( std::vector<T>(	m_data.begin() + row_index * m_col, 
												m_data.end()+ row_index * m_col ));
	}

	/*
	std::shared_ptr<grid_row<T>> row( std::size_t row_index )
	{
		return std::make_shared<grid_row<T>>( m_data.at(row_index) );
	}
	*/

	T default_value()
	{
		return default_value_;
	}

	void resize( std::size_t new_row_size, std::size_t new_column_size )
	{
		for( auto &it : m_data )
		{
			it.resize( new_row_size );
			if( new_row_size > m_row )
			{
				
			}
		}
	}

	/*
	void print()
	{
		for( auto &it : m_data )
		{
			std::cout << it << ' ';
		}
		std::cout << std::endl;
	}
	*/

	
	iterator begin()
	{
		return m_data.begin();
	}

	iterator end()
	{
		return m_data.end();
	}

	std::vector<T> operator[] (size_t row)
	{
		return m_data[row];
	}


	//template<typename T>
	//lgnds::grid_row 	row(size_t row)
	//{
	//	return grid_row<T>( m_data[row] );
	//}
	


private:
	//lgnds::grid_system system;

	std::size_t m_row = 0;
	std::size_t m_col = 0;

	T default_value_ = 0;

	std::vector<T> m_data;
};
}	//end namespace lgnds

/*
int main( void )
{	
	//template<typename T>
	//using grid_ptr = std::shared_ptr <lgnds::grid<T>> ;

	//grid_ptr<int> grid_1 = std::make_shared <lgnds::grid <int>>( 5, 5);
	
	std::shared_ptr <lgnds::grid <int>> grid = std::make_shared <lgnds::grid <int>>( 5, 5);

	grid->at(0,0) = 1;
//	lgnds::grid_row<int> row(grid[0]) ;	
//	std::vector<int> vec = grid[0];
	int test_2 = (*grid)[0][0];

	lgnds::grid<int> grid_1(6,6);
	int test = grid_1[0][0];

	for( lgnds::grid<int>::iterator it= grid->begin(); it != grid->end(); it++ )
	{
	//	int a = it;
	}

	//for( auto& elm : grid )
	return 1;
}
*/
