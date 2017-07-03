CC=gcc
CFLAG=
INC_HOME=
LIB_HOME=

RM=rm -f 

TARGET=simpleServer simpleClient GetHostInfo selectServer ServerWithMultiThread \
		ServerMultiProcess

all:$(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $<

simpleServer:simple_server.o
	$(CC) $(CFLAG) -o $@ $?

simpleClient:simple_client.o
	$(CC) $(CFLAG) -o $@ $?

selectServer:select_server.o
	$(CC) $(CFLAG) -o $@ $?

GetHostInfo:gethostinfo.o
	$(CC) $(CFLAG) -o $@ $?

ServerWithMultiThread:server_with_multithread.o
	$(CC) $(CFLAG) -o $@ $? -lpthread

ServerMultiProcess:server_with_multiprocess.o
	$(CC) $(CFLAG) -o $@ $?

clean:
	$(RM) $(TARGET) *.o


