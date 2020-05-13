CC = gcc
CFLAGS = -Wall -I include/
TARGET = exe
SRC := $(wildcard src/*.c)

all: compile

compile:
	${CC} ${CFLAGS} -o ${TARGET} ${SRC}
