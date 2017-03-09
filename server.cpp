#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

	if(argc < 2){
		cout << "Usage : ./MyServer <port>" << endl;
		exit(1);
	}


	//Socket descriptor
	int sock;

	//Addr Info
	struct sockaddr_in myaddr;
	//Port
	int port = atoi(argv[1]);

	//Message to recive buffer
	int message;
	//Length of the message recived
	int messageLength;
	//Total to print
	int total = 0;

	//Create the socket
		//AF_INET = IPv4
		//SOCK_DGRAM = Datagram (UDP)
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket");
		exit(1);
	}
	cout << "Created socket : descriptor = " << sock << endl;


	//Define the network representation
		//AF_INET = IPv4
		//htonl = int to addr -- (ntohl = addr to int)
		//htons = int to port -- (ntohs = port to int)
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port);


	//Naming the socket
	if(bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){
		perror("cannot bind socket");
		exit(1);
	}
	cout << "Socket binded" << endl;


	while(true){
		//Waiting for an INT
		cout << "Waiting for a message ..."<< endl;
		messageLength = recvfrom(sock, &message, sizeof(int), 0, NULL, NULL);

		//Printing message datas
		cout << "\tMessage received : " << messageLength << " bytes" << endl;
		cout << "\tMessage : " << message << endl;
		
		total += message;
		cout << "\tNew total : " << total << endl;;
	}

	exit(0);
}
