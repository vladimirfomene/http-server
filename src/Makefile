CFLAGS =-I.
DEPS = entry.h file.h hashtable.h dllist.h net.h cache.h mime.h threadpool.h
OBJ = server.o file.o hashtable.o dllist.o net.o cache.o mime.o threadpool.o
LIBS = -pthread

.PHONY: clean

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: server

clean: 
	$(RM) *.o
	$(RM) server
