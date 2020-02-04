#include <iostream> //handles debug input/output

#include <sys/types.h> //needed for creating sockets

#include <sys/socket.h> //needed for creating sockets

#include <unistd.h> //defines miscellaneous constants and types

#include <netdb.h> //Allows for network database operations

#include <arpa/inet.h> //Allows for internet operations

#include <string.h> //Allows for easier manipulation of character arrays

const int PORT = 21600;	//PORT number for network

int main()
{
/*The following block of code was taken from Sloan Kelly
It has been modified to fit the needs of this project
Link to code: https://gist.github.com/codehoose/020c6213f481aee76ea9b09
6acaddfaf
*/
//Begin code block
	//initialize the socket
    int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listeningSocket == -1){
		std::cerr << "Unable to create a socket...server shutting down." 
														<< std::endl;
	}
    
    //bind the socket to an IP address and PORT number
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    
    if(bind(listeningSocket, (sockaddr*)&hint, sizeof(hint)) == -1){
		std::cerr << "Unable to bind to the IP address or port number." 
														<< std::endl;
	}
    
	//listen for connections
	if(listen(listeningSocket, SOMAXCONN) == -1){
		std::cerr << "Unable to listen for connections." << std::endl;
	}
    
	std::cout << "Listening on port: " << PORT << std::endl;
    
	//accept clients
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];		//Client's remote name
	char service[NI_MAXSERV];	//Port the client is listening on
	
	int clientSocket = accept(listeningSocket, (sockaddr*)&client,
														&clientSize);
	if(clientSocket == -1) 
	{
		std::cerr << "Unable to connect the client" << std::endl;
	}
														
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	
	if(getnameinfo((sockaddr*)&client, sizeof(client), host, 
							NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
		std::cout << host << " connected on port: " << service << 
											std::endl << std::endl;
	}
	else{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port:" << 
												ntohs(client.sin_port) 
		<< std::endl << std::endl;
	}
	
	close(listeningSocket);
	
	char buffer[4096];
	
	//Accepts and echos a message back to the client
	while(true)
	{
		memset(buffer, 0, 4096);
		
		//Wait for the client to send data
		int bytesReceived = recv(clientSocket, buffer, 4096, 0);
		if(bytesReceived == -1)
		{
			std::cerr << "Error receiving data." << std::endl;
			break;
		}
		
		if(bytesReceived == 0)
		{
			std::cout << "Client disconnected." << std::endl;
			break;
		}
		
		//Prints the message sent by the client
		std::cout << std::string(buffer, 0, bytesReceived) << std::endl;
		
		//Echo message back to the client
		//This is to show that the client and server are communicating
		send(clientSocket, buffer, bytesReceived + 1, 0);
		
	}
	
	close(clientSocket);

    return 0;
}
//end code block
