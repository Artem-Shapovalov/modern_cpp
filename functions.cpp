#include <iostream>
#include <functional>
#include <array>
#include <ranges>

class Dummy
{
	public:
		void do_something()
		{
			std::cout << "Dummy doing something" << std::endl;
		}

		static void do_something_static()
		{
			std::cout << "Dummy doing something statically"
				<< std::endl;
		}
};

class DummyFunctor
{
	public:
		void operator()()
		{
			std::cout << "DummyFunctor doing something"
				<< std::endl;
		}
};

void do_something()
{
	std::cout << "Doing domething globally" << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "Modern C++ functions demo" << std::endl;

	{
		std::cout << "declaring a callback" << std::endl;
		// std::function behaves like a pointer to function, but
		// it also may store the 
		auto x{ std::function<void(void)>{ do_something } };
		auto y{ std::function<void(void)>() };
		
		std::cout << "checking if the object is available: "
			<< (y ? "y is set" : "y is not set") << std::endl;

		std::cout << "function callback: ";
		x = do_something;
		x();

		std::cout << "static member function callback: ";
		x = Dummy::do_something_static;
		x();

		std::cout << "member function callback: ";
		auto dummy{ Dummy() };
		// Here, we binding together class object with function in a
		// single object
		x = std::bind(&Dummy::do_something, dummy);
		x();

		std::cout << "functor callback: ";
		auto functor{ DummyFunctor() };
		x = functor;
		x();

		std::cout << "lambda function callback: ";
		x = []() -> void {
			std::cout << "Doing something from lambda"
				<< std::endl;
		};
		x();
	}

	{
		std::cout << std::endl << "Another ways to call functions"
			<< std::endl;
		auto func{
			[](int i, std::string s, double d) -> int
			{
				std::cout << "func:"
					<< "i: " << i << ", "
					<< "s: " << s << ", "
					<< "d: " << d << std::endl;

				return 300;
			}
		};

		auto args{ std::make_tuple(0, "foo", 3.14) };
		std::cout << "calling function with apply: "
			<< std::apply(func, args) << std::endl;
		// std::apply unpacks tuple with args and apply it to any
		// function object

		std::cout << "calling function with invoke: "
			<< std::invoke(func, 10, "bar", 9.81) << std::endl;
		// std::invoke calls any functional object with the rest
		// of arguments
	}

	return 0;
}
