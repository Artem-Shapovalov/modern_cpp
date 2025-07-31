FLAGS += -std=c++20

all: memory.example
all: move_copy.example
all: containers.example
all: functions.example
all: algorithm.example
all: multithreading.example
all: templates.example

run: all
	./memory.example
	./move_copy.example
	./containers.example
	./functions.example
	./algorithm.example
	./multithreading.example
	./templates.example

memory.example: memory.cpp
	${CXX} memory.cpp -o memory.example ${FLAGS}
memory.cpp:

move_copy.example: move_copy.cpp
	${CXX} move_copy.cpp -o move_copy.example ${FLAGS}
move_copy.cpp:

containers.example: containers.cpp
	${CXX} containers.cpp -o containers.example ${FLAGS}
containers.cpp:

functions.example: functions.cpp
	${CXX} functions.cpp -o functions.example ${FLAGS}
functions.cpp:

algorithm.example: algorithm.cpp
	${CXX} algorithm.cpp -o algorithm.example ${FLAGS}
algorithm.cpp:

multithreading.example: multithreading.cpp
	${CXX} multithreading.cpp -o multithreading.example ${FLAGS}
multithreading.cpp:

templates.example: templates.cpp
	${CXX} templates.cpp -o templates.example ${FLAGS}
templates.cpp:

clean:
	rm -rf *.example
