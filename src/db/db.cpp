#include "db.h"

// Initialize values of static variables
std::string DB::dbFile = "db.db";
sqlite3* DB::db = NULL;

sqlite3* DB::getConnection(){
	if(!db){
		sqlite3_open(DB::dbFile.c_str(), &DB::db);
	}
	
	return DB::db;
}

void DB::closeConnection(){
	if(!db)
		sqlite3_close(db);
}

void DB::setDbFile(std::string dbFile){
	DB::dbFile = dbFile;
}
