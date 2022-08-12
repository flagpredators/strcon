BIN=gcc
CFLAGS=-g -Wall -Werror -Wextra
SRCDIR=src

all: strcon

strcon.o: $(SRCDIR)/strcon.c
	$(BIN) $(CFLAGS) -c $^

utils.o: $(SRCDIR)/utils.c
	$(BIN) $(CFLAGS) -c $^

file_handler.o: $(SRCDIR)/file_handler.c
	$(BIN) $(CFLAGS) -c $^

validate.o: $(SRCDIR)/validate.c
	$(BIN) $(CFLAGS) -c $^

strcon: strcon.o utils.o file_handler.o validate.o
	$(BIN) $(CFLAGS) $^ -o $@

clean:

ifeq ($(OS),Windows_NT)
	del *.o, strcon.exe
else
	rm *.o strcon
endif