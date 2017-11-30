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

#include "oauth2.h"
#include <iostream>
#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include <regex>
#include <string>

OAuth2::OAuth2(std::string loginEndpoint, std::string successParam){
	this->loginEndpoint = loginEndpoint;
	this->successParam = successParam;
}

void OAuth2::pageLoaded(WebKitWebView  *web_view, WebKitLoadEvent load_event, gpointer user_data){
	if(load_event == WEBKIT_LOAD_FINISHED){
		OAuth2* authobj = (OAuth2*)user_data;
		authobj->filterReply(webkit_web_view_get_uri(web_view));
	}
}

void OAuth2::filterReply(std::string reply){
	std::regex tokensearch(".*" + successParam + "=(.*)&.*");
	std::smatch match;	
	std::regex_search(reply, match, tokensearch);
	if(match.size() > 1){
		client->authorize(successParam, match[1]);
		loginWindow->hide();
	}
}

void OAuth2::init(Authorized* client, Glib::ustring id=Glib::ustring()){
	this->client = client;
	this->app = Gtk::Application::create(id);	

	loginWindow = new Gtk::Window();
  loginWindow->set_default_size(800, 600);
	loginWindow->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	loginWindow->set_title("Authentication");

  page = WEBKIT_WEB_VIEW(webkit_web_view_new());
  
  pageContainer = Glib::wrap(GTK_WIDGET(page));

  loginWindow->add(*pageContainer);
  webkit_web_view_load_uri(page, loginEndpoint.c_str());
	
	g_signal_connect(page, "load-changed", G_CALLBACK(OAuth2::pageLoaded), this);
  loginWindow->show_all();
}


