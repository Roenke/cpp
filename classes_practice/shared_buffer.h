#pragma once

struct shared_buffer
{
    explicit shared_buffer(size_t size);
    shared_buffer(const shared_buffer& src);
    shared_buffer& operator=(shared_buffer src);
    ~shared_buffer();

    void new_data(const char*);

    char* get_data();
    const char* get_data() const;

    size_t get_size() const;

private:
    int* ptrs_count_;
    int* data_size_;
    char* data_;
};