# Garrett Scholtes
#
# ***NOTE***
# If you have trouble compiling on a 64 bit machine, you may first 
# need to install the 32 bit development libraries.  Perhaps: 
#
#     sudo apt install libc6-dev-i386
# 
CC=gcc
CFLAGS=-m32 -g -fno-stack-protector

default:
	$(CC) $(CFLAGS) -o lab3ex lab3ex.c
	echo "Secret file!" > root-only-file
	sudo chown root:root root-only-file
	sudo chmod 600 root-only-file

clean:
	rm -f lab3ex root-only-file
