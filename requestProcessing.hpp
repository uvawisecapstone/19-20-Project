#ifndef REQUEST_PROCESSING_HPP
#define REQUEST_PROCESSING_HPP

//#include <string>

#include <stdlib.h>
#include <time.h>

std::string processRequest(std::string out_message){
	
	std::string stringMessageID = "";
	
	for(int i=0;i<3;i++){
		stringMessageID += out_message[i];
	}
	
	int messageID = stoi(stringMessageID);
	int escapeCharacterLocation = 0;
	
	
	
	switch(messageID){
		
		//generate account
		case 1: {
			std::string username = "";;
			std::string password = "";
			
			
			escapeCharacterLocation = out_message.find("~");
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				username += out_message[i];
			}
			for(int i = escapeCharacterLocation+1; i < out_message.length(); i++){
				password += out_message[i];
			}
			
			//debug line, respond with "success"
			out_message = username + " " + password;
			
			srand(time(NULL));
			int verificationPin = rand() % 10000 + 1;
			
			
			//SQL statement to put user into table
		
			//Send verification email
			
			std::string osCall = "python3 verifyEmail.py " + username + " " + verificationPin;
			
			//make OS call python3 verifyEmail.py <username> <verificationPin>
			
			break;
		};
		//set verification status
		case 2: {
			
			std::string verificationNumber = ""
			std::string verificationEmail = ""
			escapeCharacterLocation = out_message.find("~");
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				verificationNumber += out_message[i];
			}
			for(int i = escapeCharacterLocation + 1; i < out_message.length(); i++){
				verificationEmail += out_message[i]
			}
			
			
			//compare verification number to one on file for that email
			//If true, update database to show verified = 1
			
			
			break;
		}
		
		//check login
		case 3: {
			std::string username = "";;
			std::string password = "";
			
			
			escapeCharacterLocation = out_message.find("~");
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				username += out_message[i];
			}
			for(int i = escapeCharacterLocation+1; i < out_message.length(); i++){
				password += out_message[i];
			}
			
			//check SQL database for username, password, and verification status
			//If verified, proceed. Otherwise, send back "verification failure"
			//If correct, send back "success"
			//otherwise, send back "failure"
			
			
		}
		//get path file
		case 4: {

			//sample syntax: 004asfsans~80~1~2

			std::string songID = "";
			std::string branchSimilarity = "";
			std::string longBranchesOnly = "";
			std::string minimumDistance = "";
			escapeCharacterLocation = out_message.find("~");
			escapeCharacterLocation2 = out_message.find("~",escapeCharacterLocation+1);
			escapeCharacterLocation3 = out_message.find("~",escapeCharacterLocation2+1);
			
			for(int i=3; i < escapeCharacterLocation; i++){
				songID += out_message[i];
			}	
			
			for(int i=escapeCharacterLocation+1;i<escapeCharacterLocation2; i++){
				branchSimilarity += out_message[i];
			}
			for(int i=escapeCharacterLocation2+1;i<escapeCharacterLocation3; i++){
				longBranchesOnly += out_message[i];
			}
			for(int i=escapeCharacterLocation3+1;i<out_message.length(); i++){
				minimumDistance += out_message[i];
			}
			
			
			//make os call to this:
			
			//python3 main.py <branchSimilarity> <longBranchesOnly> <minimumDistance> <songID>
			
			//make SQL request to get path from database using songID
			
			//return songID
			
		
			
			
			
			
			
		}
		
		
		
	}

return out_message;

}
#endif
