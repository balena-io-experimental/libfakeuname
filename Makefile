CC ?= gcc
CFLAGS ?= -Wall -fPIC -Os

LIB_LDFLAGS += -shared

SRCS = libfakeuname.c
LIBS = libfakeuname.so

all: ${LIBS}

${LIBS}: ${SRCS} 
	$(CC) $(LIB_LDFLAGS) -o $@ $(CFLAGS) -ldl $< 

