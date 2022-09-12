#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
	Entity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print() {}
};

int main()
{
	std::weak_ptr<Entity> w0;
	std::weak_ptr<Entity> w1;
	{ //some scope
		std::shared_ptr<Entity> e0;

		{ //nested scope
			//std::unique_ptr<Entity> entity = new Entity(); //not allow because the constructor is explicit
			//std::unique_ptr<Entity> entity(new Entity());	//we can do it this way
			std::unique_ptr<Entity> entity = std::make_unique<Entity>(); //but this is preferred, Exception safe.

			//w1 = entity; //we can't copy a unique pointer into a weak pointer

			//std::shared_ptr<Entity> sharedEntity(new Entity()); //it compiles but it's wrong to do it this way because needs to allocate the control block to operate
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>(); //this is the way to go.
			e0 = sharedEntity; //we can copy
			w0 = sharedEntity; //to copy a shared pointer into a weak pointer doesn't increase the counting

			std::cout << "is w0 expired? " << w0.expired() << std::endl; //we can check whether the weak pointer is still pointing to some valid address.
			std::cout << "is w1 expired? " << w1.expired() << std::endl; //therefore it's expired always as it points to nowhere

			entity->Print();
		}

		std::cout << "is w0 now expired? " << w0.expired() << std::endl;
		std::cout << "is w1 now expired? " << w1.expired() << std::endl;

		std::cin.get();
	}

	std::cout << "is w0 finally expired? " << w0.expired() << std::endl;
	std::cout << "is w1 finally expired? " << w1.expired() << std::endl;

	return 0;
}

