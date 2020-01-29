#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

int main()
{
//The following block of code was taken from Sloan Kelly
//It has been modified to fit the needs of this project
//Link to code: https://gist.github.com/codehoose/
//                                		020c6213f481aee76ea9b096acaddfaf
//**********************************************************************
	int port = 61001;	//port number for network
	
	//initialize the socket
    int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    //bind the socket to an IP address and port number
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(listeningSocket, (sockaddr*)&hint, sizeof(hint));
    
    listen(listeningSocket, SOMAXCONN);
    
    //accept clients
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	
	accept(listeningSocket, (sockaddr*)&client, &clientSize);
														
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	
	int result = getnameinfo((sockaddr*)&client, sizeof(client), host,
									NI_MAXHOST, service, NI_MAXSERV, 0);
	
	cout << result << endl;
								
	if(result){	
		cout << host << " connected on " << service << endl;
	}
	else{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on " << ntohs(client.sin_port) << endl;
	}
//**********************************************************************
    return 0;
}
