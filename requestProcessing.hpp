#ifndef REQUEST_PROCESSING_HPP
#define REQUEST_PROCESSING_HPP

#include <string>

#include <stdlib.h>
#include <time.h>

std::string processRequest(std::string out_message){
	
	std::string stringMessageID = "";
	
	for(int i=0;i<3;i++){
		stringMessageID += out_message[i];
	}
	
	int messageID = stoi(stringMessageID);
	int escapeCharacterLocation = 0;
	
	int messageLength = out_message.length();
	
	switch(messageID){
		
		//generate account
		case 1: {
			std::string username = "";
			std::string password = "";
			
			
			escapeCharacterLocation = out_message.find("~");
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				username += out_message[i];
			}
			for(int i = escapeCharacterLocation+1; i < messageLength; i++){
				password += out_message[i];
			}
			
			//debug line, respond with "success"
			out_message = username + " " + password;
			
			srand(time(NULL));
			int verificationPin = rand() % 10000 + 1;
			
			//generate 64-character salt string
			
			//hash password+salt
			
			//SQL statement to put user data into table
		
			//Send verification email
			
			std::string osCall = "python3 verifyEmail.py " + username + " " + std::to_string(verificationPin);
			
			//make OS call python3 verifyEmail.py <username> <verificationPin>
			
			break;
		};
		//set verification status
		case 2: {
			
			std::string verificationNumber = "";
			std::string verificationEmail = "";
			escapeCharacterLocation = out_message.find("~");
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				verificationNumber += out_message[i];
			}
			for(int i = escapeCharacterLocation + 1; i < messageLength; i++){
				verificationEmail += out_message[i];
			}
			
			
			//compare verification number to one on file for that email
			//If true, update database to show verified = 1
			
			
			break;
		}
		
		//change verification status
		case 3: {
			
			//example 003username~password~1234
			
			std::string username = "";
			std::string password = "";
			std::string verificationPin = "";
			
			
			//sql query to get the salt of the username
			
			
			escapeCharacterLocation = out_message.find("~");
			int escapeCharacterLocation2 = out_message.find("~", escapeCharacterLocation);
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				username += out_message[i];
			}
			for(int i = escapeCharacterLocation+1; i < escapeCharacterLocation2; i++){
				password += out_message[i];
			}
			for(int i = escapeCharacterLocation2+1; i < messageLength; i++){
				password += out_message[i];
			}
			
			
			//check SQL database for username, password, verification pin
			//if login successful, proceed
			
			//change verification status to 1.
			
			
		}
		
		
		//check login
		case 4: {
			//example syntax: 004username~password
			
			
			std::string username = "";
			std::string password = "";
			
			
			//sql query to get the salt of the username
			
			
			escapeCharacterLocation = out_message.find("~");
			
			for(int i = 3; i < escapeCharacterLocation; i++){
				username += out_message[i];
			}
			for(int i = escapeCharacterLocation+1; i < messageLength; i++){
				password += out_message[i];
			}
			
			
			//check SQL database for username, password, and verification status
			
			//If verified, proceed. Otherwise, send back "verification failure"
			
			//to check for password, run hash(password+salt)
			
			
			
			//If correct, send back "success"
			//otherwise, send back "failure"
			
			
		}
		//get path file
		case 5: {

			//sample syntax: 005asfsans~80~1~2~email~password

			std::string songID = "";
			std::string branchSimilarity = "";
			std::string longBranchesOnly = "";
			std::string minimumDistance = "";
			std::string username = "";
			std::string password = "";
			escapeCharacterLocation = out_message.find("~");
			int escapeCharacterLocation2 = out_message.find("~",escapeCharacterLocation+1);
			int escapeCharacterLocation3 = out_message.find("~",escapeCharacterLocation2+1);
			int escapeCharacterLocation4 = out_message.find("~",escapeCharacterLocation3+1);
			int escapeCharacterLocation5 = out_message.find("~",escapeCharacterLocation4+1);
			
			for(int i=3; i < escapeCharacterLocation; i++){
				songID += out_message[i];
			}	
			
			for(int i=escapeCharacterLocation+1;i<escapeCharacterLocation2; i++){
				branchSimilarity += out_message[i];
			}
			for(int i=escapeCharacterLocation2+1;i<escapeCharacterLocation3; i++){
				longBranchesOnly += out_message[i];
			}
			for(int i=escapeCharacterLocation3+1;i<messageLength; i++){
				minimumDistance += out_message[i];
			}
			for(int i=escapeCharacterLocation4+1;i<messageLength; i++){
				username += out_message[i];
			}
			for(int i=escapeCharacterLocation5+1;i<messageLength; i++){
				password += out_message[i];
			}
			
			//get salt for username
			
			
			//check username & password+salt
			//if verified, continue
				
				//make os call to this:
				
				//python3 main.py <branchSimilarity> <longBranchesOnly> <minimumDistance> <songID>
				
				//make SQL request to get path from database using songID
				
				//set out_message equal to path file
			
	
			//otherwise, out_message = "authentication error"
			
			
		}
		
		
		
	}

return out_message;

}
#endif
