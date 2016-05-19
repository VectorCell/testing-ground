CSTD   := c99
CPPSTD := c++11

ifeq "$(CXX)" "g++"
	GCCVERSIONLT48 := $(shell expr `gcc -dumpversion` \< 4.8)
	ifeq "$(GCCVERSIONLT48)" "1"
		CPPSTD := c++0x
	endif
endif

CFLAGS   := -pedantic -std=$(CSTD) -Wall -Werror -O3
CPPFLAGS := -pedantic -std=$(CPPSTD) -Wall -Werror -O3
LIBFLAGS := -fopenmp

all: temp parallelization simple-bench output-sparse

temp : temp.cc
	$(CXX) $(CPPFLAGS) -o temp temp.cc $(LIBFLAGS)

parallelization : parallelization.cc
	$(CXX) $(CPPFLAGS) -o parallelization parallelization.cc $(LIBFLAGS)

simple-bench : simple-bench.cc
	$(CXX) $(CPPFLAGS) -o simple-bench simple-bench.cc $(LIBFLAGS)

output-sparse : output-sparse.cc
	$(CXX) $(CPPFLAGS) -o output-sparse output-sparse.cc $(LIBFLAGS)

test : temp
	./temp < temp.in

test-parallelization : parallelization
	./parallelization

test-simple-bench : simple-bench
	timeout --preserve-status --signal=SIGINT 1 ./simple-bench

test-output-sparse : output-sparse
	./output-sparse.sh

clean :
	rm -f *.o
	rm -f *.d
	rm -f *.elf
	rm -f *.class
	rm -f *.pyc
	rm -f *.out
	rm -f temp
	rm -f parallelization
	rm -f simple-bench
	rm -f output-sparse

-include *.d
