CC = gcc
CFLAGS = -lpthread

OBJS1 = synch_pthread.o
OBJS2 = synch_semaphore.o
SRCS = $(OBJS1: .o=.c) $(OBJS2: .o=.c)

TARGET: synch_pthread synch_semaphore

all: $(TARGET)

synch_pthread : $(OBJS1)
		$(CC) -o synch_pthread $(OBJS1) $(CFLAGS)
synch_semaphore : $(OBJS2)
		$(CC) -o synch_semaphore $(OBJS2) $(CFLAGS)

dep :
		gccmakedep $(SRCS)

clean :
	-rm -f $(OBJS1) $(OBJS2) $(TARGET)

rebuild: clean all


