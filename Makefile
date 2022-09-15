CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x \
public08.x public09.x public10.x public11.x public12.x public13.x public14.x public15.x 

public01.x: ournix.o public01.o
	$(CC) ournix.o public01.o -o public01.x

public02.x: ournix.o public02.o
	$(CC) ournix.o public02.o -o public02.x

public03.x: ournix.o public03.o
	$(CC) ournix.o public03.o -o public03.x

public04.x: ournix.o public04.o
	$(CC) ournix.o public04.o -o public04.x

public05.x: ournix.o public05.o
	$(CC) ournix.o public05.o -o public05.x

public06.x: ournix.o public06.o
	$(CC) ournix.o public06.o -o public06.x

public07.x: ournix.o public07.o
	$(CC) ournix.o public07.o -o public07.x

public08.x: ournix.o public08.o
	$(CC) ournix.o public08.o -o public08.x

public09.x: ournix.o public09.o
	$(CC) ournix.o public09.o -o public09.x

public10.x: ournix.o public10.o driver.o
	$(CC) ournix.o public10.o driver.o -o public10.x

public11.x: ournix.o public11.o
	$(CC) ournix.o public11.o -o public11.x

public12.x: ournix.o public12.o
	$(CC) ournix.o public12.o -o public12.x

public13.x: ournix.o public13.o
	$(CC) ournix.o public13.o -o public13.x

public14.x: ournix.o public14.o memory-checking.o
	$(CC) ournix.o public14.o memory-checking.o -o public14.x

public15.x: ournix.o public15.o memory-checking.o
	$(CC) ournix.o public15.o memory-checking.o -o public15.x

ournix.o: ournix.c ournix.h
	$(CC) $(CFLAGS) -c ournix.c

public01.o: public01.c ournix.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c ournix.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c ournix.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c ournix.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c ournix.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c ournix.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c ournix.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c ournix.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c ournix.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c ournix.h driver.h
	$(CC) $(CFLAGS) -c public10.c

public11.o: public11.c ournix.h
	$(CC) $(CFLAGS) -c public11.c

public12.o: public12.c ournix.h
	$(CC) $(CFLAGS) -c public12.c

public13.o: public13.c ournix.h
	$(CC) $(CFLAGS) -c public13.c

public14.o: public14.c ournix.h memory-checking.h
	$(CC) $(CFLAGS) -c public14.c

public15.o: public15.c ournix.h memory-checking.h
	$(CC) $(CFLAGS) -c public15.c

clean: 
	- rm *.x ournix.o public01.o public02.o public03.o public04.o public05.o public06.o \
	public07.o public08.o public09.o public10.o public11.o public12.o public13.o public14.o public15.o 


