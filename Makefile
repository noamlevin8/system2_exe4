#ID: 326662574
#MAIL: noamlevin11@gmail.com

CXX = clang++
CXXFLAGS = -std=c++14 -Werror -Wsign-conversion -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

DEMOSOURCES = Node.hpp Tree.hpp Demo.cpp Complex.cpp
TESTSOURCES = Node.hpp Tree.hpp TestCounter.cpp Test.cpp Complex.cpp
DEMOOBJECTS = $(subst .cpp,.o,$(filter %.cpp,$(DEMOSOURCES)))
TESTOBJECTS = $(subst .cpp,.o,$(filter %.cpp,$(TESTSOURCES)))

all: demo test

demo: $(DEMOOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o demo

test: $(TESTOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o test

tidy:
	clang-tidy $(filter %.cpp,$(DEMOSOURCES)) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test

.PHONY: all demo test tidy valgrind clean