
CC = gcc
CPPFLAGS = -lm -ggdb3 -g -fcompare-debug-second

foo: make-objs
	${CC} *.o -o ./foo ${CPPFLAGS}

make-objs: 
	${CC} -c ./src/*.c ${CPPFLAGS}

.PHONY: clean

clean:
	find . -name "*.o" -delete