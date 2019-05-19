targets = $(basename $(wildcard *.cpp))

CXXFLAGS= -std=c++11 -g -Wall -Werror

all: $(targets)

$(targets): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(targets)

.PHONY: all clean
