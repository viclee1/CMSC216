CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors \
	 -fstack-protector-all -Wextra

all: public01 public02 public03 public04 public05 public06 student_tests

clean:
	rm -f public01 public02 public03 public04 public05 public06 student_tests ./*.o

public01: my_memory_checker_216.o calendar.o public01.o
	$(CC) my_memory_checker_216.o calendar.o public01.o -o public01

public02: my_memory_checker_216.o calendar.o public02.o
	$(CC) my_memory_checker_216.o calendar.o public02.o -o public02

public03: my_memory_checker_216.o calendar.o public03.o
	$(CC) my_memory_checker_216.o calendar.o public03.o -o public03

public04: my_memory_checker_216.o calendar.o public04.o
	$(CC) my_memory_checker_216.o calendar.o public04.o -o public04

public05: my_memory_checker_216.o calendar.o public05.o
	$(CC) my_memory_checker_216.o calendar.o public05.o -o public05

public06: my_memory_checker_216.o calendar.o public06.o
	$(CC) my_memory_checker_216.o calendar.o public06.o -o public06

student_tests: my_memory_checker_216.o calendar.o student_tests.o
	$(CC) my_memory_checker_216.o calendar.o student_tests.o -o student_tests

calendar.o: calendar.c calendar.h
	$(CC) $(CFLAGS) -c calendar.c -o calendar.o

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
			 $(CC) $(CFLAGS) -c my_memory_checker_216.c -o my_memory_checker_216.o

public01.o: my_memory_checker_216.o calendar.o public01.o
	  $(CC) $(CFLAGS) -c public01.c
	  
public02.o: my_memory_checker_216.o calendar.o public02.o
	  $(CC) $(CFLAGS) -c public02.c

public03.o: my_memory_checker_216.o calendar.o public03.o
	  $(CC) $(CFLAGS) -c public03.c

public04.o: my_memory_checker_216.o calendar.o public04.o
	  $(CC) $(CFLAGS) -c public04.c

public05.o: my_memory_checker_216.o calendar.o public05.o
	  $(CC) $(CFLAGS) -c public05.c

public06.o: my_memory_checker_216.o calendar.o public06.o
	  $(CC) $(CFLAGS) -c public06.c

student_tests.o: my_memory_checker_216.o calendar.o student_tests.o
	       $(CC) $(CFLAGS) -c student_tests.c
