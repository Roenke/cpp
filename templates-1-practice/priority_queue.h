#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class priority_queue
{
public:
    priority_queue();
    priority_queue(priority_queue const&);
    priority_queue& operator=(priority_queue const&);

    void push(T const&, int);
    void pop();
    T& front();
    T const& front() const;
    size_t size();
private:
    std::vector<std::pair<int, T>> container_;
};

template <typename T>
priority_queue<T>::priority_queue()
    : container_(0)
{}

template <typename T>
priority_queue<T>::priority_queue(priority_queue const& other)
    :container_(other.container_)
{}

template <typename T>
priority_queue<T>& priority_queue<T>::operator=(priority_queue const& other)
{
    container_ = other.container_;
    return *this;
}

template <typename T>
void priority_queue<T>::push(T const& value, int priority)
{
    container_.push_back(std::pair<int, T>(priority, value));
    std::push_heap(container_.begin(), container_.end(), 
        [](std::pair<int, T> const& lhs, std::pair<int, T> const& rhs) { return lhs.first < rhs.first; });
}

template <typename T>
void priority_queue<T>::pop()
{
    std::pop_heap(container_.begin(), container_.end(), 
        [](std::pair<int, T> const& lhs, std::pair<int, T> const& rhs) { return lhs.first < rhs.first; });
    container_.pop_back();
}

template <typename T>
T& priority_queue<T>::front()
{
    return container_[0].second;
}

template <typename T>
T const& priority_queue<T>::front() const
{
    return container_[0].second;
}

template <typename T>
size_t priority_queue<T>::size()
{
    return container_.size();
}
