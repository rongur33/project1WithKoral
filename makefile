# All Targets

all: bin/Tester
# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.

bin/Tester: bin/Order.o bin/Tester.o bin/Volunteer.o  bin/Customer.o
	g++ -o bin/Tester bin/Order.o bin/Tester.o bin/Volunteer.o  bin/Customer.o
# Depends on the source and header files

bin/Order.o: src/Order.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Order.o src/Order.cpp
# Depends on the source and header files

bin/Tester.o: src/Tester.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tester.o src/Tester.cpp

bin/Volunteer.o: src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Volunteer.o src/Volunteer.cpp

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp
bin/WareHouse.o: src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/WareHouse.o src/WareHouse.cpp

#Clean the build directory

clean:
	rm -f bin/*
