CXX= g++
CXXFLAGS= -g -Wall -std=gnu++11
LDFLAGS=
SHELL= bash
PROGRAMS= AES
SOURCES= main.cpp cipher.cpp BaseOps.cpp invCipher.cpp keyExpansion.cpp
OBJECTS= $(SOURCES:.cpp=.o)

all: $(PROGRAMS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

AES: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f $(PROGRAMS) $(OBJECTS)

test: test-output

test-output: $(PROGRAMS)
	@echo "Testing output..."
	@diff --suppress-common-lines -y <(./AES) appendix_c.txt
