APP_NAME=a

CC = g++
CFLAGS = -Wall -std=c++11

TEST_CFLAGS = -fsanitize=leak

TARGETS = ./main.cpp
DEPS = $(TARGETS)  ./include/*.hpp

default: $(DEPS)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -o $(APP_NAME).out $(TARGETS)

test:
	make default
	./$(APP_NAME).out

clean:
	rm *.out