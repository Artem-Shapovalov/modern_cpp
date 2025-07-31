#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <tuple>
#include <optional>
#include <any>
#include <variant>

int main(int argc, char** argv)
{
	std::cout << "Modern C++ containers demo" << std::endl;

	{
		std::cout << "std::pair" << std::endl;

		// std::pair is a simplest container, that represents just
		// a two values combined in a one structure by template.
		// Often other containers utilize std::pair for their needs in
		// their interfaces.

		auto x{ std::make_pair( "foo", 1 ) };
		auto y{ x };
		auto z{ std::pair{ (int)1, std::string("foo") } };

		std::cout << "accessing items: "
			<< x.first << " "  << x.second << std::endl;

		std::cout << "unpacking pair: ";
		auto [ x_first, x_second ] { x };
		std::cout << x_first << " " << x_second << std::endl;

		std::cout << "comparing pairs:" << std::endl;
		// You may compare the same type pairs. If pairs have different
		// type, like x and z, you'll got a compilation error.
		std::cout << (
			(x <=> y) == 0 ? "x == y" : 
			(x <=> y) >  0 ? "x >  y" :
			(x <=> y) <  0 ? "x <  y" : ""
			) << std::endl;

		y.second = 2;
		std::cout << (
			(x <=> y) == 0 ? "x == y" : 
			(x <=> y) >  0 ? "x >  y" :
			(x <=> y) <  0 ? "x <  y" : ""
			) << std::endl;

		y.second = 0;
		std::cout << (
			(x <=> y) == 0 ? "x == y" : 
			(x <=> y) >  0 ? "x >  y" :
			(x <=> y) <  0 ? "x <  y" : ""
			) << std::endl;

	}

	{
		std::cout << std::endl << "std::tuple" << std::endl;

		// Tuple is a structure like a pair, but it holds more than
		// 2 items inside

		auto x{ std::make_tuple( "foo", 1, 1.0 ) };

		std::cout << "accessing to item by id: "
			<< std::get<0>(x) << " "
			<< std::get<1>(x) << " "
			<< std::get<2>(x) << std::endl;

		std::cout << "accessing to item by type: "
			<< std::get<int>(x) << " "
			<< std::get<const char*>(x) << " "
			<< std::get<double>(x) << std::endl;

		std::cout << "unpacking tuples:" << std::endl;
		auto [ name, id, val ] = x;
		std::cout << name << id << val << std::endl;

		std::get<const char*>(x) = "fff";
		auto _name = "";
		auto _id = 0;
		auto _val = 0.0;
		std::tie(_name, _id, _val) = x;

		std::cout << _name << _id << _val << std::endl;
	}

	{
		std::cout << std::endl << "std::array" << std::endl;

		// std::array holds the fixed size data arrays. Here's the
		// ways how to declare and initialize it
		auto x{ std::to_array<std::string>({ "foo", "bar", "baz" }) };
		auto y{ x };
		auto z{ std::array{
				std::string("x"),
				std::string("y"),
				std::string("z")
			} };

		std::cout << "running through with for loop by value: ";
		for (auto s : x)
		{
			// Changing s do not affect to the values stored in x
			std::cout << s << " ";
		}
		std::cout << std::endl;

		std::cout << "getting item by id: ";
		std::cout << x[1] << std::endl;

		std::cout << "comparing arrays" << std::endl;

		std::cout << "three-way comparsion of equal arrays: "
			<< ((x <=> y) == 0 ? "x == y" : "x != y")
			<< std::endl;

		std::cout << "three-way comparsion of not equal arrays: "
			<< (
			(x <=> z) == 0 ? "x == z" :
			(x <=> z) < 0 ? "x < z" :
			(x <=> z) > 0 ? "x > z" : ""
			) << std::endl;
	}

	{
		std::cout << std::endl << "std::vector" << std::endl;

		// std::vector behaves like array, but may change its size.
		
		auto x{ std::vector<std::string>{ "foo", "bar" } };
		auto y{ x };
		auto z{ std::vector{
				std::string("y"),
				std::string("z")
			} };

		std::cout << "adding new value to the end:" << std::endl;
		x.push_back("baz");

		std::cout << "adding new value to specific place:" << std::endl;
		y.emplace(y.end(), std::string("baz"));
		z.insert(z.begin(), "x");

		std::cout << "remove the last element:" << std::endl;
		z.pop_back();

		std::cout << "clear vector:" << std::endl;
		z.clear();
		z.push_back("z");

		std::cout << "erasing value from specific place:" << std::endl;
		auto z_iter{ z.begin() };
		z_iter++;
		z.erase(z_iter);

		std::cout << "getting item by id: ";
		std::cout << x[1] << std::endl;

		std::cout << "getting the first item: ";
		std::cout << x.front() << std::endl;

		std::cout << "getting the last item: ";
		std::cout << x.back() << std::endl;

		std::cout << "getting acces to the underlying array: ";
		std::cout << x.data()[1] << std::endl;

		std::cout << "getting the current size: ";
		std::cout << x.size() << std::endl;

		std::cout << "comparing vectors" << std::endl;

		std::cout << "three-way comparsion of equal vectors: "
			<< (( x <=> y) == 0 ? "x == y" : "x != y")
			<< std::endl;

		std::cout << "three-way comparsion of not equal arrays: "
			<< (
			(x <=> z) == 0 ? "x == z" :
			(x <=> z) < 0 ? "x < z" :
			(x <=> z) > 0 ? "x > z" : ""
			) << std::endl;
	}

	{
		std::cout << std::endl << "std::list" << std::endl;

		// std::list also stores the data like vector, but you can't
		// access items by their index. Under the hood it's a linked
		// list implementation.

		auto x{ std::list<std::string>{ "foo", "bar" } };
		auto y{ x };
		auto z{ std::list{
				std::string("y"),
				std::string("z")
			} };

		std::cout << "adding new value to the end: " << std::endl;
		x.push_back("baz");

		std::cout << "adding new value to specific place:" << std::endl;
		y.emplace(y.end(), std::string("baz"));
		z.insert(z.begin(), "x");

		std::cout << "insert the first element:" << std::endl;
		z.push_front("--");

		std::cout << "remove the first element:" << std::endl;
		z.pop_front();

		std::cout << "insert the last element:" << std::endl;
		z.push_back("--");

		std::cout << "remove the last element:" << std::endl;
		z.pop_back();
	}

	{
		std::cout << std::endl << "std::set" << std::endl;

		// std::set is a collection of unique things. It's useful when
		// you need to keep data unique.
		
		auto x{ std::set<std::string>{ "foo", "bar", "baz" } };
		auto y{ x };
		auto z{ std::set{
				std::string("x"),
				std::string("y"),
				std::string("z")
			} };

		std::cout << "adding existing value:" << std::endl;
		// In this case nothing happened because the value is
		// already there
		x.insert("foo");

		std::cout << "adding inexisted value" << std::endl;
		// Here 'fff' would be added into the set and automatically
		// sorted
		x.insert("fff");

		std::cout << "removing existing value:" << std::endl;
		// Here the 'fff' would be removed from the set
		x.erase("fff");

		std::cout << "removing inexisted value:" << std::endl;
		// The 'fff' no longer inside the set, this why nothing
		// happens
		x.erase("fff");

		std::cout << "getting the size of the set: "
			<< x.size() << std::endl;

		std::cout << "searching in the set:" << std::endl;
		// returns number of occurences of the specific item,
		// for sets it's always 1 or 0
		std::cout << x.count("foo") << std::endl;

		// checks if the set contains specific value
		std::cout << x.contains("foo") << std::endl;

		// searches the specific value and returns const iterator
		std::cout << *(x.find("foo")) << std::endl;

		std::cout << "Get intersection of the common items"
			<< std::endl;
		// Warning: this may damage the x too! Be careful using it!
		auto k{ z };
		k.insert("foo");
		k.merge(x); // as k have similar 'foo'
	}

	{
		std::cout << std::endl << "std::map" << std::endl;

		// std::map is almost the same as the set, but it stores
		// key-value pairs. Imagine this storage of labeled boxes
		// with data.

		auto x{ std::map<std::string, int>{
			{ "foo", 1 }, { "bar", 2 }, { "baz", 3 } } };
		auto y{ x };
		auto z{ std::map<std::string, int>() };

		std::cout << "accessing items: " << x["foo"] << std::endl;
		std::cout << "adding items: " << std::endl;
		z["bax"] = 10;

		std::cout << "modifying item value:" << std::endl;
		x["foo"] = 0;

		std::cout << "getting inexistent items: " << x["xxx"]
			<< std::endl;
		// Attempt to get the inexisted item makes an empty item.
		std::cout << (
			x.contains("xxx") ? "x has 'xxx'" : "x has no 'xxx'"
			) << std::endl;

		std::cout << "removing items:" << std::endl;
		z.erase("bax");

		std::cout << "checks if the map already have an item: "
			<< x.contains("baz") << std::endl;

		std::cout << "Comparing maps:" << std::endl;
		y["foo"] = x["foo"];
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;
		x["foo"] = 1;
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;
		x["foo"] = 0;
		y["foo"] = 1;
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;
	}

	{
		std::cout << std::endl << "std::queue" << std::endl;

		// std::queue is a first-in, first-out container
		std::queue<int> x;
		auto y{ x };

		std::cout << "adding values:" << std::endl;
		x.push(0);
		x.push(1);
		x.push(2);

		std::cout << "extracting and reading values: " << std::endl;
		while (!x.empty())
		{
			std::cout << "front: " << x.front()
				<< " back: " << x.back()
				<< std::endl;

			x.pop();
		}
		std::cout << std::endl;

		std::cout << "comparing:" << std::endl;
		x.push(0);
		y.push(1);
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		x.pop();
		y.pop();
		
		x.push(1);
		y.push(1);
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		x.pop();
		y.pop();
		
		x.push(1);
		y.push(0);
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		x.pop();
		y.pop();

		// This container can not be iterated at all
	}

	{
		std::cout << std::endl << "std::stack" << std::endl;

		// std::stack is a last-in first-out container, like a
		// queue, but you popping values from the same point you
		// push.
		std::stack<int> x;
		auto y{ x };

		std::cout << "adding values:" << std::endl;
		x.push(0);
		x.push(1);
		x.push(2);

		std::cout << "extracting and reading values: " << std::endl;
		while (!x.empty())
		{
			// unlike the queue it has no font and back
			std::cout << x.top();

			x.pop();
		}
		std::cout << std::endl;

		std::cout << "comparing:" << std::endl;
		x.push(0);
		y.push(1);
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		x.pop();
		y.pop();
		
		x.push(1);
		y.push(1);
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		x.pop();
		y.pop();
		
		x.push(1);
		y.push(0);
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		x.pop();
		y.pop();

		// This container can not be iterated at all
	}

	{
		std::cout << std::endl << "std::deque" << std::endl;

		// std::deque is a super-container, that allows:
		// - get access by index
		// - push and pop both from front and back
		// - insert item in any place
		// - iterate
		// - clear
		
		auto x{ std::deque{ 1, 2, 3 } };
		auto y{ x };
		
		std::cout << "accessing by index: " << x[1] << std::endl;

		std::cout << "pushing and popping: " << std::endl;
		x.push_front(0);
		x.pop_back();

		y.push_back(4);
		y.pop_front();

		std::cout << "comparing:" << std::endl;
		std::cout << (
			(x <=> y) == 0 ? "x == y" :
			(x <=> y) <  0 ? "x <  y" :
			(x <=> y) >  0 ? "x >  y" : ""
			) << std::endl;

		std::cout << "erasing all of the values:";
		x.clear();
		y.clear();
	}

	{
		std::cout << std::endl << "std::optional" << std::endl;

		// std::optional is a universal null object. It may contain
		// something as well as do not contain.
		
		auto x{ std::make_optional(1) };
		auto y{ std::make_optional<int>() };
		std::optional<int> z;

		std::cout << "checking values: "
			<< "x " << (x ? "has value" : "has no value") << ", "
			<< "y " << (y ? "has value" : "has no value") << ", "
			<< "z " << (z ? "has value" : "has no value")
			<< std::endl;

		std::cout << "extracting values: "
			<< "x = " << *x << ", "
			<< "y = " << *y << ", "
			<< "z = " << *z
			<< std::endl;

		std::cout << "modifying optional:" << std::endl;
		y = 10;

		std::cout << "extracting values with alternative: "
			<< "x = " << x.value_or(300) << ", "
			<< "y = " << y.value_or(300) << ", "
			<< "z = " << z.value_or(300)
			<< std::endl;

		std::cout << "returning optional: ";
		auto lambda = [](bool val) -> std::optional<int>
		{
			if (val)
			{
				return 10;
			}
			else
			{
				return {};
			}
		};
		std::cout
			<< lambda(true).value_or(300)
			<< lambda(false).value_or(300)
			<< std::endl;

		std::cout << "clearing the optional: ";
		x.reset();
		std::cout << "x = " << x.value_or(300) << std::endl;
	}

	{
		std::cout << std::endl << "std::any" << std::endl;

		// std::any is a variable that may contain value of any type.
		// It may change it's type whan assigning new value.
		auto x{ std::make_any<int>(1) };

		std::cout << "extracting value from any: "
			<< x.type().name() << " x = "
			<< std::any_cast<int>(x)
			<< std::endl;

		std::cout << "assigning value to any: ";
		x = 3.14;
		std::cout << x.type().name() << " x = "
			<< std::any_cast<double>(x)
			<< std::endl;
	}

	{
		std::cout << std::endl << "std::variant" << std::endl;

		// std::variant like std::any can hold the object of several
		// typed, but the type list is pre-defined

		auto lambda{
			[](bool val) -> std::variant<int, bool>
			{
				if (val)
				{
					return 300;
				}
				else
				{
					return false;
				}
			}
		};

		auto x{ std::variant<int, bool>{ 10 } };

		std::cout << "extracting values from variant: ";
		std::cout << std::get<int>(x) << std::endl;

		auto p{ std::get_if<bool>(&x) };
		std::cout << "pointer to the bool variant: " << p << std::endl;

		std::cout << "handling lambda result: ";
		std::visit([](auto&& arg) { std::cout << arg; }, lambda(true));
		std::visit([](auto&& arg) { std::cout << arg; }, lambda(false));
		std::cout << std::endl;
	}

	return 0;
}
