CFLAGS   ?= -DMAIN -Wall
CXXFLAGS ?= -Wall -std=c++11

# Programs to build
PROGS = extract le pack

all: $(PROGS)

extract: extract.c extract.h
	$(CC) $(CFLAGS) -o $@ extract.c

le: le.c
	$(CC) $(CFLAGS) -o $@ le.c

pack: pack.c
	$(CC) $(CFLAGS) -o $@ pack.c

clean:
	rm -f $(PROGS) *.o
