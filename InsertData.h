
#include <iostream>

#include <sqlite3.h>

//Funciton for inserting data into the UserData table
void insertUserData(std::string username, std::string password, 
					std::string email, std::string lastRequest){

	//Insert statement for UserData table
	std::string userData = "INSERT INTO UserData VALUES (";
	
	//Takes input to be inserted into UserData table
	std::cout << "Enter Username and password:\n";
	std::cin >> username;
	std::cin >> password;
	
	email = username + "'@website.com'";
	lastRequest = "'September 12, 2019'";
	
}//End insertUserData

//Function for inserting data into the SongData table
std::string insertSongData(std::string songId, std::string pathFile){
	//Insert statement for SongData table
	std::string songData = "INSERT INTO SongData (SongID, PathFile) VALUES (";
	
	songId = "'" + songId + "'";
	pathFile = "'" + pathFile + "'";
	
	//Updates songData's insertion with the values to be inserted
	songData = songData + songId + "," + pathFile + ");";
	
	return songData;
}//End insertSongData
