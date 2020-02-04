/*The following block of code was taken from Sloan Kelly
It has been modified to fit the needs of this project
Link to code: 
https://gist.github.com/codehoose/d7dea7010d041d52fb0f59cbe3826036
*/

//Begin code block
#include <iostream>	//handles debug input/output

#include <sys/types.h>	//needed for creating sockets

#include <unistd.h>	//defines miscellaneous constants and types

#include <sys/socket.h>	//needed for creating sockets

#include <netdb.h>	//Allows for network database operations

#include <arpa/inet.h>	//Allows for internet operations

#include <string.h>	//Allows for easier manipulation of character arrays

const int PORT = 21600; // Listening port # on the server

const std::string ipAddress = "0.0.0.0";   // IP Address of the server 

int main()
{                 
      
   // Create dSocket
   int dSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (dSocket == -1)
   {
      std::cerr << "Can't create a socket" << std::endl;
   }
   
   // Fill in a hint structure
   
   sockaddr_in hint;
   hint.sin_family = AF_INET;
   hint.sin_port = htons(PORT);
   inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
   
   // Connect to a server
   
   int connResult = connect(dSocket, (sockaddr*)&hint, sizeof(hint));
   if (connResult == -1)
   {
      std::cerr << " Can't connect to server." << std::endl;
   }
   
   // Do-while loop to send and receive data
   
   char buffer[4096];
   std::string userInput;
   
   do
   {
      // Prompt the user for text
      
      std::cout << "> ";
      std::getline(std::cin, userInput);

      // Send the text
      
      int sendResult = send(dSocket, userInput.c_str(), userInput.size()
																+ 1, 0);
      if (sendResult == -1)
      {
		 std::cerr << "Could not send message to the server" << 
															std::endl;
      }
      
      // Wait for Response
         
	  memset(buffer, 0, 4096);
      int bytesReceived = recv(dSocket, buffer, 4096, 0);
      if (bytesReceived == -1)
      {
		 std::cout << "There was no response from the server" << 
															std::endl;
      }
      else
      {
         std::cout << "SERVER> " << std::string(buffer, bytesReceived) 
														<< std::endl;   
	  }
     
   } while (true);
   
    close(dSocket);
    
    return 0;
}
//End code block
