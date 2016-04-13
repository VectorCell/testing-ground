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
LIBFLAGS := 

all: parallelization

parallelization : parallelization.cc
	$(CXX) $(CPPFLAGS) -o parallelization parallelization.cc $(LIBFLAGS)

test : all
	./parallelization

clean :
	rm -f *.o
	rm -f *.d
	rm -f *.elf
	rm -f *.class
	rm -f *.pyc
	rm -f *.out
	rm -f parallelization

-include *.d
