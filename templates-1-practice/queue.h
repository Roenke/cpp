#pragma once
#include <iostream>

namespace data_structures
{

    template<typename T>
    struct list_elem
    {
        T elem;
        list_elem* next;
    };

    template<typename T>
    class queue
    {
    public:
        queue();

        explicit queue(queue<T> const&);

        queue& operator=(queue const&);
        void push(T);
        T pop();
        T& front();
        T const& front() const;

        size_t size() const;

        ~queue();
    private:
        size_t size_;
        list_elem<T>* head_;
    };

    template <typename T>
    queue<T>::queue()
        : size_(0)
    {
        head_ = nullptr;
    }

    template <typename T>
    queue<T>::queue(queue<T> const& other)
        : size_(0)
    {
        auto ptr = other.head_;
        while(ptr != nullptr)
        {
            push(static_cast<T>(ptr->elem));
            ptr = ptr->next;
        }
    }

    template <typename T>
    queue<T>& queue<T>::operator=(queue const&)
    {
        return{};
    }

    template <typename T>
    void queue<T>::push(T elem)
    {
        ++size_;
        if (head_ == nullptr)
        {
            head_ = new list_elem<T>();
            head_->elem = elem;
            head_->next = nullptr;
            return;
        }
        list_elem<T>* ptr = head_;
        while (ptr->next != nullptr) ptr = ptr->next;
        ptr->next = new list_elem<T>();
        ptr->next->next = nullptr;
        ptr->next->elem = elem;
    }

    template <typename T>
    T queue<T>::pop()
    {
        if (head_ == nullptr)
        {
            throw std::exception("queue is emplty. pop failed.");
        }

        auto old_head = head_;
        head_ = head_->next;
        --size_;

        return old_head->elem;
    }

    template <typename T>
    T& queue<T>::front()
    {
        if (head_ == nullptr)
        {
            throw std::exception("queue is empty. front failed.");
        }

        return head_->elem;
    }

    template <typename T>
    T const& queue<T>::front() const
    {
        if (size_ == 0)
        {
            throw std::exception("queue is empty");
        }

        return head_->elem;
    }

    template <typename T>
    size_t queue<T>::size() const
    {
        return size_;
    }

    template <typename T>
    queue<T>::~queue()
    {

    }
}