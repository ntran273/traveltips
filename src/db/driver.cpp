#include "db.h"
#include "fbposts.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

// Creates a table if does not exist yet
void initDb(){
	sqlite3* db = DB::getConnection(); // opens a new connection or reused an existing one
	string sql = "CREATE TABLE IF NOT EXISTS FBPOSTS ("
		"ID TEXT PRIMARY KEY NOT NULL,"
		"IMAGESRC TEXT,"
		"IMAGE TEXT,"
		"MESSAGE TEXT);";
  char* err; // store errors when applicable
	sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
  if(err!=NULL)
		cout << err; // display errors when available
		
}

int main(){
	DB::setDbFile("fbPosts.db");
	initDb();
	srand(time(NULL)); // generate random seed using current time
	fbposts test(to_string(rand()), "My post", "myimage", "Hello World"); // create a post with a ranomd id. This is used to ensure that a new ID is used for every post
  test.save(); // saves the post object into the repository.

	vector<fbposts*> posts = fbLoader::getPosts(); // retrive all posts in the database
	fbposts* p = posts.at(0); // retrieve first Post* in the vector
	cout << p->getMessage(); // call the getMessage method of the post pointer
	DB::closeConnection(); // close the db connection
}
