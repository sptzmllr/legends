#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "dataobject.h"
#include <saga_api/saga_api.h>

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
	
	void reserve( std::size_t new_cap )
	{
		m_values.reserve( new_cap );

	}

	void resize( std::size_t new_size )
	{
		m_values.resize( new_size );
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

	table( CSG_Table* pTable )
	{
		long long int table_size = pTable->Get_Count();
		
		if( table_size >= 0 )
			this->size = (std::size_t) table_size;

		for( int field_index = 0; field_index < pTable->Get_Field_Count(); field_index++ )
		{
			std::wstring ws =  pTable->Get_Field_Name(field_index); 
			std::string FieldName( ws.begin(), ws.end() );

			std::shared_ptr <table_field_base> base_ptr = nullptr;
			switch( pTable->Get_Field_Type(field_index) )
			{
				/*
				case SG_DATATYPE_Bit:
				{
					this->push_field<bool>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<bool> field = (*std::dynamic_pointer_cast<table_field<bool>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (bool) pTable->Get_Record(rec)->asShort(field_index);
					}
				}
				break;
				*/

				case SG_DATATYPE_Byte:
				{
					this->push_field<unsigned char>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<unsigned char> field = (*std::dynamic_pointer_cast<table_field<unsigned char>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (unsigned char) pTable->Get_Record(rec)->asChar(field_index);
					}
				}
				break;

				case SG_DATATYPE_Char:
				{
					this->push_field<char>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<char> field = (*std::dynamic_pointer_cast<table_field<char>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (char) pTable->Get_Record(rec)->asChar(field_index);
					}
				}
				break;

				case SG_DATATYPE_Word:
				{
					this->push_field<uint16_t>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<uint16_t>field = (*std::dynamic_pointer_cast<table_field<uint16_t>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (uint16_t) pTable->Get_Record(rec)->asChar(field_index);
					}
				}
				break;

				case SG_DATATYPE_Short:
				{
					this->push_field<int16_t>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<int16_t> field = (*std::dynamic_pointer_cast<table_field<int16_t>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (int16_t) pTable->Get_Record(rec)->asShort(field_index);
					}
				}
				break;

				case SG_DATATYPE_DWord:
				{
					this->push_field<uint32_t>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<uint32_t> field = (*std::dynamic_pointer_cast<table_field<uint32_t>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (uint32_t) pTable->Get_Record(rec)->asShort(field_index);
					}
				}
				break;

				case SG_DATATYPE_Int:
				{
					this->push_field<int32_t>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<int32_t> field = (*std::dynamic_pointer_cast<table_field<int32_t>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (int32_t) pTable->Get_Record(rec)->asInt(field_index);
					}
				}
				break;

				case SG_DATATYPE_ULong:
				{
					this->push_field<uint64_t>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<uint64_t> field = (*std::dynamic_pointer_cast<table_field<uint64_t>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (uint64_t) pTable->Get_Record(rec)->asLong(field_index);
					}
				}
				break;

				case SG_DATATYPE_Long:
				{
					this->push_field<int64_t>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<int64_t> field = (*std::dynamic_pointer_cast<table_field<int64_t>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (int64_t) pTable->Get_Record(rec)->asLong(field_index);
					}
				}
				break;

				case SG_DATATYPE_Float:
				{
					this->push_field<float>( FieldName );
					base_ptr = this->m_fields.back();
					lgnds::table_field<float> field = (*std::dynamic_pointer_cast<table_field<float>>(base_ptr));

					for( std::size_t rec=0; rec<size; rec++ )
					{
						field.at(rec) = (float) pTable->Get_Record(rec)->asFloat(field_index);
					}
				}
				break;

				case SG_DATATYPE_Double:
				{
					this->push_field<double>( FieldName );

					base_ptr = this->m_fields.back();
					lgnds::table_field<double> field = (*std::dynamic_pointer_cast<table_field<double>>(base_ptr));

					for( std::size_t rec = 0; rec < pTable->Get_Count(); rec++ )
					{
						field.at( rec ) = pTable->Get_Record(rec)->asDouble(field_index);

					}
				}
				break;

				case SG_DATATYPE_String:
				{
					this->push_field<std::string>( FieldName );

					base_ptr = this->m_fields.back();
					lgnds::table_field<std::string> field = (*std::dynamic_pointer_cast<table_field<std::string>>(base_ptr));

					for( std::size_t rec = 0; rec < pTable->Get_Count(); rec++ )
					{
						std::wstring ws = pTable->Get_Record(rec)->asString(field_index);
						std::string s( ws.begin(), ws.end() );
						field.at( rec ) = s;

					}
				}
				break;


			}
		}

	}

	~table( void )	{};

	template <typename T>
	void push_field (std::string S)
	{
		std::shared_ptr<table_field<T>> new_field = std::make_shared <table_field <T>>(S);
		new_field->resize( this->size );
		this->m_fields.push_back( new_field );
		
	}

	/*
	template <typename T>
	std::shared_ptr <table_field<T>> 	push_field( std::string S )
	{
		
	}
	*/
	
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
	
	std::size_t 	size = 0;
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
