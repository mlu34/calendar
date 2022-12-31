CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors \
         -fstack-protector-all -Wextra
PROGS = public01 public02 public03 public04 public05 student_tests


all: $(PROGS)

public01: public01.o calendar.o my_memory_checker_216.o 
	$(CC) $(CFLAGS) -c public01.c
	$(CC) -o public01 public01.o calendar.o my_memory_checker_216.o
    
public02: public02.o calendar.o my_memory_checker_216.o 
	$(CC) $(CFLAGS) -c public02.c
	$(CC) -o public02 public02.o calendar.o my_memory_checker_216.o

public03: public03.o calendar.o my_memory_checker_216.o 
	$(CC) $(CFLAGS) -c public03.c
	$(CC) -o public03 public03.o calendar.o my_memory_checker_216.o

public04: public04.o calendar.o my_memory_checker_216.o 
	$(CC) $(CFLAGS) -c public04.c
	$(CC) -o public04 public04.o calendar.o my_memory_checker_216.o

public05: public05.o calendar.o my_memory_checker_216.o 
	$(CC) $(CFLAGS) -c public05.c
	$(CC) -o public05 public05.o calendar.o my_memory_checker_216.o


student_tests: student_tests.o calendar.o my_memory_checker_216.o event.h
	$(CC) -o student_tests student_tests.o calendar.o my_memory_checker_216.o

students_tests.o: student_tests.c event.h calendar.h 
	$(CC) $(CFLAGS) -c student_tests.c 

calendar.o: calendar.c calendar.h event.h
	$(CC) $(CFLAGS) -c calendar.c

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	$(CC) $(CFLAGS) -c my_memory_checker_216.c


clean:
	@echo "Removing object, executable, and core files."
	rm -f *.o *~core core.*

