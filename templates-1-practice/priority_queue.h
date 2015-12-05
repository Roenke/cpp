#pragma once
#include <vector>

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
    std::vector<T> container_;
};
