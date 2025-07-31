#include <iostream>
#include <memory>
#include <string>

class DummyClass
{
	public:
		DummyClass(std::string name) : name(name)
		{
			std::cout << ">> creating " << name << std::endl;
		}

		virtual ~DummyClass()
		{
			std::cout << ">> destroying " << name << std::endl;
		}

		std::string name;
};

int main(int argc, char** argv)
{
	std::cout << "Modern C++ memory demo" << std::endl;

	// The main idea of modern cpp usage is automatical control the memory
	// by holding objects. You no need to directly call new or free, the
	// objects called smart pointers make it for you themselves.
	// Smartpointers mocks the regular pointers from old C++ and C, you
	// can dereference it, you can compare it and so on, but it's more
	// complicated object that controls the memory.

	{
		std::cout << "Unique pointers" << std::endl;

		// The next variable holds std::unique_ptr with DummyClass
		// object. The memory is automatically allocated inside the
		// make_unique function and the constructor was called. After
		// out the scope, DummyClass would be automatically destroyed
		// and the memory would be freed
		auto x{ std::make_unique<DummyClass>("unique_ptr") };
		std::cout << "x is " << typeid(decltype(x)).name() << std::endl;
		std::cout << x->name << std::endl;

		// This pointer can not be copied or passed to the function
		// this way it useful to prevent sharing the created objects.
	}

	{
		std::cout << "Shared pointers" << std::endl;

		// The next variable holds std::shared_ptr with DummyClass
		// object. Unlike std::unique_ptr it may be assigned to other
		// variables and passed to the functions. As std::unique_ptr,
		// the DummyClass object would be automatically destroyed
		// and the memory freed, but it happens when all of the
		// holding variables outs of scope.
		auto x{ std::make_shared<DummyClass>("shared_ptr") };
		std::cout << "x is " << typeid(decltype(x)).name() << std::endl;
		std::cout << x->name << std::endl;

		auto y = x;
		std::cout << "y is " << typeid(decltype(y)).name() << std::endl;
		std::cout << y->name << std::endl;
	}

	{
		std::cout << "Weak pointers" << std::endl;

		// The next variable holds std::weak_ptr with DummyClass
		// object. Weak pointers are observers of the shared pointers:
		// they do not affect on the data inside, you have no access
		// to the holding data, but you can see the health of the
		// pointer.
		std::weak_ptr<DummyClass> y;
		std::cout << "y is " << typeid(decltype(y)).name() << std::endl;
		std::cout << (y.expired() ? "invalid" : "valid") << std::endl;

		{
			auto x{ std::make_shared<DummyClass>("shared_ptr") };
			std::cout << "x is " << typeid(decltype(x)).name()
				<< std::endl;
			std::cout << x->name << std::endl;

			y = x;
			std::cout << (y.expired() ? "invalid" : "valid")
				<< std::endl;
		}

		std::cout << (y.expired() ? "invalid" : "valid") << std::endl;
	}
	
	return 0;
}
