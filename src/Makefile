executables=w01-1 w01-2 w01-3 \
						w02-1 w02-2 \
						w03-1 w03-2 \
						w04-1 \
						w05-1 w05-2 \
						w06-1 \
						w07-1 w07-2 w07-3 \
						w09-1 \
						w10-1 w10-2 \
						w11-1 w11-2 \
						w12-1 \
						w13-1 \
						w14-1

# a little function to compile a single file source to target executable
define compile-single
	g++ -g -Wall -Werror -pedantic $< -o $@
endef


# build targets
all : $(executables)

w01-1 : w01-1-UserDefinedFunctions.cpp
	$(compile-single)

w01-2 : w01-2-UserDefinedDataTypes.cpp
	$(compile-single)

w01-3 : w01-3-Arrays.cpp
	# we have warnings for illustration but compile anyway despite warnings
	g++ -Wall -pedantic $^ -o $@

w02-1 : w02-1-Structs.cpp
	$(compile-single)

w02-2 : w02-2-Classes.cpp
	$(compile-single)

w03-1 : w03-1-Pointers.cpp
	# we have warnings for illustration but compile anyway despite warnings
	g++ -Wall -pedantic $^ -o $@

w03-2 : w03-2-DynamicMemory.cpp
	# we have warnings for illustration but compile anyway despite warnings
	g++ -Wall -pedantic $^ -o $@

w04-1 : w04-1-Recursion.cpp
	$(compile-single)

w05-1 : w05-1-Searching.cpp
	$(compile-single)

w05-2 : w05-2-Sorting.cpp
	$(compile-single)

w06-1 : w06-1-AnalysisAlgorithms.cpp
	$(compile-single)

w07-1 : w07-1-InheritanceComposition.cpp
	$(compile-single)

w07-2 : w07-2-Overloading.cpp
	# we have warnings for illustration but compile anyway despite warnings
	g++ -Wall -pedantic $^ -o $@

# first multi-file example, the Template example here
# uses both the Vector template class and the
# ComplexNumber class which is not a template class
w07-3 : w07-3-Templates.cpp Vector.hpp Vector.cpp ComplexNumber.o
	# compile the main file into an object file, the ComplexNumber.o
	# target takes care of compiling that file to its object file
	g++ -Wall -Werror -pedantic -c w07-3-Templates.cpp -o w07-3-Templates.o
	# link together object files into the target executable
	g++ -Wall -Werror -pedantic w07-3-Templates.o ComplexNumber.o -o $@

ComplexNumber.o : ComplexNumber.hpp ComplexNumber.cpp
	g++ -Wall -Werror -pedantic -c ComplexNumber.cpp -o ComplexNumber.o

w09-1 : w09-1-LinkedListFundamentals.cpp
	$(compile-single)

w10-1 : w10-1-Stacks-Implementation.cpp Stack.hpp Stack.cpp
	$(compile-single)

w10-2 : w10-2-Stacks-Applications.cpp Stack.hpp Stack.cpp
	$(compile-single)

w11-1 : w11-1-Queues-Implementation.cpp Queue.hpp Queue.cpp
	$(compile-single)

w11-2 : w11-2-Queues-Applications.cpp Queue.hpp Queue.cpp
	$(compile-single)

w12-1 : w12-1-Binary-Tree-Properties.cpp
	$(compile-single)

w13-1 : w13-1-Hashing-and-Dictionaries.cpp Dictionary.hpp Dictionary.cpp
	$(compile-single)

w14-1 : w14-1-STL-standard-template-library.cpp
	$(compile-single)



# other targets
.PHONY : clean
clean :
	rm -rf $(executables) *.o *.gch *.exe
