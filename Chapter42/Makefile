CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -pthread

SOURCES = main.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

MAIN = main
default: $(MAIN)

$(MAIN):$(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(MAIN) *o


