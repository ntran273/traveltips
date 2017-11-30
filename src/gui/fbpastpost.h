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

#ifndef FBPASTPOST_H
#define FBPASTPOST_H
#include "gui.h"
#include <map>
#include <vector>
#include "../db/model.h"
#include "../db/db.h"
#include "../api/fbapi.h"

// A widget created to represent a post in the Posts window. It is actually a VBox with other widgets
// embedded in it. See fbpastpost.cpp for more details.
class PostWidget : public Gtk::VBox {
	private:
		std::string id;
		Gtk::HBox* remember_container;
		Gtk::Label* remember_label;
		Gtk::Separator* title_separator;
		Gtk::Label* title;
		Gtk::Label* timestamp;
		Gtk::Switch* remember;
		Gtk::Image* image;
		Gtk::Label* message;
		Gtk::Separator* post_separator;
		Post* post;
	public:
    PostWidget(Post*);
		std::string getId();
		std::string getTitle();
		std::string getImage();
		std::string getMessage();
		Post* getPost();
		void toggleSwitch();
};

// LoginController extends ViewController to associat it with start_window specified in the Glade file
class LoginController: public ViewController, public ConnectionListener {
	public: 
		// Required constructor that expects as parameters the Glade application manager, name of the window in the
		// Glade file (start_window), and whether it is a top level window or not.
		LoginController(GladeAppManager*, std::string, bool);		
		// Required method called when the x button on the window is clicked
		bool clickClose(GdkEventAny*);
		// Additional method used to simulate a login
		void login();
		// Method called by the FB manager when it has logged in properly. This is FBListener's virtual method declared in
		// fbapi.h
		void loginSuccess();
};

class PostController: public ViewController {
	private:
		// A link to the Box in Glade that will contain posts
		Gtk::Box* posts_container;
		// A link to the Box in Glade that will contain remembered posts
		Gtk::Box* remembered_posts_container;
		// A Hashmap containing PostWidget objects. The id of the post is used as index so we can easily
		// relate Post objects to PostWidget objects
		std::map<std::string, PostWidget*> posts;
		// A Hashmap containing PostWidget objects. The id of the post is used as index so we can easily
		// relate remembered Post objects to PostWidget objects
		std::map<std::string, PostWidget*> rememberedPosts;
	public:
		// Required constructor that expects as parameters the Glade application manager, name of the window in the
		// Glade file (posts_window), and whether it is a top level window or not.
		PostController(GladeAppManager*, std::string, bool);
		// Required method called when the x button on the window is clicked
		bool clickClose(GdkEventAny*);
		// Additional method called to add a new post to the window
		void addPost(Post*);
		// Additional method called to add a new remembered post to the window
		void addRememberedPost(Post*);
		// Additional method called when the refresh button is clicked
		void refresh();
		// Additional method called when the remembered post's refresh button is clicked
		void rememberedRefresh();
};

#endif
