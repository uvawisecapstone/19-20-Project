#include <iostream>

#include <sqlite3.h>

//Callback is used by the sqlite3_exec function
int callback(void *None, int count, char **data, char **column){
	int i;
	for(i = 0; i < count; i++){
		printf("%s\n\n",data[i]);
	}//End for
	
	return 0;
}//End callback

//Builds the query for the pathFile
std::string queryData(std::string dataSelection){
	//dataSelection takes the SongID and uses it to query for 
	//the path value that matches the ID
	
	//Holds SELECT statement
	std::string sqlQuery = "";
	
	//Places quotations around dataSelection. Query will not work 
	//without this statement
	dataSelection = "'" + dataSelection + "'";
	
	//Adds information for what is being queried
	sqlQuery = "SELECT PathFile FROM SongData WHERE SongID =" + dataSelection; 
	
	return sqlQuery;
}//End queryData
