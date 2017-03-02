#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

	if(argc < 4){
		cout << "Usage : ./MyClient <IP> <port> <N=EndLoop>" << endl;
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
	//End of Loop
	int N = atoi(argv[3]);

	

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
	for(int i=1; i<=N; i++){
		cout << "Sending the message : " << i << " ..." << endl;
		if(sendto(sock, &i, sizeof(i), 0, (struct sockaddr *)&addserv, sizeof(addserv)) < 0){
			perror("sendto failed");
			exit(1);
		}

		cout << "\tMessage sent" << endl;
	}
	

	exit(0);
}
