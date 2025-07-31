#include <iostream>
#include <deque>
#include <vector>
#include <ranges>
#include <algorithm>

int main(int argc, char** argv)
{
	std::cout << "Algorithms demo" << std::endl;

	// In modern C++ since 2020 the ranges library was introduces.
	// It provides an abstraction layer for all of the containers and
	// unifies the algorithms to apply on it.
	// Actually all of the containers are ranges, they're holds data inside,
	// but to effectively interact with theme there is another abstration
	// layer - views. Views are adaptors to the ranges, that helps us to
	// do such of things.
	auto x{ std::deque<int>() }; // This is a range
	auto x_view{ std::views::all(x) }; // That's view
	auto y{ std::vector<int>() };

	{
	std::cout << "basic for-each loop container iteration: ";
	x = { 1, 2, 3, 4, 5 };
	for (auto& i : x) { std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "for-each iteration throught container with ranges: ";
	x = { 1, 2, 3, 4, 5 };
	std::ranges::for_each(x,
		[](auto& i) -> void
		{
			std::cout << i << " ";
		});
	std::cout << std::endl;
	}

	{
	std::cout << "for-each iterating with views: ";
	x = { 1, 2, 3, 4, 5 };
	x_view = std::views::all(x);
	for (auto& i : x_view) { std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "iterating container with iterator: ";
	x = { 1, 2, 3, 4, 5 };
	for (
		auto i{ std::ranges::begin(x) };
		i != std::ranges::end(x);
		i++
	    )
	{ std::cout << *i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "iterating view with iterator: ";
	x = { 1, 2, 3, 4, 5 };
	x_view = std::views::all(x);
	for (
		auto i{ x_view.begin() };
		i != x_view.end();
		i++
	    )
	{ std::cout << *i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "iterating in for-each loop in reverse direction: ";
	x = { 1, 2, 3, 4, 5 };
	for (auto& i : x | std::views::reverse) { std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "iterating with a first 3 items in for-each loop: ";
	x = { 1, 2, 3, 4, 5 };
	for (auto& i : x | std::views::take(3)) { std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "iterating skipping first 3 items in for-each loop: ";
	x = { 1, 2, 3, 4, 5 };
	for (auto& i : x | std::views::drop(3)) { std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "combining techniques: ";
	x = { 1, 2, 3, 4, 5 };
	for (auto& i : x | std::views::take(4) | std::views::reverse)
	{ std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "iterating through the items by criteria: ";
	x = { 1, 2, 3, 4, 5 };
	for (auto& i : x | 
		std::views::filter([](auto v) -> bool { return v % 2 == 0; }))
	{ std::cout << i << " "; }
	std::cout << std::endl;
	}

	{
	std::cout << "getting size of the container: ";
	x = { 1, 2, 3, 4, 5 };
	std::cout << std::ranges::size(x) << std::endl;
	}

	{
	std::cout << "sorting: " << std::endl;
	x = { 4, 8, 45, 2, 4, 6, 9 };
	for (auto& i : x) { std::cout << i << " "; } std::cout << std::endl;
	std::ranges::sort(x);
	for (auto& i : x) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "sorting with specific order: " << std::endl;
	x = { 4, 8, 45, 2, 4, 6, 9 };
	for (auto& i : x) { std::cout << i << " "; } std::cout << std::endl;
	std::ranges::sort(x, [](auto& v, auto& _v) -> bool { return v > _v; });
	for (auto& i : x) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "copy values to another container: " << std::endl;
	x = { 1, 2, 3, 4, 5 };
	y = {};
	std::ranges::copy(x, std::back_inserter(y));
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	for (auto i : y) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "copy values by criteria: " << std::endl;
	x = { 1, 2, 3, 4, 5 };
	y = {};
	std::ranges::copy_if(x, std::back_inserter(y),
		[](int v) -> bool { return v % 2 == 0; });
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	for (auto i : y) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "copy first 3 values: " << std::endl;
	x = { 1, 2, 3, 4, 5 };
	y = {};
	std::ranges::copy_n(std::ranges::begin(x), 3, std::back_inserter(y));
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	for (auto i : y) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "remove items: " << std::endl;
	// note that the size of deque didn't changed
	x = { 1, 2, 3, 4, 5 };
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	std::ranges::remove(x, 2);
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "remove by criteria: " << std::endl;
	// note that the size of deque didn't changed
	x = { 1, 2, 3, 4, 5 };
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	std::ranges::remove_if(x, [](auto& v) -> bool { return v % 2 == 0; });
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "searching item: ";
	x = { 1, 2, 3, 4, 5 };
	auto it = std::ranges::find(x, 3);
	std::cout << *it << std::endl;
	}

	{
	std::cout << "inserting item: " << std::endl;
	x = { 1, 2, 3, 4, 5 };
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	auto it = std::ranges::begin(x);
	x.insert(it + 2, 0);
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	}

	{
	std::cout << "erasing item: " << std::endl;
	x = { 1, 2, 3, 4, 5 };
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	auto it = std::ranges::begin(x);
	x.erase(it + 2);
	for (auto i : x) { std::cout << i << " "; } std::cout << std::endl;
	}

	return 0;
}
