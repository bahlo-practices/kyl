# Variables
CC=g++
CFLAGS=-Wall
LDFLAGS=
SOURCES=
MAIN=main.cpp
EXECUTABLE=practice2.o

# Tasks
all:
	${CC} ${CFLAGS} -o ${EXECUTABLE} ${MAIN} ${SOURCES}

run: all
	./${EXECUTABLE}

clean:
	rm `find . -name "*o"`
