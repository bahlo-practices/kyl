# Variables
CC=g++
CFLAGS=-Wall
LDFLAGS=
SOURCES=
MAIN=algo.cpp
EXECUTABLE=algo.o

# Tasks
all:
	${CC} ${CFLAGS} -o ${EXECUTABLE} ${MAIN} ${SOURCES}

run: all
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
