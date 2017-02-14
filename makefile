CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -std=c++11 -Wall $(DEBUG)

sim02 : main.o config.o object.o meta.o metadata.o
	$(CC) $(LFLAGS) main.o config.o object.o meta.o metadata.o -o sim02

PA01.o : config.h meta.h
	$(CC) $(CFLAGS) main.cpp

config.o : config.cpp config.h
	$(CC) $(CFLAGS) config.cpp

object.o : object.cpp object.h
	$(CC) $(CFLAGS) object.cpp

meta.o : meta.cpp meta.h
	$(CC) $(CFLAGS) meta.cpp

metadata.o : metadata.cpp metadata.h
	$(CC) $(CFLAGS) metadata.cpp

clean:
	\rm *.o PA1
