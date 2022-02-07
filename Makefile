# source files in this project 
VERSION=0.3
BASE_DIR := ../assg-base-$(VERSION)

# template files, list all files that define template classes
# or functions and should not be compiled separately (template
# is included where used)
template_files =

# compiler flags, tools and include variables
VERSION=0.3
BASE_NAME=assg-base-$(VERSION)
BASE_DIR := ../$(BASE_NAME)
GCC_FLAGS=-Wall -Werror -pedantic -g
GCC_FLAGS_NOERROR=-Wall -pedantic -g
GCC=g++
INC=-Iinclude -I$(BASE_DIR)/include

FORMATTER=clang-format
DOC=doxygen
PANDOC=pandoc
RM=rm -rf

FORMATTER_FLAGS=-i
DOC_FLAGS=$(BASE_DIR)/config/Doxyfile
PANDOC_FLAGS=-s --variable geometry:margin=0.75in --variable urlcolor:NavyBlue --variable colorlinks:true
PANDOC_HIGHLIGHT=--highlight-style tango

SRC_DIR := src
OBJ_DIR := obj
DOC_DIR := doc
BIN_DIR := bin

# all lecture example target executables
example_targets = u01-1 u01-2 u01-3 u02-1 u02-2 u03-1 u03-2 u04-1 u05-1 u05-2 \
	u06-1 u07-1 u07-2 u07-3 u09-1 u10-1 u10-2 u11-1 u11-2 u12-1 u13-1 u14-1 \
	g01-1 g02-1 g02-2 g03-1 g03-2 g03-3 g03-6
example_targets := $(patsubst %, $(BIN_DIR)/%, $(example_targets))

# pdf files for example repository description documentation
readme_doc = readme.pdf
readme_doc := $(patsubst %.pdf, $(DOC_DIR)/%.pdf, $(readme_doc))


## List of all valid targets in this project:
## ---------------------------------------------------------
## all          : By default generate all lecture
##                code example executables.  Executables
##                are compiled into the bin directory.
##
.PHONY : all
all : $(example_targets)

## u01-1        : Unit 01-1 User Defined Functions examples
##
$(BIN_DIR)/u01-1 : $(OBJ_DIR)/u01-1-UserDefinedFunctions.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS) $< -o $@

## u01-2        : Unit 01-2 User Defined Data Types examples
##
$(BIN_DIR)/u01-2 : $(OBJ_DIR)/u01-2-UserDefinedDataTypes.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS) $< -o $@

## u01-3        : Unit 01-3 C/C++ Arrays examples
##
$(BIN_DIR)/u01-3 : $(OBJ_DIR)/u01-3-Arrays.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS) $< -o $@


## u02-1        : Unit 02-1 C/C++ Structures
##
$(BIN_DIR)/u02-1 : $(OBJ_DIR)/u02-1-Structs.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS) $< -o $@

## u02-2        : Unit 02-2 C++ Classes
##
$(BIN_DIR)/u02-2 : $(OBJ_DIR)/u02-2-Classes.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS) $< -o $@

## u03-1        : Unit 03-1 Pointer Variables
##
$(BIN_DIR)/u03-1 : $(OBJ_DIR)/u03-1-Pointers.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u03-2        : Unit 03-2 Dynamic Memory
##
$(BIN_DIR)/u03-2 : $(OBJ_DIR)/u03-2-DynamicMemory.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS) $< -o $@

## u04-1        : Unit 04-1 Recursion
##
$(BIN_DIR)/u04-1 : $(OBJ_DIR)/u04-1-Recursion.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u05-1        : Unit 05-1 Searching
##
$(BIN_DIR)/u05-1 : $(OBJ_DIR)/u05-1-Searching.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u05-2        : Unit 05-2 Sorting
##
$(BIN_DIR)/u05-2 : $(OBJ_DIR)/u05-2-Sorting.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u06-1        : Unit 06-1 Analysis of Algorithms
##
$(BIN_DIR)/u06-1 : $(OBJ_DIR)/u06-1-AnalysisAlgorithms.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u07-1        : Unit 07-1 Inheritance and Composition
##
$(BIN_DIR)/u07-1 : $(OBJ_DIR)/u07-1-InheritanceComposition.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u07-2        : Unit 07-2 Overloading
##
$(BIN_DIR)/u07-2 : $(OBJ_DIR)/u07-2-Overloading.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $< -o $@

## u07-3        : Unit 07-3 Templates
##
$(BIN_DIR)/u07-3 : $(OBJ_DIR)/u07-3-Templates-finaltemplate.o $(OBJ_DIR)/ComplexNumber.o $(OBJ_DIR)/Vector.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u09-1        : Unit 09-1 Linked List Fundamentals
##
$(BIN_DIR)/u09-1 : $(OBJ_DIR)/u09-1-LinkedListFundamentals.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u10-1        : Unit 10-1 Implementaiton of Stacks
##
$(BIN_DIR)/u10-1 : $(OBJ_DIR)/u10-1-Stacks-Implementation.o  $(OBJ_DIR)/Stack.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u10-2        : Unit 10-2 Applications of Stacks
##
$(BIN_DIR)/u10-2 : $(OBJ_DIR)/u10-2-Stacks-Applications.o $(OBJ_DIR)/Stack.o  | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u11-1        : Unit 11-1 Implementation of Queues
##
$(BIN_DIR)/u11-1 : $(OBJ_DIR)/u11-1-Queues-Implementation.o  $(OBJ_DIR)/Queue.o $(OBJ_DIR)/Customer.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u11-2        : Unit 11-2 Applications of Queues
##
$(BIN_DIR)/u11-2 : $(OBJ_DIR)/u11-2-Queues-Applications.o  $(OBJ_DIR)/Queue.o $(OBJ_DIR)/Customer.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u12-1        : Unit 12-1 Binary Tree Properties
##
$(BIN_DIR)/u12-1 : $(OBJ_DIR)/u12-1-Binary-Tree-Properties.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u13-1        : Unit 13-1 Hashing and Dictionaries
##
$(BIN_DIR)/u13-1 : $(OBJ_DIR)/u13-1-Hashing-and-Dictionaries.o $(OBJ_DIR)/Dictionary.o $(OBJ_DIR)/Employee.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

## u14-1        : Unit 14-1 STL Standard Template Library
##
$(BIN_DIR)/u14-1 : $(OBJ_DIR)/u14-1-STL-standard-template-library.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g01-1 : $(OBJ_DIR)/g01-1-QuickFind.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g02-1 : $(OBJ_DIR)/g02-1-recurrence-relations.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g02-2 : $(OBJ_DIR)/g02-2-algorithm-analysis.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g03-1 : $(OBJ_DIR)/g03-1-lg-function.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g03-2 : $(OBJ_DIR)/g03-2-types-of-numbers.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g03-3 : $(OBJ_DIR)/g03-3-point-struct.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@

$(BIN_DIR)/g03-6 : $(OBJ_DIR)/g03-6-sieve-of-eratosthenes.o | $(BIN_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $^ -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(GCC) $(GCC_FLAGS_NOERROR) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@


## readme       : Create repository pdf documentation from
##                README.md project markdown file.
##
.PHONY : readme
readme : $(readme_doc)

$(readme_doc) : README.md
	${PANDOC} ${PANDOC_FLAGS} ${PANDOC_HIGHLIGHT} -o $@ $^


## format       : Run the code formatter/beautifier by hand if needed
##
.PHONY : format
format :
	$(FORMATTER) $(FORMATTER_FLAGS) include/*.hpp src/*.cpp


## clean        : Remove auto-generated files for a completely
##                clean rebuild
##
.PHONY : clean
clean  :
	$(RM) $(TEST_TARGET) $(DEBUG_TARGET) *.o *.gch
	$(RM) output html latex
	$(RM) $(OBJ_DIR) $(BIN_DIR)


## help         : Get all build targets supported by this build.
##
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $^
