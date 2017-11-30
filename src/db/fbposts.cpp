#include "fbposts.h"
#include "db.h"
#include <iostream>
#include <vector>
using namespace std;

//fbposts object constructor
fbposts::fbposts(string id, string imageSrc, string image, string message){
	this->id = id;
	this->imageSrc = imageSrc;
	this->image = image;
	this->message = message;
	this->remembered = false;
}

//Getter and Setter

string fbposts::getId(){ return id; }

void fbposts::setId(string id){ this->id = id; }

bool fbposts::isRemembered(){ return remembered; }

void fbposts::setRemembered(bool remembered){ this->remembered = remembered; }

string fbposts::getImage(){ return image; }		

void fbposts::setImage(string image){ this-> image = image; }

string fbposts::getImageSrc(){ return imageSrc; }

void fbposts::setImageSrc(string imageSrc) { this->imageSrc = imageSrc; }

string fbposts::getMessage(){ return message; }

void fbposts::setMessage(string message){ this->message = message; }

//Save fbposts into the DB

void fbposts::save(){
	sqlite3* db = DB::getConnection();
	std::string sql = "INSERT INTO POSTS (ID, IMAGESRC, IMAGE, MESSAGE)"
	 "VALUES(\"" + id + "\", \"" + imageSrc + "\", \"" + image + "\", \"" + message + "\");";
	char* err;
  sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
  if(err!=NULL)
		std::cout << err << std::endl << std::flush;
}

void fbposts::remove(){
	sqlite3* db = DB::getConnection();
	std::string sql = "DELETE FROM POSTS WHERE ID = \"" + id + "\";";
	char* err;
  sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
  if(err!=NULL)
		std::cout << err << std::endl << std::flush;
}

// callback function to build the vector of fbposts
int fbLoader::callback(void *data, int numResults, char **values, char **colNames){
 	 vector<fbposts*>* posts = (vector<fbposts*>*) data;
  	fbposts* p = new fbposts(values[0], values[1], values[2], values[3]);
	p->setRemembered(true);
  	(*posts).push_back(p);
  return 0;
}

// retrieve fbposts from the database
vector<fbposts*> fbLoader::getPosts(){
	vector<fbposts*>* posts = new vector<fbposts*>;
	sqlite3* db = DB::getConnection();
	string sql = "SELECT ID, IMAGESRC, IMAGE, MESSAGE FROM POSTS";
	char* err;
	sqlite3_exec(db, sql.c_str(), fbLoader::callback, posts, &err);
	if(err!=NULL)
		cout << err << endl << flush;
  return *posts;
}
