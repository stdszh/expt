#pragma once

#include <sstream>

namespace expt{

template<typename Stream, typename First, typename... Args>
void append_streasm(Stream& stream, First&& first, Args&&... args)
{
	stream << first;
	if constexpr (sizeof...(args) > 0) {
		append_streasm(stream, std::forward<Args>(args)...);
	}
}

template<typename... Args>
std::string make_string(Args&&... args)
{
	std::ostringstream stream;
	append_streasm(stream, std::forward<Args>(args)...);
	return stream.str();
}

}