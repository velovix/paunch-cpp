CC=g++
CFLAGS=-Wall -std=c++11 -c
OBJS= error.o draw.o renderable.o effect.o lodepng.o point.o bounding.o line.o polygon.o collision.o physics.o actor-manager.o window.o audio.o sound.o

all: $(OBJS)
	ar crf libpaunch.a $(OBJS)

error.o: error.cpp
	$(CC) $(CFLAGS) error.cpp

draw.o: draw.cpp
	$(CC) $(CFLAGS) draw.cpp

renderable.o: renderable.cpp
	$(CC) $(CFLAGS) renderable.cpp

effect.o: effect.cpp
	$(CC) $(CFLAGS) effect.cpp

lodepng.o: lodepng.cpp lodepng.h
	$(CC) $(CFLAGS) lodepng.cpp

point.o: point.cpp
	$(CC) $(CFLAGS) point.cpp

bounding.o: bounding.cpp
	$(CC) $(CFLAGS) bounding.cpp

line.o: line.cpp
	$(CC) $(CFLAGS) line.cpp

polygon.o: polygon.cpp
	$(CC) $(CFLAGS) polygon.cpp

physics.o: physics.cpp
	$(CC) $(CFLAGS) physics.cpp

collision.o: collision.cpp
	$(CC) $(CFLAGS) collision.cpp

actor-manager.o: actor-manager.cpp
	$(CC) $(CFLAGS) actor-manager.cpp

window.o: window.cpp
	$(CC) $(CFLAGS) window.cpp

audio.o: audio.cpp
	$(CC) $(CFLAGS) audio.cpp

sound.o: sound.cpp
	$(CC) $(CFLAGS) -w sound.cpp

clean:
	rm *.o
