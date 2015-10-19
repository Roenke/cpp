#include "shared_buffer.h"

shared_buffer::shared_buffer(size_t size){

}

shared_buffer::shared_buffer(const shared_buffer&);
shared_buffer& operator=(shared_buffer&);
~shared_buffer();
char* get_data();
const char* get_data() const;
size_t get_size() const;