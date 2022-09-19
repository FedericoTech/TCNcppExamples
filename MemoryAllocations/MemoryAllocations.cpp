#include <iostream>
#include <memory>

struct AllocationMetrics
{
	size_t TotalAllocated = 0;
	size_t TotalFreed = 0;
	size_t CurrentUsage() { return TotalAllocated - TotalFreed;  }
};

static AllocationMetrics s_AllocationMetrics;

void * operator new (size_t size)
{
	std::cout << "Allocating " << size << " bytes" << std::endl;

	s_AllocationMetrics.TotalAllocated += size;

	return malloc(size);
}

static void PrintMemoryUsage()
{
	std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes" << std::endl;
}

//This doesn't work in Mingw-w64
void operator delete(void * memory) noexcept
{
	std::cout << "deleting, no size" << std::endl;
	free(memory);
}

void operator delete(void *memory, size_t size)
{
	std::cout << "deleting " << size << " bytes" << std::endl;

	s_AllocationMetrics.TotalFreed += size;

	free(memory);
}


struct Object
{
	int x, y, z;

};

int main()
{
	std::cout << __cplusplus << std::endl << std::endl;

	PrintMemoryUsage();

	std::string string = "Cherno"; //it doesn't call new in Mingw-w64

	PrintMemoryUsage();

	Object * obj = new Object;

	PrintMemoryUsage();

	{
		std::unique_ptr<Object> obj2 = std::make_unique<Object>();
		PrintMemoryUsage();
	}

	delete obj;

	PrintMemoryUsage();
}
