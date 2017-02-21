CC=gcc
CFLAGS=-m32 -g -fno-stack-protector

default:
	$(CC) $(CFLAGS) -o lab3ex lab3ex.c

clean:
	rm -f lab3ex
