#include <iostream>

template<typename T>
struct list_elem
{
    T* elem;
    list_elem* next;
};

template<typename T>
class queue
{
public:
    queue();
    queue(queue&);

    // ToDo: сделать конструктор с приведением типов.
    template<typename U>
    explicit queue(queue<T>&);

    queue& operator=(queue const&);
    void push(queue&);
    T pop();
    
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
queue<T>::queue(queue& other)
{
    size_ = other.size();
    list_elem<T>* ptr = other.head_;
}

template <typename T>
template <typename U>
queue<T>::queue(queue<T>& other)
{
    size_ = other.size();
}

template <typename T>
queue<T>& queue<T>::operator=(queue const&)
{
    return {};
}

template <typename T>
void queue<T>::push(queue&)
{
}

template <typename T>
T queue<T>::pop()
{
    if(head_ == nullptr)
    {
        throw std::exception("dkjfghdkfgh");
    }

    --size_;
    return *hea ->elem;
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

void main()
{
    queue<double> double_queue;

}
