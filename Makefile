CC = g++
CFLAGS = -g -Wshadow -std=c++11

all: master slave

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

master: master.o
	$(CC) $(CFLAGS) -o $@ $^

slave: slave.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -f *.o