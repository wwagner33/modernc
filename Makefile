all: wellDoneServer

clean:
	@rm -rf *.o
	@rm -rf wellDoneServer

server: main.o httpd.o
	gcc -o wellDoneServer $^

main.o: main.c httpd.h
	gcc -c -o main.o main.c

httpd.o: httpd.c httpd.h
	gcc -c -o httpd.o httpd.c