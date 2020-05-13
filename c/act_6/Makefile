CC = gcc
CFLAGS = -Wall -I include/
TARGET = exe
TEST = u_test
SRC := $(wildcard src/*.c)

.PHONY: compile unit_test

all: compile

compile:
	@${CC} ${CFLAGS} -o ${TARGET} ${SRC}

unit_test:
	@${CC} ${CFLAGS} -o ${TEST} ${subst src/main.c, test.c, ${SRC}}
