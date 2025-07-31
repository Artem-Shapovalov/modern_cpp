#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <semaphore>
#include <barrier>
#include <latch>
#include <vector>

int main(int argc, char** argv)
{
	std::cout << "Modern C++ multithreadin demo" << std::endl;

	{
	std::cout << "Basic thread: ";
	// thread would be immediately started
	auto t{ std::thread{ []() { std::cout << "I'm here" << std::endl; } } };
	// awaiting the thread finish
	t.join();
	}

	{
	std::cout << "Thread with arguments: ";
	auto func{
		[](int a, int b) -> void
		{
			std::cout << (a + b) << std::endl;
		}
	};
	auto t{ std::thread{ func, 1, 2 } };
	t.join();
	}

	{
	std::cout << "async thread starting with collecting result:  ";
	auto func{
		[](int a, int b) -> int
		{
			// async returns std::future<int>
			return a + b;
		}
	};
	auto res{ std::async(func, 1, 2) };
	std::cout << res.get() << std::endl;
	// no need to await thread end
	}

	{
	std::cout << "another unjoinable thread: ";

	auto func{
		[](std::promise<int> a, std::promise<int> b) -> void
		{
			std::this_thread::sleep_for(
					std::chrono::milliseconds(500));
			a.set_value(1);
			std::this_thread::sleep_for(
					std::chrono::milliseconds(500));
			b.set_value(2);
		}
	};
	auto pa{ std::promise<int>{} };
	auto fa{ pa.get_future() };
	auto pb{ std::promise<int>{} };
	auto fb{ pb.get_future() };
	auto t{ std::thread{ func, std::move(pa), std::move(pb) } };
	t.detach();

	std::cout << "fa: " << fa.get() << " " << std::flush;
	std::cout << "fb: " << fb.get() << std::endl;
	}

	{
	std::cout << "basic mutex: ";

	auto m{ std::mutex{} };
	auto v{ 3.14 };
	auto func{
		[&]() -> void
		{
			m.lock();
			// thread can't change the v in the same time as
			// main thread
			v = 2.73;
			m.unlock();
		}
	};
	auto t{ std::thread{ func } };

	m.lock();
	// If mutex already locked, this attempt to lock it would wait for
	// mutex would be released.
	v = 9.81;
	m.unlock();

	t.join();
	std::cout << v << std::endl;
	}

	{
	std::cout << "automating lock and unlock with lock_guard: ";
	auto m{ std::mutex{} };
	auto v{ 3.14 };
	auto func{
		[&]() -> void
		{
			auto lock{ std::lock_guard(m) };
			// Now the mutex is locked

			v = 2.73;
			// Mutex would be released during 'lock' destruction
		}
	};
	auto t{ std::thread{ func } };

	{
		auto lock{ std::lock_guard(m) };
		v = 9.81;
	}

	t.join();
	std::cout << v << std::endl;
	}

	{
	std::cout << "Preventing multiple access with atomic variables: ";
	auto v{ std::atomic{ 3.14 } };
	auto func{
		[&]() -> void
		{
			// v is an object, that hides mutex inside, and
			// with overloaded '=' operator it automatically
			// locks and unlocks the mutex
			v = 2.73;
		}
	};
	auto t{ std::thread{ func } };
	t.join();
	v = 9.81;
	std::cout << v << std::endl;
	}

	{
	std::cout << "limiting threads with semaphores:" << std::endl;
	// In this example not more than 3 threads may be active.
	// Semaphore allows numerous lock attempts before it would be locked
	// as mutex.
	auto s{ std::counting_semaphore(3) };
	auto func{
		[&](int num) -> void
		{
			s.acquire();
			std::cout << std::flush
				<< "Thread " << num << "started"
				<< std::endl;
			std::this_thread::sleep_for(
					std::chrono::milliseconds(500));
			std::cout << std::flush
				<< "Thread " << num << "ended"
				<< std::endl;
			s.release();
		}
	};

	auto t{ std::vector<std::thread>{} };
	for (auto i{ 0 }; i < 10; i++) { t.push_back( std::thread{ func, i} ); }
	for (auto& _t : t) { _t.join(); }
	}

	{
	std::cout << "using barriers to pause the threads at the same point: ";
	auto sync_point{ std::barrier(3) };
	auto func{
		[&](int id) -> void
		{
			std::cout << ">" << std::flush;
			std::this_thread::sleep_for(
					std::chrono::milliseconds(id * 1000));
			std::cout << id << std::flush;

			// The thread go forward only when 3 threads
			// would arrive and wait.
			sync_point.arrive_and_wait();
			std::cout <<  "." << std::flush;
		}
	};
	auto t{ std::vector<std::thread>{} };
	for (int i{ 0 }; i < 3; i++) { t.push_back(std::thread{ func, i+1 }); }
	for (auto& thread : t) { thread.join(); }
	std::cout << std::endl;
	}

	{
	std::cout << "waiting for all of the threads do their job: ";
	auto sync_point{ std::latch(3) };
	auto func {
		[&](int id) -> void
		{
			std::cout << ">" << std::flush;
			std::this_thread::sleep_for(
					std::chrono::milliseconds(id * 1000));
			sync_point.count_down();
			std::cout << id << std::flush;
		}
	};

	auto t{ std::vector<std::thread>{} };
	for (int i{ 0 }; i < 3; i++) { t.push_back(std::thread{ func, i+1 }); }
	for (auto& thread : t) { thread.detach(); }

	std::cout << "waiting for threads: ";
	// Note: you may wait only once! Latches are not reusable.
	sync_point.wait();

	std::cout << "..." << std::endl;
	}

	{
	std::cout << "remote control of threads with conditional variable: ";
	auto cv{ std::condition_variable{} };
	auto func {
		[&]() -> void
		{
			auto m{ std::mutex{} };
			auto lock{ std::unique_lock<std::mutex>{ m } };
			std::cout << ">" << std::flush;
			cv.wait(lock);
			std::cout << "<" << std::flush;
		}
	};
	auto t{ std::vector<std::thread>{} };
	for (int i{ 0 }; i < 3; i++) { t.push_back(std::thread{ func }); }

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cv.notify_one(); // one of the waiting threads would be unlocked
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cv.notify_all(); // rest of the waiting threads would be unlocked

	for (auto& thread : t) { thread.join(); }
	std::cout << std::endl;
	}

	return 0;
}
