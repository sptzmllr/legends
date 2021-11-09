#include <cmath>
#include <vector>

namespace lgnds {

namespace math {

template<typename T>
constexpr T pi = 2 * acos(0.0);

template<typename T>
constexpr T euler = std::exp(1.0);

template<typename T>
class statistics
{
	static_assert(std::is_floating_point<T>::value, "Type must be floating point");
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

private:
	std::vector<T>	data_;
};
// ended namespace lgnds::math
};


// ended namespace lgnds
};
