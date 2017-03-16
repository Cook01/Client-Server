#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

	if(argc < 3){
		cout << "Usage : ./MyServer <port> <nb octet to read>" << endl;
		exit(1);
	}


	//Socket descriptor
	int sock;

	//Addr Info
	struct sockaddr_in myaddr;
	//Port
	int port = atoi(argv[1]);

	//Nb octet
	int nbOctet = atoi(argv[2]);
	int nbByte = nbOctet*8;
	//Message to recive buffer
	int message;
	//Length of the message recived
	int messageLength;
	//Total to print
	int total = 0;

	//Create the socket
		//AF_INET = IPv4
		//SOCK_DGRAM = Datagram (UDP)
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
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


	do{
		//Reception d'un INT
		cout << "Waiting for a message ..."<< endl;
		messageLength = recvfrom(sock, &message, nbByte, 0, NULL, NULL);
		cout << "\tMessage received : " << messageLength << " bytes" << endl;
		cout << "\t" << message << endl;

		nbByte -= messageLength;
		cout << "\tNb bytes left to read : " << nbByte << endl;

	} while(nbByte > 0);

	exit(0);
}