#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

	if(argc < 3){
		cout << "Usage : ./MyClient <IP> <port>" << endl;
		exit(1);
	}

	//Socket descriptor
	int sock;

	//Addr Infos
	struct sockaddr_in addserv;

	//Server IP
	const char* ip = argv[1];
	//Server port
	int port = atoi(argv[2]);

	//Message to send
	int message = 0;

	

	//Create the socket
		//AF_INET = IPv4
		//SOCK_DGRAM = Datagram (UDP)
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket");
		exit(1);
	}
	cout << "Created socket: descriptor = " << sock << endl;


	//define the network representation
		//AF_INET = IPv4
		//htonl = int to addr -- (ntohl = addr to int)
		//htons = int to port -- (ntohs = port to int)
	memset((char *)&addserv, 0, sizeof(addserv));
	addserv.sin_family = AF_INET;
	addserv.sin_port = htons(port);

	//Set the IP
	inet_pton(AF_INET, ip, &(addserv.sin_addr));

	//Send the int message
	cout << "Message n°1 to send : ";
	cin >> message;
	cout << endl;
	cout << "\tSending the message : " << message << " ..." << endl;
	if(sendto(sock, &message, sizeof(message), 0, (struct sockaddr *)&addserv, sizeof(addserv)) < 0){
		perror("sendto failed");
		exit(1);
	}
	cout << "\tMessage sent" << endl;

	cout << "Message n°2 to send : ";
	cin >> message;
	cout << "\tSending the message : " << message << " ..." << endl;
	if(sendto(sock, &message, sizeof(message), 0, (struct sockaddr *)&addserv, sizeof(addserv)) < 0){
		perror("sendto failed");
		exit(1);
	}
	cout << "\tMessage sent" << endl;

	exit(0);
}
