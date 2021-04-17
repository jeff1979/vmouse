CC=gcc

#TARGET  := <<your executable name>> 
TARGET  := uinput_test 

#SRCS    := <<one ore more of your .c files>> 
SRCS    := uinput_test.c\

OBJS    := ${SRCS:.c=.o} 
DEPS    := ${SRCS:.c=.dep} 
XDEPS   := $(wildcard ${DEPS}) 

#for gcc
CCFLAGS = -O2 -Wall -g -l ./include

#for ld link library and path
LDFLAGS = -L. 
LIBS    = -lrt

#generic should not be change
.PHONY: all clean distclean 
all:: ${TARGET} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.c %.dep 
	${CC} ${CCFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.c Makefile 
	${CC} ${CCFLAGS} -MM $< > $@ 

clean:: 
	-rm -f *~ *.o ${TARGET} 

distclean:: clean
