CC = g++

all :
	$(CC) server.cpp -o server
	$(CC) client.cpp -o client