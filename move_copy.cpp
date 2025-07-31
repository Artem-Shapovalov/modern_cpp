#include <iostream>
#include <memory>
#include <string>

/** \brief Example class implementation for shallow copy */
class ShallowCopyableDummy
{
	public:
		/** \brief   Constructor
		 *  \details Just initializes data pointer
		 *  \param   data String literal to initialize the memory */
		ShallowCopyableDummy(const char* data)
			: data(std::make_shared<std::string>(data))
		{
			std::cout << "ShallowCopyableDummy constructor"
				<< std::endl;
		}

		/** \brief   Copy constructor
		 *  \details Initializes the data pointer with copy constructor
		 *           of the std::shared_ptr
		 *  \param   obj Constant reference to the initializer object */
		ShallowCopyableDummy(const ShallowCopyableDummy& obj)
			: data(obj.data)
		{
			std::cout << "ShallowCopyableDummy copy constructor"
				<< std::endl;
		}

		/** \brief   Copy assignment
		 *  \details Does the same as copy constructor
		 *  \param   obj Constant reference to the initializer object */
		ShallowCopyableDummy& operator=(const ShallowCopyableDummy& obj)
		{
			std::cout << "ShallowCopyableDummy copy assignment"
				<< std::endl;

			data = obj.data;
			return *this;
		}

		/** \brief   Destructor
		 *  \details All of destructors should be virtual because it
		 *           safer in case of future inheritance */
		virtual ~ShallowCopyableDummy()
		{
			std::cout << "ShallowCopyableDummy destructor"
				<< std::endl;
		}

		/** \brief   Pointer to store the data
		 *  \details This pointer is made shared because it supports
		 *           copying */
		std::shared_ptr<std::string> data;
};

/** \brief Example class implementation for deep copy */
class DeepCopyableDummy
{
	public:
		/** \brief   Constructor
		 *  \details Just initializes data pointer
		 *  \param   data String literal to initialize the memory */
		DeepCopyableDummy(const char* data)
			: data(std::make_unique<std::string>(data))
		{
			std::cout << "DeepCopyableDummy constructor"
				<< std::endl;
		}

		/** \brief   Copy constructor
		 *  \details Deep copy constructor and Shallow copy constructor
		 *           have the same signature, but they differs by their
		 *           behavior. This constructor initializes the new
		 *           string object with the data from the source object.
		 *  \param   obj Constant reference to the initializer object */
		DeepCopyableDummy(const DeepCopyableDummy& obj)
			: data(std::make_unique<std::string>(*obj.data))
		{
			std::cout << "DeepCopyableDummy copy constructor"
				<< std::endl;
		}

		/** \brief   Copy assignment
		 *  \details Does the same as copy constructor
		 *  \param   obj Constant reference to the initializer object */
		DeepCopyableDummy& operator=(const DeepCopyableDummy& obj)
		{
			std::cout << "DeepCopyableDummy copy assignment"
				<< std::endl;

			data = std::make_unique<std::string>(*obj.data);
			return *this;
		}

		/** \brief   Destructor
		 *  \details All of destructors should be virtual because it
		 *           safer in case of future inheritance */
		virtual ~DeepCopyableDummy()
		{
			std::cout << "DeepCopyableDummy destructor"
				<< std::endl;
		}

		/** \brief   Pointer to store the data
		 *  \details This pointer is made shared because it supports
		 *           copying */
		std::unique_ptr<std::string> data;
};

/** \brief Example class implementation for move */
class MovableDummy
{
	public:
		/** \brief   Constructor
		 *  \details Just initializes data pointer
		 *  \param   data String literal to initialize the memory */
		MovableDummy(const char* data)
			: data(std::make_unique<std::string>(data))
		{
			std::cout << "MovableDummy constructor"
				<< std::endl;
		}

		/** \brief   Moving constructor
		 *  \details Initializes the data pointer as the deep copy and
		 *           discards the source object
		 *  \param   obj Universal reference to the initializer object.
		 *           note: Universal reference may lead to rvalue as
		 *                 well as to lvalue */
		MovableDummy(MovableDummy&& obj)
			: data(std::make_unique<std::string>(*obj.data))
		{
			std::cout << "MovableDummy moving constructor"
				<< std::endl;
			obj.data.release();
		}

		/** \brief   Moving assignment
		 *  \details Does the same as moving constructor
		 *  \param   obj Universal reference to the initializer object.
		 *           note: Universal reference may lead to rvalue as
		 *                 well as to lvalue */
		MovableDummy& operator=(MovableDummy&& obj)
		{
			std::cout << "MovableDummy moving assignment"
				<< std::endl;

			data = std::make_unique<std::string>(*obj.data);
			return *this;
		}

		/** \brief   Destructor
		 *  \details All of destructors should be virtual because it
		 *           safer in case of future inheritance */
		virtual ~MovableDummy()
		{
			std::cout << "MovableDummy destructor"
				<< std::endl;
		}

		/** \brief   Pointer to store the data */
		std::unique_ptr<std::string> data;
};

int main(int argc, char** argv)
{
	std::cout << "Modern C++ move and copy semantics demo" << std::endl;
	
	{
		std::cout << std::endl << "Shallow copy" << std::endl;

		// Shallow copy means just copying the pointers, but not data
		// behind them. This way we have two pointers, referencing
		// to the same data. This why these object depends each other
		// through data.

		// x is std::shared_ptr holiding pointer to allocated memory
		auto x{ std::make_shared<std::string>("x") };

		// y is std::shared_ptr too, but together they're hold pointer
		// to the same memory, handle the same counters and so on.
		// std::shared_ptr supports shallow copy right in it's
		// constructor.
		auto y{ x };

		std::cout << "Initial state" << std::endl;
		std::cout << "x = " << *x << std::endl;
		std::cout << "y = " << *y << std::endl;

		// Changing x makes change in y, because they refers to the
		// same memory.
		
		std::cout << "Changing x" << std::endl;
		*x = "changed";
		std::cout << "x = " << *x << std::endl;
		std::cout << "y = " << *y << std::endl;

		std::cout << "Changing y" << std:: endl;
		*y = "changed again";
		std::cout << "x = " << *x << std::endl;
		std::cout << "y = " <<* y << std::endl;
	}

	{
		std::cout << std::endl << "Deep copy (clone)" << std::endl;
		
		// Deep copy means that copies exactly data, not pointers, and
		// as a result, having two separate identical objects. In this
		// case changes on one of the objects do not affect to another.

		// x is std::unique_ptr holding pointer to allocated memory
		auto x{ std::make_unique<std::string>("x") };

		// y is std::unique_ptr holding pointer to another allocated
		// memory with copy of data from x. As std::unique_ptr is
		// developed not being copyable, deep copy is implemented
		// outside of the class.
		auto y{ std::make_unique<std::string>(*x) };

		std::cout << "Initial state" << std::endl;
		std::cout << "x = " << *x << std::endl;
		std::cout << "y = " << *y << std::endl;

		// Changing x makes no changes in y, they refers to separate
		// memory.
		
		std::cout << "Changing x" << std:: endl;
		*x = "changed";
		std::cout << "x = " << *x << std::endl;
		std::cout << "y = " << *y << std::endl;

		std::cout << "Changing y" << std::endl;
		*y = "changed again";
		std::cout << "x = " << *x << std::endl;
		std::cout << "y = " << *y << std::endl;
	}

	{
		std::cout << std::endl << "Moving data" << std::endl;
		// Move semantics allows transfer data from one object to
		// another.

		// This is an initial object, that would be source for data for
		// another. Despite it's std::unique_ptr and it can not be
		// passed to the constructor or assigned to another object, it
		// would be correctly assigned with the move semantics.
		auto x{ std::make_unique<std::string>("x") };
		std::cout << "x = " << *x << "(" << x.get() << ")" << std::endl;

		auto y{ std::move(x) }; // at this point x would be discarded
		std::cout << "y = " << *y << "(" << y.get() << ")" << std::endl;

		// See that now inside the x the null pointer is stored. Any
		// attempt to dereference it leads to segmentation fault.
		std::cout << "x = n/a(" << x.get() << ")" << std::endl;
	}

	{
		std::cout << std::endl << "Shallow copy class" << std::endl;

		ShallowCopyableDummy x("x");
		auto y{ x };
		ShallowCopyableDummy z("z");
		z = x;
		
		std::cout << "Initial state" << std::endl;
		std::cout << "x: " << *x.data << std::endl;
		std::cout << "y: " << *y.data << std::endl;
		std::cout << "z: " << *z.data << std::endl;

		std::cout << "Changing data" << std::endl;
		*x.data = "changed";
		std::cout << "x: " << *x.data << std::endl;
		std::cout << "y: " << *y.data << std::endl;
		std::cout << "z: " << *z.data << std::endl;
	}

	{
		std::cout << std::endl << "Deep copy class" << std::endl;

		DeepCopyableDummy x("x");
		auto y{ x };
		DeepCopyableDummy z("z");
		z = x;
		
		std::cout << "Initial state" << std::endl;
		std::cout << "x: " << *x.data << std::endl;
		std::cout << "y: " << *y.data << std::endl;
		std::cout << "z: " << *z.data << std::endl;

		std::cout << "Changing data" << std::endl;
		*x.data = "changed";
		std::cout << "x: " << *x.data << std::endl;
		std::cout << "y: " << *y.data << std::endl;
		std::cout << "z: " << *z.data << std::endl;
	}

	{
		std::cout << std::endl << "Move class" << std::endl;

		MovableDummy x("x");
		std::cout << "x: " << *x.data << "(" << x.data.get() << ")"
			<< std::endl;

		auto y{ std::move(x) };
		std::cout << "x: n/a(" << x.data.get() << ")" << std::endl;
		std::cout << "y: " << *y.data << "(" << y.data.get() << ")"
			<< std::endl;

		MovableDummy z("z");
		z = std::move(y);
		std::cout << "x: n/a(" << x.data.get() << ")" << std::endl;
		std::cout << "y: n/a(" << y.data.get() << ")" << std::endl;
		std::cout << "z: " << *z.data << "(" << z.data.get() << ")"
			<< std::endl;
	}

	return 0;
}
