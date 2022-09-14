#include <iostream>

class Entity
{
private:
	int m_X, m_Y;
	int *m_pX = &m_X;
	mutable int mutable_var; //mutable makes a var able to be change in const methods
public:
	int GetX() const //we tell the compiler it doesn't modify any member in it.
	{
		//m_X = 2; //therefore this won't compile
		mutable_var = 1; //however we can modify this var because it's declared mutable
		return m_X;
	}

	//it means, we are returning a constant pointer to a constant value and that the method itself won't modify anything inside it.
	const int * const GetPX() const
	{
		//m_pX = nullptr; //therefore this won't compile
		mutable_var = 1; //however we can modify this var value because it's declared mutable

		*m_pX = 2; //this will compile because the const restriction seems to apply to the address of the pointer only not to the value pointed to.
		return m_pX;
	}

	void SetX(int x)
	{
		m_X = x;
	}
};

void PrintEntity(const Entity& e) //we are passing the reference to the object and making it const
{
	std::cout << e.GetX() << std::endl; //GetX has to be 'const safe' to work here
	std::cout << *e.GetPX() << std::endl; //GetPX has to be 'const safe' to work here
}

int main()
{
	const int MAX_AGE = 90; //we declare this constant

	std::cout << "we have this const int MAX_AGE: " << MAX_AGE << std::endl;

//Plain pointer exercise
	std::cout << "plain pointer exercise: 'int *'" << std::endl;

	int * a = new int; //we allocate an 'int' in the heap

	*a = 2;	//we set some value

	std::cout << "*a: " << *a << std::endl;

	delete a; //we deallocate the 'int' ponted to


	//a = &MAX_AGE; //it won't compile because invalid conversion from 'const int*' to 'int*'

	//a = (int*) &MAX_AGE; //by casting the reference as 'int*' we cast the constness away.
	a = const_cast<int*>(&MAX_AGE); //this is another way to put the line above

	*a = 30; //we try to change te value of MAX_AGE through the pointer

	std::cout << "MAX_AGE: " << MAX_AGE << std::endl; 	//we still get 90. this is due to that the compiler optimisation
														//replaced the occurrences of MAX_AGE for its value
														//to get rid of that optimisation MAX_AGE should also be volatile
	std::cout << "*a: " << *a << std::endl;
	std::cout << "a == &MAX_AGE? " << (a == &MAX_AGE) << std::endl;

	*a = MAX_AGE; //we reestablish the value. MAX_AGE here was replaced by compiler optimisation so it's like saying a* = 90

// pointer to const value
	std::cout << std::endl << "pointer to a const value: 'const int *'" << std::endl;

	const int * b = new int; //we declare a constant pointer and allocate the 'int' in the heap

	//*b = 2; //we try to set a value in the position pointet to but we can't because it's constant.

	delete b; //so we deallocate the 'int' from the heap

	b = &MAX_AGE; //we can however point to the constant by reference without casting! because the two of them are const
	std::cout << "*b: " << *b << std::endl;

// constant pointer to value
	std::cout << std::endl << "const pointer to a value: 'int * const'" << std::endl;

	int * const c = new int; //we allocate an 'int' in the heap by a constant pointer

	*c = 2; //we can change the content
	//c = &MAX_AGE; //but we cannot change the address the pointer points to

	std::cout << "*c: " << *c << std::endl;

	delete c; //we deallocate c from the heap.

// const pointer to const value
	std::cout << std::endl << "const pointer to a const value: 'const int * const'" << std::endl;

	const int * const d = new int {3}; //we allocate a const 'int' in the heap by a constant pointer

	//*d = 2; //we cannot change the content
	//d = &MAX_AGE; //and we cannot change the address the pointer points to

	std::cout << "*d: " << *d << std::endl;

	delete d; //we deallocate d from the heap.

// plain class exercise
	std::cout << std::endl << "Plain class exercise" << std::endl;

	Entity e;
	e.SetX(-3);
	PrintEntity(e);

	return 0;
}



