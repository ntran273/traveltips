/*Copyright 2017 Paul Salvador Inventado

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

#ifndef OAUTH2_H
#define OAUTH2_H

#include <webkit2/webkit2.h>
#include <gtkmm.h>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>  
#include <iostream>
#include <exception>

using namespace web; 
using namespace web::http;
using namespace web::http::client; 

class Authorized {
	public:
		virtual void authorize(std::string, std::string) = 0;
};

class OAuth2 {
  private:
		std::string loginEndpoint;
		std::string successParam;
		WebKitWebView* page;
		Authorized* client;
		static void pageLoaded(WebKitWebView*, WebKitLoadEvent, gpointer);
		Glib::RefPtr<Gtk::Application> app;
		Gtk::Window* loginWindow;
		Gtk::Widget* pageContainer;
	public:
		OAuth2(std::string, std::string);	
		std::string getLoginEndpoint(){ return loginEndpoint; }
		std::string getSuccessParam(){ return successParam; }
		void init(Authorized*, Glib::ustring);
		void filterReply(std::string);
		static void temp(std::string x, std::string y){}
};

/*class FbManager {
	private:
		std::string apiVersion;
		std::string accessToken;
	public:
		FbManager();
		void login(std::string, std::string);
		static void loginSuccess();
		std::string getAccessToken();
};

/*class UnavailableAccessTokenException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Access token has not yet been retrieved. Make sure you call the login function first.";
  }
};

FBManager::FbManager(){
	apiVersion = "v2.10";
}

void FbManager::loginSuccess(std::string param, std::string value){
	accessToken = value;
}

std::string FbManager::getAccessToken(){
	if(accessToken.empty())
		throw UnavailableAccessTokenException();
	else
		return accessToken;
}

void FbManager::login(std::string clientId, std::string scope){
	uri_builder login("https://www.facebook.com/" + apiVersion + "/dialog/oauth");
	login.append_query("client_id", clientId);
	login.append_query("response_type", "token");
	login.append_query("scope", scope);
	login.append_query("redirect_uri", "https://www.facebook.com/connect/login_success.html");

	OAuth2 auth(login.to_string(), "access_token");
	//auth.setCallback(FbManager::loginSuccess);
	auth.init();
}*/
#endif
