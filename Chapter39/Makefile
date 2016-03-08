CC = clang++
CFLAGS = -std=c++11 -Wall -Wextra -fno-omit-frame-pointer -fno-exceptions #-fno-rtti

SOURCES = main.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

MAIN = main
default: $(MAIN)

$(MAIN):$(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(MAIN) *o


