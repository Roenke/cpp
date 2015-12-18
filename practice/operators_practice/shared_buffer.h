#pragma once

namespace lazy
{
    struct shared_buffer
    {
        explicit shared_buffer(size_t size);
        shared_buffer(const shared_buffer& src);
        shared_buffer& operator=(shared_buffer src);
        ~shared_buffer();

        char* get_data();
        const char* get_data() const;

        size_t get_size() const;

    private:
        int* ptrs_count_;
        int* data_size_;
        char* data_;
    };
}; /* lazy */
