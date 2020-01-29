
#include <iostream> //handles debug input/output

//#include <sys/types.h>

//#include <sys/socket.h>

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
	//initialize the socket
    int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    //bind the socket to an IP address and PORT number
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(listeningSocket, (sockaddr*)&hint, sizeof(hint));
    
    listen(listeningSocket, SOMAXCONN);
    
    std::cout << "Listening on port: " << PORT << std::endl;
    
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
	
	std::cout << result << std::endl;
													
	if(result){	
		std::cout << host << " connected on " << service << std::endl;
	}
	else{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << "connected on " << ntohs(client.sin_port) 
		<< std::endl;
	}
    return 0;
}
