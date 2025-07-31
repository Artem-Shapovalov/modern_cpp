#include <iostream>

// Debugging helper. debug_type function intensionally produces an error that
// contains the real type of the variable.
template<typename T> struct TypePrinter;
template<typename T> void debug_type() { TypePrinter<T> x; }

template<typename T> // Declaring T as name of the type
T identity(T value)
{
	std::cout << "T is: " << typeid(T).name() << std::endl;
	return value;
}

template<typename... Args> // Declaring Args as variadic list of type names
void print_all(Args... args)
{
	(std::cout << ... << args) << std::endl;
}

template<typename... Args>
void print_enumerated(Args&&... args) // args is a list
{
	int index = 0;
	// ((EXPR), ...) expands to set of (EXPR<arg1>, EXPR<arg2>, EXPR<arg3>
	// and so on. Each of them would be evaluated
	((std::cout << index++ << ": " << args << std::endl), ...);
	std::cout << "Total: " << sizeof...(args) << std::endl;
}

template<typename T, size_t V>
class CustomArray
{
	public:
		T data[V];
};

int main(int argc, char** argv)
{
	std::cout << "Modern C++ templates demo" << std::endl;

	{
	std::cout << "Basic type deduction debugging technique:" << std::endl;
	int i;
	auto j{ 3.14 };
	std::cout << "i has type: " << typeid(i).name() << std::endl;
	std::cout << "j has type: " << typeid(decltype(j)).name() << std::endl;
	}

	{
	std::cout << "Types deduction" << std::endl;
	auto i{ identity(42) }; // -> int
	auto d{ identity(3.14) }; // -> double
	auto s{ identity("Hi") }; // -> const char*
	auto np{ identity(nullptr) }; // -> void*
	auto pi{ identity(&i) };  // -> int*

	const auto& ri{ i }; identity(ri); // debug_type(ri);
	std::cout << "ri has type: "
		<< typeid(decltype((ri))).name()
		<< std::endl;
	
	const auto&& uri{ std::move(i) };
	std::cout << "uri has type: "
		<< typeid(decltype(uri)).name()
		<< std::endl;

	}

	{
	std::cout << "Variadic parameters template example" << std::endl;
	print_all("This line ", "is made from ", 4, " parameters!");
	print_enumerated("foo", "bar", 3.14, 42);

	std::cout << "Parenthesis example: ";
	(std::cout << "e1", std::cout << 3.14, std::cout << 42) << std::endl;
	}

	return 0;
}
