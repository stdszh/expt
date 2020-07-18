#include "bst.h"

namespace expt{namespace bst{

std::shared_ptr<NodeLink> NodeLink::parent() const noexcept
{
	return _parent.lock();
}

void NodeLink::parent(const std::weak_ptr<NodeLink>& parent) noexcept
{
	_parent = parent;
}

const std::shared_ptr<NodeLink>& NodeLink::left() const noexcept
{
	return _left;
}

void NodeLink::left(const std::shared_ptr<NodeLink>& left) noexcept
{
	_left = left;
}

const std::shared_ptr<NodeLink>& NodeLink::right() const noexcept
{
	return _right;
}

void NodeLink::right(const std::shared_ptr<NodeLink>& right) noexcept
{
	_right = right;
}

std::weak_ptr<NodeLink> NodeLink::increment() const
{
	if (_right) {
		auto x = _right;
		while (x->_left) {
			x = x->_left;
		}
		return x;
	} else {
		auto x = shared_from_this();
		auto y = x->parent();
		while (y && y->_right == x) {
			x = y;
			y = x->parent();
		}
		Assert<OutOfRange>(y, "iterator is out of range");
		return y;
	}
}

std::weak_ptr<NodeLink> NodeLink::decrement() const
{
	if (_left) {
		auto x = _left;
		while (x->_right) {
			x = x->_right;
		}
		return x;
	} else {
		auto x = shared_from_this();
		auto y = x->parent();
		while (y && y->_left == x) {
			x = y;
			y = x->parent();
		}
		Assert<OutOfRange>(y, "iterator is out of range");
		return y;
	}
}

}}