#pragma once

#include <exception>

#include "utility.h"

namespace expt{

class Exception : public std::runtime_error
{
public:
	template<typename... Args>
	Exception(Args&&... args) : std::runtime_error(make_string(std::forward<Args>(args)...))
	{
	}

};

template<typename E, typename... Args>
void Throw(Args&&... args)
{
	throw E(std::forward<Args>(args)...);
}

template<typename E, typename V, typename... Args>
void Assert(const V& v, Args&&... args)
{
	if (!v) {
		Throw<E>(std::forward<Args>(args)...);
	}
}

}