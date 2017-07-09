CC=gcc
CFLAG=
INC_HOME=
LIB_HOME=

TARGET=thread thread2 thread_with_lock thread_with_cond

all:$(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $<

thread:thread.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

thread2:thread2.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

thread_with_lock:thread_with_lock.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

thread_with_cond:thread_with_cond.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

clean:
	rm -f $(TARGET) *.o
