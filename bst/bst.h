#pragma once

#include <memory>
#include <iterator>
#include <functional>

#include "utility.h"
#include "exception.h"

namespace expt{namespace bst{

class InvalidNode : public Exception
{
public:
	template<typename... Args>
	InvalidNode(Args&&... args) : Exception(std::forward<Args>(args)...) {}

};

class OutOfRange : public Exception
{
public:
	template<typename... Args>
	OutOfRange(Args&&... args) : Exception(std::forward<Args>(args)...) {}

};

class NodeLink : public std::enable_shared_from_this<NodeLink>
{
public:
	virtual ~NodeLink() = default;

	std::shared_ptr<NodeLink> parent() const noexcept;
	void parent(const std::weak_ptr<NodeLink>& parent) noexcept;

	const std::shared_ptr<NodeLink>& left() const noexcept;
	void left(const std::shared_ptr<NodeLink>& left) noexcept;

	const std::shared_ptr<NodeLink>& right() const noexcept;
	void right(const std::shared_ptr<NodeLink>& right) noexcept;

	std::weak_ptr<NodeLink> increment() const;

	std::weak_ptr<NodeLink> decrement() const;

private:
	std::weak_ptr<NodeLink> _parent;
	std::shared_ptr<NodeLink> _left;
	std::shared_ptr<NodeLink> _right;

};

template<typename T>
class Node : public NodeLink
{
public:
	Node(const T& value) : _value(value) {}

	Node(T&& value) : _value(std::move(value)) {}

	template<typename... Args>
	Node(Args&&... args) : _value(std::forward<Args>(args)...) {}

	const T& value() const noexcept {return _value;}

private:
	const T _value;
	
};

template<typename T>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
{
public:
	using base = std::iterator<std::bidirectional_iterator_tag, const T>;
	using iterator_category = typename base::iterator_category;
	using value_type = typename base::value_type;
	using difference_type = typename base::difference_type;
	using pointer = typename base::pointer;
	using reference = typename base::reference;

	Iterator() noexcept {}

	explicit Iterator(std::weak_ptr<NodeLink> node_link) noexcept : _node_link(node_link) {}

	reference operator*() {return cast()->value();}

	pointer operator->() {return &cast()->value();}

	Iterator& operator++()
	{
		_node_link = lock()->increment();
		return *this;
	}

	Iterator operator++(int)
	{
		auto tmp = *this;
		_node_link = lock()->increment();
		return tmp;
	}

	Iterator& operator--()
	{
		_node_link = lock()->decrement();
		return *this;
	}

	Iterator operator--(int)
	{
		auto tmp = *this;
		_node_link = lock()->decrement();
		return tmp;
	}

	bool operator==(const Iterator& right) const {return lock() == right.lock();}

	bool operator!=(const Iterator& right) const {return lock() != right.lock();}

private:
	std::shared_ptr<NodeLink> lock()
	{
		auto ptr = _node_link.lock();
		Assert<InvalidNode>(ptr, "iterator is invalid");
		return ptr;
	}

	std::shared_ptr<Node<T>> cast()
	{
		auto ptr = std::dynamic_pointer_cast<Node<T>>(lock());
		Assert<InvalidNode>(ptr, "invalid node");
		return ptr;
	}

private:
	std::weak_ptr<NodeLink> _node_link;

};

template<typename T, template<typename> typename Compare = std::less>
class BST
{
public:
	using iterator = Iterator<T>;

	BST() : _begin(std::make_shared<NodeLink>()), _end(_begin), _size(0) {}

	iterator insert(const T& value)
	{
		return __insert(std::make_shared<Node<T>>(value));
	}

	iterator insert(T&& value)
	{
		return __insert(std::make_shared<Node<T>>(std::move(value)));
	}

	template<typename... Args>
	iterator emplace(Args&&... args)
	{
		return __insert(std::make_shared<Node<T>>(std::forward<Args>(args)...));
	}

protected:
	virtual iterator insert(const std::shared_ptr<Node<T>>& node)
	{
		if (!_root) {
			set_root(node);
			return iterator(node);
		}

		auto tmp = _root;
		while (true) {
			if (_compare(node->value(), std::static_pointer_cast<Node<T>>(tmp)->value())) {
				if (tmp->left()) {
					tmp = tmp->left();
				} else {
					set_left_child(tmp, node);
					break;
				}
			} else {
				if (tmp->right()) {
					tmp = tmp->right();
				} else {
					set_right_child(tmp, node);
					break;
				}
			}
		}
		return iterator(node);
	}

	void set_root(const std::shared_ptr<NodeLink>& root)
	{
		_root = root;
		_begin = _root;
		_root->right(_end);
		_end->parent(_root);
	}

	void set_left_child(const std::shared_ptr<NodeLink>& parent, const std::shared_ptr<NodeLink>& son)
	{
		parent->left(son);
		son->parent(parent);
		if (parent == _begin) {
			_begin = son;
		}
	}

	void set_right_child(const std::shared_ptr<NodeLink>& parent, const std::shared_ptr<NodeLink>& son)
	{
		parent->right(son);
		son->parent(parent);
		if (parent == _end->parent()) {
			_end->parent(son);
		}
	}

private:
	iterator __insert(const std::shared_ptr<Node<T>>& node)
	{
		if (_end->parent()) {
			_end->parent()->right(nullptr);
		}
		auto it = insert(node);
		if (_end->parent()) {
			_end->parent()->right(_end);
		}
		++_size;
		return it;
	}

protected:
	Compare<T> _compare;
	std::shared_ptr<NodeLink> _root;
	std::shared_ptr<NodeLink> _begin;
	std::shared_ptr<NodeLink> _end;

private:
	std::size_t _size;

};

}}
