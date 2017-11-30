#ifndef DB_H
#define DB_H

#include <sqlite3.h>
#include <string>

class DB {
  private:
  	static sqlite3* db; // link to existing database
		static std::string dbFile; // database file name
    DB(); // disable the construction of a database object; force the use of getConnection
  public:
    static sqlite3* getConnection(); // create a new or retrieve an existing database connection
		static void closeConnection(); // close the currently open database connection
		static void setDbFile(std::string); // use a specific database file
};

#endif
