# provide a makefile with a target called shell_jr that 
# creates the executable shell_jr
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors \
         -fstack-protector-all -Wextra

shell_jr: shell_jr.c shell_jr.o
	gcc shell_jr.c -o shell_jr
	
shell_jr.o: shell_jr.c
	gcc $(CFLAGS) -c shell_jr.c -o shell_jr.o

clean:
	rm -f shell_jr shell_jr.o
