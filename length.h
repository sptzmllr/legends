#pragma once
#include <iostream>

namespace lgnds
{
/*
class FloatingPointEnum {
    float f;
    FloatingPointEnum(float arg) : f(arg) {}
public:
    static const FloatingPointEnum Value1;
    static const FloatingPointEnum Value2;
    operator float() const { return f; }
};
const FloatingPointEnum FloatingPointEnum::Value1(0.1234f);
const FloatingPointEnum FloatingPointEnum::Value2(0.6789f);

class length_unit { 
	float f;
	length_unit(float arg) : f(arg) {}
public:
	static const length_unit meter;
	operator float() const { return f; }
};
const length_unit length_unit::meter(1.0f);
	
*/
enum length_unit
{
	millimeter, centimeter, decimeter, meter, kilometer, int_inch, int_foot, int_yard, int_fathom, int_link, int_chain, int_mile, int_nautical_mile,
   	us_inch, us_foot, us_yard, us_chain, us_mile, indian_foot, indian_yard, indian_chain
};

//template<typename T, enum lgnds::length_unit Unit>
//class length;
//template<typename T, enum lgnds::length_unit Unit>
//std::ostream& operator<<( std::ostream& output, const lgnds::length<T,Unit>& );


template<typename T, enum lgnds::length_unit Unit>
class length
{
	static_assert(std::is_floating_point<T>::value, "Type must be floating point");
public:
	length() {};

	length( T Arg )
	{
		Value_	= Arg;
		Unit_	= Unit;
	}

	/*
	length( T Arg )
		: Value_{ Arg } {};

	T& operator=(T&& Other)
	{
		return Value_ = Other;
	}
	*/

	std::string print_unit()
	{
		//return "Meter";
		switch( Unit_ )
		{
			case millimeter:		return "Millimeter"					; break;
			case centimeter: 		return "Centimeter"					; break;
			case decimeter: 		return "Decimeter"					; break;
			case meter: 			return "Meter"						; break;
			case kilometer: 		return "Kilometer"					; break;
			case int_inch: 			return "International Inch"			; break;
			case int_foot: 			return "International Foot"			; break;
			case int_yard: 			return "International Yard"			; break;
			case int_fathom: 		return "International Fathom"		; break;
			case int_link: 			return "International Link"			; break;
			case int_chain: 		return "International Chain"		; break;
			case int_mile: 			return "International Mile"			; break;
			case int_nautical_mile:	return "International Nautical Mile"; break;
			case us_inch: 			return "International Inch"			; break;
			case us_foot:			return "US Foot"					; break;
			case us_yard:			return "US Yard"					; break;
			case us_chain:			return "US Chain"					; break;
			case us_mile:			return "US Mile"					; break;
			case indian_foot:		return "Indian Foot"				; break;
			case indian_yard:		return "Indian Yard"				; break;
			case indian_chain:		return "Indian Chain"				; break;	
			default:				return ""							; break;
								
		}
	}

	//template< enum lgnds::length_unit ForeinUnit>
	T convert( const enum lgnds::length_unit External )
	{	
		T temp = this->convert_to_meter();

		switch( External )
		{
			case kilometer: return temp * 0.000'1;	break;
		}
	}

	T convert_to_meter()
	{
		switch( Unit_ )
		{
			case millimeter:		return Value_ / 1000;				break;
			case centimeter: 		return Value_ /	100; 				break;
			case decimeter: 		return Value_ * 0.1; 				break;
			case meter: 			return Value_ * 1.0;				break;
			case kilometer: 		return Value_ * 1'000;				break;
			case int_inch: 			return Value_ * 1'000;				break;
			case int_foot: 			return Value_ * 1.0; 				break;
			case int_yard: 			return Value_ / 1.0936; 			break;
			case int_fathom: 		return Value_ * 1.8299; 			break;
			case int_link: 			return Value_ / 4.9709695378987;	break;
			case int_chain: 		return Value_ / 0.049710; 			break;
			case int_mile: 			return Value_ * 1609.344;			break;
			case int_nautical_mile:	return Value_ * 1852; 				break;
			case us_inch: 			return Value_ / 39.37;				break;
			case us_foot:			return Value_ / 3.281; 				break;
			case us_yard:			return Value_ / 1.094;				break;
			case us_chain:			return Value_ / 0.049709695378987;	break;
			case us_mile:			return Value_ * 1609.34; 			break;
			case indian_foot:		return 42.;							break;
			case indian_yard:		return 42.;							break;
			case indian_chain:		return 42.;							break;	
			default:				return 0.0;							break;
		}
	
	}

	//template<typename U, enum lgnds::length_unit Unit2>
	friend std::ostream& operator<<( std::ostream& output, const length<T,Unit>& Arg)
	{
		return output << Arg.Value_ ; //<< " " << Arg.print_unit();
	}


private:

	T 					Value_;
	lgnds::length_unit 	Unit_;

};



// end namespace lgnds
};
