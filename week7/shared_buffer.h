class shared_buffer{
public:
	explicit shared_buffer(size_t);
	shared_buffer(const shared_buffer&);
	shared_buffer& operator=(shared_buffer&);
	~shared_buffer();
	char* get_data();
	const char* get_data() const;
	size_t get_size() const;
private:
	
};

