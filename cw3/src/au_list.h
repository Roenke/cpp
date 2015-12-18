#pragma once

namespace containers
{
	template<typename T>
	struct au_list
	{
		typedef T value_type;
		typedef value_type& reference;
		typedef value_type const & const_reference;
		typedef value_type* pointer;
		typedef value_type const* const_pointer;
		typedef size_t size_type;

		struct node
		{
			node();
			reference get_value();
			const_reference get_value() const;
			void set_value(const_reference);
			node* get_prev();
			node* get_prev() const;

			node* get_next();
			node* get_next() const;

			friend au_list;
		private:
			value_type value_;
			node* next_;
			node* prev_;
		};

		au_list();
		au_list(au_list const& other);
		node* begin();
		node* begin() const;
		node* end();
		node* end() const;

		bool empty() const;
		size_type size() const;

		template<typename V>
		node* insert(node* position, V* first, V* last);
		node* insert(node* position, const_reference value);

		node* erase(node* position);
		node* erase(node* first, node* last);

		void clear();

		~au_list();

	private:
		node* head_;
		node* end_;
		size_type size_;
	};
};

template <typename T>
containers::au_list<T>::node::node()
	: value_(T())
	, next_(nullptr)
	, prev_(nullptr)
{
}

template <typename T>
typename containers::au_list<T>::reference containers::au_list<T>::node::get_value()
{
	return value_;
}

template <typename T>
typename containers::au_list<T>::const_reference containers::au_list<T>::node::get_value() const
{
	return value_;
}

template <typename T>
void containers::au_list<T>::node::set_value(const_reference other)
{
	value_ = other;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::node::get_prev()
{
	return prev_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::node::get_prev() const
{
	return prev_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::node::get_next()
{
	return next_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::node::get_next() const
{
	return next_;
}

template <typename T>
containers::au_list<T>::au_list()
	: head_(new node())
	, size_(0)
{
	end_ = head_;
}

template <typename T>
containers::au_list<T>::au_list(au_list const& other)
	: au_list()
{
	node* other_iter = other.begin();
	while(other_iter != other.end())
	{
		insert(end_, other_iter->value_);
		other_iter = other_iter->get_next();
	}
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::begin()
{
	return head_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::begin() const
{
	return head_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::end()
{
	return end_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::end() const
{
	return end_;
}

template <typename T>
bool containers::au_list<T>::empty() const
{
	return size_ == 0;
}

template <typename T>
typename containers::au_list<T>::size_type containers::au_list<T>::size() const
{
	return size_;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::insert(node* position, const_reference value)
{
	node* new_node = new node();
	new_node->value_ = value;
	new_node->prev_ = position->prev_;
	new_node->next_ = position;

	++size_;
	if (position->get_prev() != nullptr)
	{
		position->get_prev()->next_ = new_node;
	}
	position->prev_ = new_node;
	if (position == head_)
	{
		head_ = new_node;
	}

	return new_node;
}

template <typename T>
template <typename V>
typename containers::au_list<T>::node* containers::au_list<T>::insert(node* position, V* first, V* last)
{
	while(last >= first)
	{
		position = insert(position, T(*last));
		--last;
	}
	
	return position;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::erase(node* position)
{
	node* result = position->next_;
	if (position == head_)
	{
		head_ = head_->next_;
		head_->prev_ = position->prev_;
	}
	else
	{
		position->prev_->next_ = position->next_;
		position->next_->prev_ = position->prev_;
	}
	
	--size_;

	delete position;
	return result;
}

template <typename T>
typename containers::au_list<T>::node* containers::au_list<T>::erase(node* first, node* last)
{
	node* iter = first;

	while(iter != last)
	{
		iter = erase(iter);
	}

	return iter;
}

template <typename T>
void containers::au_list<T>::clear()
{
	erase(head_, end_);
}

template <typename T>
containers::au_list<T>::~au_list()
{
	clear();
	delete head_;
}
