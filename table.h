#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "dataobject.h"
namespace lgnds{

template<typename table>
class table_field_iterator
{
public:
	using IterType = typename table::FieldBasePointer;
	using PointerType = typename std::vector<IterType>::iterator;
	using ReferenceType = typename std::vector<IterType>::reference;

public:
	table_field_iterator(PointerType ptr)
		: m_ptr(ptr) {}

	table_field_iterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	table_field_iterator operator++(int)
	{
		table_field_iterator iter = *this;
		++(*this);
		return iter;
	}

	table_field_iterator& operator--()
	{
		m_ptr--;
		return *this;
	}

	table_field_iterator operator--(int)
	{
		table_field_iterator iter = *this;
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

	bool operator==(const table_field_iterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const table_field_iterator& other) const
	{
		return m_ptr != other.m_ptr;
	}

private:
	PointerType m_ptr;

};

template<typename table_field>
class table_column_iterator
{
public:
	using ValueType = typename table_field::ValueType;
	using PointerType = typename std::vector<ValueType>::iterator;
	using ReferenceType = typename std::vector<ValueType>::reference;

public:
	table_column_iterator(PointerType ptr)
		: m_ptr(ptr) {}

	table_column_iterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	table_column_iterator operator++(int)
	{
		table_column_iterator iter = *this;
		++(*this);
		return iter;
	}

	table_column_iterator& operator--()
	{
		m_ptr--;
		return *this;
	}

	table_column_iterator operator--(int)
	{
		table_column_iterator iter = *this;
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

	bool operator==(const table_column_iterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const table_column_iterator& other) const
	{
		return m_ptr != other.m_ptr;
	}

private:
	PointerType m_ptr;
};

class table_field_base 
{
public:
	// virtual destructor for polymorphism 
	virtual ~table_field_base() = default;

	void set_name(std::string name)
	{
		m_name = name;
	}

	std::string get_name()
	{
		return m_name;	
	}

protected:

	std::string 	m_name;
};


template< typename T>
class table_field : public table_field_base
{
public:
	using ValueType = T;
	using iterator = table_column_iterator<table_field<ValueType>>;
public:

	table_field() {};
	table_field( std::string name)
   	{
		m_name = name;
		//m_values = std::make_unique<std::vector<T>>();
	};
	~table_field( void ) {};

	void push_back( T value )
	{
		//m_values->push_back( value );
		m_values.push_back( value );
	}

	T& at( const size_t index )
	{
		return m_values.at(index);
	}

	iterator begin()
	{
		return iterator(std::begin(m_values));
	}

	iterator end()
	{
		return iterator(std::end(m_values));
	}

protected:

private:
	std::vector<T> 	m_values;
	//std::unique_ptr<std::vector<T>> m_values;
};


class table : public data_object
{
public:
	using FieldBasePointer = typename std::shared_ptr<table_field_base>;
	using iterator = table_field_iterator<table>;
public:
	table( void )	{};
	table( std::string name )
	{
		m_table_name = name;	
	}

	template <typename T>
	table( std::string table_name, std::string field_name, size_t size )
	{
		m_table_name = table_name;
		//this->push_field<T>(
	}

#ifdef LEGENDS_SAGA_COMPABILITY
	table( CSG_Table* Table )
	{

	}
#endif

	~table( void )	{};

	template <typename T>
	void push_field (std::string S)
	{
		m_fields.push_back( std::make_shared <table_field <T>>(S) );
	}
	
	template <typename T>
	std::shared_ptr <table_field <T>>	field( int index )
	{
		std::shared_ptr <table_field_base>  base_ptr = m_fields.at(index);
		//std::shared_ptr <table_field <T>> field;
		return std::dynamic_pointer_cast<table_field<T>>(base_ptr);
		//return field;
	}

	template <typename T>
	std::shared_ptr <table_field <T>> field( std::string name )
	{
		/*
		for( lgnds::table::iterator it = this->begin();
				it != this->end(); ++it )
		{
			if( it->get_name() == name )
			{
				std::shared_ptr <table_field_base> base_ptr = field;
				return std::dynamic_pointer_cast<table_field<T>>(base_ptr);
			}
		}
		*/
		for( auto& field : m_fields )
		{
			if( field->get_name() == name )
			{
				std::shared_ptr <table_field_base> base_ptr = field;
				return std::dynamic_pointer_cast<table_field<T>>(base_ptr);
			}
		}

		return nullptr;
	}

	
	iterator begin()
	{
		return iterator(m_fields.begin());
	}

	
	iterator end()
	{
		return iterator(m_fields.end());
	}


private:
	std::vector<std::shared_ptr<table_field_base>> m_fields;
	std::string m_table_name = "none";
};



}

/*
int main()
{
	std::shared_ptr<lgnds::table> test = std::make_shared<lgnds::table>();

	test->push_field <int>( "hallo");
	test->push_field <double>( "hallo");

	//std::shared_ptr<lgnds::table_field<int>> field = test->field(0);
	std::shared_ptr<lgnds::table_field<int>> field_a = test->field<int>(0);

	field_a->push_back( 1 );

	return 1;
}
*/























/*
template<typename grid>
class grid_iterator
{
public:
	using valuetype = typename grid::valuetype;
	using pointertype = valuetype*;
	using referencetype = valuetype&;
public:
	grid_iterator(pointertype ptr)
		: m_ptr(ptr) {}

	grid_iterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	grid_iterator& operator++(int)
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

	grid_iterator& operator--(int)
	{
		grid_iterator iterator = *this;
		--(*this);
		return iterator;
	}

	referencetype operator[](int index)
	{
		return *(m_ptr + index);
	}

	pointertype operator->()
	{
		return m_ptr;
	}

	referencetype operator*()
	{
		return *m_ptr;
	}

	bool operator==(const grid_iterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const grid_iterator& other) const
	{
		return m_ptr != other.m_ptr;
	}
private:
	pointertype m_ptr;
};
*/

/*
template<typename T>
class grid{
public:
//	using valuetype = T;	
//	using iterator = grid_iterator<grid<T>>;
public:
	grid( void ) {};
	grid( size_t rows, size_t column )
	{
		row = rows;
		col= column;
		data = std::vector<std::vector<T>>(column);
		for( auto& t: data )
			t = std::vector<T>(rows);
	}
	~grid( void ) {};

	T& at( size_t x, size_t y)
	{
		return data.at(y).at(x);
	}
*/
	/*
	iterator begin()
	{
		return iterator(this->at(0,0));
	}

	iterator end()
	{
		return iterator(data.end());
	}
	*/

/*

protected:
	size_t row = 0;
	size_t col = 0;

	std::vector< std::vector<T> > data;
};

*/
