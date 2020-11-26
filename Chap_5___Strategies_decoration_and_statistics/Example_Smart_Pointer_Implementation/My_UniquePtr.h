#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

template <class T>
class My_UniquePtr {

	T* m_ptr;

public:

	// defuault ctor
	My_UniquePtr(T* ptr = nullptr) : m_ptr{ptr}
	{
	}

	// destructor
	~My_UniquePtr()
	{
		delete m_ptr;
	}

	// copy ctor deleted
	My_UniquePtr(const My_UniquePtr& original) = delete;

	// move ctor
	My_UniquePtr(My_UniquePtr&& original)
	{
		std::cout << "move operator= called\n";

		m_ptr = original.m_ptr;   // shallow copy of T-ptrs  
		original.m_ptr = nullptr; // moved ptr left to default state
	}

	// overloaded copy-assignment operator= deleted
	My_UniquePtr& operator=(const My_UniquePtr& original) = delete;

	// overloaded move-assignment operator=
	My_UniquePtr& operator=(My_UniquePtr&& original)
	{
		std::cout << "move operator= called\n";

		if (!(this == &original))
		{
			delete m_ptr;             // release any resource possibly handled already

			m_ptr = original.m_ptr;   // shallow copy of T-ptrs  
			original.m_ptr = nullptr; // moved ptr left to default state
		}

		return *this;
	}

	// overloaded operator->
	T* operator*() const { return m_ptr; }
	
	// overloaded operator*
	T& operator->() const { return *m_ptr; }

	// check whether My_UniquePtr is actually managing a resource or not
	bool isAssigned() const { return !(m_ptr == nullptr); }

};

#endif
