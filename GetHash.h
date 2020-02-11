
#include <iostream>

#include "picosha2.h"

//Gets a hash used for both inserting and querying songs
std::string getHash(std::string stringToHash){
	//Keeps hashed version of the string
	std::string hashValue;
	//Calls SHA 256 from picaish2.h to hash the received value and
	//store it using hashValue variable
	picosha2::hash256_hex_string(stringToHash, hashValue);
	
	return hashValue;
}//End getHash
