#include <iostream>

#include <sqlite3.h>

#include <fstream>

#include "InsertData.h"

#include "QueryData.h"

#include "GetHash.h"

int databaseHandler()
{
	//Points to SQLite connection
	sqlite3 *db; 
	
	//Variables needed to open and get contents of the music file
	std::ifstream musicFile;
	std::string fileData = ""; //Holds data that is read from the file
	std::string iterate = ""; //Iterates through the open file
	int count = 0;
	
	//Variables to be passed to insertSongData function
	std::string getSongId = "";
	std::string getPathFile = "";
	
	//Variables to be passed to unsertUserData function
	std::string getUsername = "";
	std::string getPassword = "";
	std::string getEmail = "";
	std::string getLastRequest = ""; //Holds date user's last song request
	
	//Holds the connection to the specified database
	int openConnection = sqlite3_open("CapstoneDatabase.db", &db);
	
	//INSERT statement
	std::string insert = "";
	//SELECT statement
	std::string query = "";
	
	//Check the conneciton to the database
	if(openConnection == SQLITE_OK){
		
		do{
			std::cout << "Search for a song:" << std::endl;
			getline(std::cin, getSongId);//Takes input for the song file name
			
			getSongId = getSongId + ".mp3";//Adds necessary file extension to search
			musicFile.open(getSongId);//Opens the file using given songId
		}while(!musicFile);
		
		//Iterates throught the file and gets the first 50 lines
		//Creates a single string from all 50 lines
		while(count < 50){ 
			musicFile >> iterate;
			fileData = fileData + iterate;
			count++;
		}//End while
		
		//Gets the hashed version of fileData
		fileData = getHash(fileData);
		
		//Gets the SELECT statement to query the database for the songId
		query = queryData(fileData);
		//Executes the SQL SELECT statement
		std::cout << sqlite3_exec(db, query.c_str(), callback, 0, 0) << std::endl;
		
		//Gets the INSERT statement to insert songId and pathFile
		//into the database
		insert = insertSongData(fileData, getSongId);
		//Executes the SQL INSERT statement
		sqlite3_exec(db, insert.c_str(), 0, 0, 0);
		//Statement for testing purposes. Lets me know when something 
		//has been inserted into the database	
		std::cout << "It has been put in the database" << std::endl;
		sqlite3_exec(db, query.c_str(), callback, 0, 0);
			
		
	}//end if
	else{
		
		std::cout << "Unable to connect to database\n";
		
	}//end else
	
	musicFile.close();
	sqlite3_close(db);//Closes the connection to the database
	
	return 0;
}
