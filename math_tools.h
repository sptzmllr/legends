#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

namespace lgnds {

namespace math {

template<typename T>
constexpr T pi = 2 * acos(0.0);

template<typename T>
constexpr T euler = std::exp(1.0);


// "cumulative" 
enum class counting_type { cumulative, non_cumulative };


template<typename T, lgnds::math::counting_type Count_Type=lgnds::math::counting_type::cumulative>
class statistics
{
	// TODO Enhance the static assert with numbers and strings
	static_assert(std::is_arithmetic<T>::value, "");

public:
	statistics() {};
	~statistics() {};

	void push_back(T Value)
	{
		data_.push_back(Value);
	}

	void emplace_back(T Value)
	{
		data_.emplace_back(Value);
	}

	void clear()
	{
		data_.clear();
	}

	T min()
	{
		return *std::min_element( data_.begin(), data_.end() );
	}

private:
	std::vector<T>				data_;

	lgnds::math::counting_type 	Count_Type_;
};
// ended namespace lgnds::math
};


// ended namespace lgnds
};
