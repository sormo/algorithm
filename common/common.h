#pragma once

#include <string>
#include <vector>
#include <algorithm>

#define INVALID_SIZE_T ((size_t)-1)

// convert string of ascii digits to string of numbers [0,9]
std::vector<char> ConvertToDigits(const std::string & n);
std::string ConvertFromDigits(const std::vector<char> & n);

// operations on vector of numbers
std::vector<char> AddNumbers(const std::vector<char> & a, const std::vector<char> & b);
std::vector<char> SubNumbers(const std::vector<char> & a, const std::vector<char> & b);

// read numbers from file to vector
std::vector<unsigned int> ReadNumbersToVector(const std::string & file);

namespace detail
{
	template<typename F, typename Tuple, size_t ...S >
	decltype(auto) apply_tuple_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
	{
		return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
	}
}
template<typename F, typename Tuple> 
decltype(auto) apply_from_tuple(F&& fn, Tuple&& t) 
{ 
	std::size_t constexpr tSize = std::tuple_size<typename std::remove_reference<Tuple>::type>::value; 	
	return detail::apply_tuple_impl(std::forward<F>(fn), std::forward<Tuple>(t), std::make_index_sequence<tSize>());
}