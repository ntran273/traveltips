#ifndef FBAPI_H
#define FBAPI_H

#include "oauth2.h"
#include <cpprest/http_client.h>
#include <cpprest/uri.h>  
#include <iostream>
#include <exception>
#include <regex> 
#include <vector>
#include "../db/fbposts.h"

using namespace web; 
using namespace web::http;
using namespace web::http::client; 

class UnavailableAccessTokenException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Access token has not yet been retrieved. Make sure you call the login function first.";
  }
};

class ConnectionListener{
  public:
		virtual void loginSuccess() = 0;
};

class FbManager: public Authorized { // a class that implements the Authorized class
	private:
		std::string apiVersion; // Facebook API version
		std::string accessToken; // Storage for access token retrieved after login
		std::string clientId; // Currently used Facebook client ID
		std::string scope; // Currently used Facebook scope
		std::string clean_json(std::string); // removes unicode sequence from json string
		std::vector<ConnectionListener*> connectionListeners;
		OAuth2* auth;
	public:
		FbManager(std::string, std::string); // create FbManager using specified client ID and scope
		void login(Glib::ustring); // initiate FB login
		std::string getAccessToken(); // retrieve access token
		void authorize(std::string, std::string); // implementation of virtual method declared in the Authorized class
		std::vector<fbposts*> getPosts(); // retrieves posts from the /me/feed endpoint; will be replacing with a vector of posts in next version
		void addConnectionListener(ConnectionListener*);
};

class FB {
  private:
		static std::string clientId; // clientId used for the FBManager
		static std::string scope; // scope used for the FBManager
  	static FbManager* fbManager; // link to existing Facebook manager
    FB(); // disable the construction of a Facebook manager; force the use of getManager
  public:
		static void configure(std::string, std::string); // set client ID and scope
    static FbManager* getManager(); // create a new or retrieve an existing Facebook manager
};

#endif
