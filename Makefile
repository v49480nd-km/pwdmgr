CC = gcc
CFLAGS = -Wall -g -O3 -std=c17 -pipe -Wextra -Wpedantic -march=native
RM = rm -f
TARGET = pwdmgr
SOURCES = main.c utils.c
HEADERS = utils.h
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(TARGET)

