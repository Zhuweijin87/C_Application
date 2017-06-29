CC=gcc
CFLAG=
INC_HOME=
LIB_HOME=

RM=rm -f 

TARGET=simpleserver

all:$(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $<

simpleserver:simple_server.o
	$(CC) $(CFLAG) -o $@ $?

clean:
	$(RM) $(TARGET) *.o


