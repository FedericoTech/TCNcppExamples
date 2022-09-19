#include <iostream>
#include <cstdint>
#include <cstring>


class String
{
public:
	String() = default; //this and the one bellow are the same
	//String(){}
	//String(): m_Data(nullptr), m_Size(0){} //if the pointer wasn't allocated we need to initialise it here

	String(const char* string) //this would work with constant Others
	{
		std::cout << "Created!" << std::endl;
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}

	//copy constructor
	String(const String& other)	//this would work with constant Others
	{
		std::cout << "Copied!" << std::endl;
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}

	//move constructor
	String(String&& other) noexcept  //Other can't be constant as we are going to change it.
	{
		std::cout << "Moved!" << std::endl;
		m_Size = other.m_Size;
		m_Data = other.m_Data; //we move the pointer of other to this object

		//we steal the data of other
		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	//copy assignment operator
	String &operator=(const String &other) //this would work with constant Others
	{
		std::cout << "Copy assigned!" << std::endl;

		if(this == &other){
			return *this;
		}

		m_Size = other.m_Size;

		delete[] m_Data; //important, deallocate whatever was. the member had to be initialised too
		m_Data = new char[m_Size];

		memcpy(m_Data, other.m_Data, m_Size);

		return *this;
	}

	//move assignment operator
	String& operator=(String&& other) noexcept //Other can't be constant as we are going to change it.
	{
		std::cout << "Move assigned!" << std::endl;

		if(this == &other){
			return *this;
		}

		m_Size = other.m_Size;

		delete[] m_Data; //important, deallocate whatever was. the member had to be initialised too
		m_Data = other.m_Data; //we move the pointer of other to this object

		//we steal the data of other
		other.m_Size = 0;
		other.m_Data = nullptr;

		return *this;
	}

	~String()
	{
		std::cout << "Destroyed!" << std::endl;
		delete m_Data;
	}

	void Print()
	{
		for(uint32_t i = 0; i < m_Size; i++){
			std::cout << m_Data[i];
		}

		std::cout << std::endl;
	}

private:
	char *m_Data = nullptr;
	uint32_t m_Size = 0;
};

class Entity
{
public:
	Entity(const String &name)
		: m_Name(name)
	{

	}

	Entity(String&& name)
		: m_Name((String &&)name)
		//: m_Name(std::move(name)) //alternatively we can do this, #include <memory>
	{

	}

	void PrintName()
	{
		m_Name.Print();
	}
private:
	String m_Name;
};

int main()
{
	Entity entity = String("Cherno");
	//Entity entity("Cherno"); //implicit constructor, it's like doing the bellow line
	//Entity entity(String("Cherno")); //this for clarity
	//both of the above lines need a copy constructor to function.
	entity.PrintName();


	String string = "Hello";
	//String dest = (String&&)string;
	//String dest((String&&) string);
	//String dest(std::move(string));

	String dest = std::move(string); //move constructed

	string.Print();
	dest.Print();

	//copy assigned
	String dest2;
	dest2 = dest;

	dest2.Print();

	//move assigned
	String dest3;
	//dest3 = (String &&)dest2;
	dest3 = std::move(dest2);

	dest2.Print();
	dest3.Print();

	std::cin.get();
}
