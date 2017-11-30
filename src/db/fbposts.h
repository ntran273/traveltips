/*Copyright 2017 Xuan Do
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef FBPOSTS_H
#define FBPOSTS_H
#include <string>
#include <vector>
#include <sqlite3.h>
using namespace std;


class fbposts {
	private:
		string id;
		bool remembered;
		string imageSrc;
		string image;
		string message;

	public:
		fbposts(string, string, string, string);
		string getId();
		void setId(string);
		bool isRemembered();
		void setRemembered(bool);
		string getImage();	
		void setImage(string);
		string getImageSrc();	
		void setImageSrc(string);
		string getMessage();
		void setMessage(string);
		void save();
		void remove();

};

class fbLoader {
	private:
		static int callback(void*, int , char**, char**); // callback function to build the vector of posts
  	public:		
		static vector<fbposts*> getPosts();
};

#endif
