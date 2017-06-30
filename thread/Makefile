CC=gcc
CFLAG=
INC_HOME=
LIB_HOME=

TARGET=thread thread2

all:$(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $<

thread:thread.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

thread2:thread2.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

clean:
	rm -f $(TARGET) *.o
