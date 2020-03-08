#include <initializer_list>

namespace ntl
{
	template<typename T, typename V>
	class Array
	{
	public:
		Array() = default;
		~Array();

	private:
		T array[V];
		size_t size = V;
	};
	Array::~Array()
	{
	}
}