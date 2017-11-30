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

#ifndef FBPASTPOST
#define FBPASTPOST

#include "fbpastpost.h"
#include <iostream>

/** ViewController for the Login top level window **/
LoginController::LoginController(GladeAppManager* gapManager, std::string windowName, bool isTopLevel):ViewController(gapManager, windowName, isTopLevel){
	// Sets the size and position of the window
	window->set_title("FB Past Post");
	window->set_default_size(400, 300);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	// Assigns login() as handler for clicking on the login button
	Gtk::Button* pButton = nullptr;
  builder->get_widget("btn_fblogin", pButton);
	pButton->signal_clicked().connect( sigc::mem_fun(*this, &LoginController::login) );
	FbManager* mgr = FB::getManager();
	mgr->addConnectionListener(this);
}

void LoginController::login(){
	// Switch to the posts_window
	FbManager* mgr = FB::getManager();
	mgr->login(gapManager->getGtkApplication()->get_id());
}

void LoginController::loginSuccess(){
	gapManager->showView("posts_window");
}

bool LoginController::clickClose(GdkEventAny* evt){
	// Exit the GUI
	gapManager->exit();
	return false;
}

/** ViewController for the Posts window **/
PostController::PostController(GladeAppManager* gapManager, std::string windowName, bool isTopLevel):ViewController(gapManager, windowName, isTopLevel){

	// Sets the size and position of the window
	window->set_title("Posts");
	window->set_default_size(800, 600);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	// Associates the post_box Box in the Glade file to a pointer for later use
	posts_container = nullptr;
  builder->get_widget("post_box", posts_container);

	// Associates the post_box Box in the Glade file to a pointer for later use
	remembered_posts_container = nullptr;
  builder->get_widget("remember_post_box", remembered_posts_container);

	// Assigns refresh() as handler for clicking on the refresh button 
	Gtk::Button* pRefresh = nullptr;
  builder->get_widget("btn_refresh", pRefresh);
	pRefresh->signal_clicked().connect( sigc::mem_fun(*this, &PostController::refresh) );

	// Assigns remember_refresh() as handler for clicking on the remembered post refresh button 
	Gtk::Button* pRemRefresh = nullptr;
  builder->get_widget("btn_rem_refresh", pRemRefresh);
	pRemRefresh->signal_clicked().connect( sigc::mem_fun(*this, &PostController::rememberedRefresh) );
}

void PostController::refresh(){
	// Place holder to API call that will create Post objects for each Facebook post retrieved.
	// Each post is sent to addPost so it is shown on the GUI

	FbManager* mgr = FB::getManager();
	std::vector<Post*> results = mgr->getPosts();
	for(Post* p : results){
		addPost(p);	
	}
}

void PostController::rememberedRefresh(){
	// Place holder to API call that will create Post objects for each Facebook post retrieved.
	// Each post is sent to addPost so it is shown on the GUI
	//remembered_posts_container
	std::vector<Post*> posts = PostLoader::getPosts();
	for(auto post: rememberedPosts){
			remembered_posts_container->remove(*(post.second));
	}
	rememberedPosts.clear();
	for(Post* p : posts){
		addRememberedPost(p);	
	}
}

void PostController::addPost(Post* post){
	if(posts.count(post->getId())==0){ // add post if has not been added yet
		// Creates a PostWidget object associated with a Post. All values of the Post are used for the display
		PostWidget* p = Gtk::manage(new PostWidget(post));
		// Stores the PostWidget object for reference
		posts[post->getId()] = p;
		// Adds the PostWidget object into the post_box designed in the Glade file
		posts_container->add(*p);
	}

}

void PostController::addRememberedPost(Post* post){
	if(rememberedPosts.count(post->getId())==0){ // add post if has not been added yet
		// Creates a PostWidget object associated with a Post. All values of the Post are used for the display
		PostWidget* p = Gtk::manage(new PostWidget(post));
		// Stores the PostWidget object for reference
		rememberedPosts[post->getId()] = p;
		// Adds the PostWidget object into the post_box designed in the Glade file
		remembered_posts_container->add(*p);
	}

}

bool PostController::clickClose(GdkEventAny* evt){
	// Switch the view to the login window when the x button is clicked
	gapManager->showView("start_window");
	return false;
}

/** Widget to represent Facebook posts **/
//PostWidget::PostWidget(std::string id, std::string titleText, std::string imageLoc, std::string messageText){
PostWidget::PostWidget(Post* p){
	post = p;
	// Create widgets that will be added into a Box widget.
	remember_label = new Gtk::Label("Remember");
	remember = new Gtk::Switch(); // on/off switch
	remember->set_active(p->isRemembered());
	remember->property_active().signal_changed().connect(sigc::mem_fun(*this, &PostWidget::toggleSwitch));
	title_separator = new Gtk::Separator(Gtk::ORIENTATION_VERTICAL);
	title = new Gtk::Label(p->getTitle(), Gtk::ALIGN_START);
	// Creates another (horizontal) box that contains the title label and switch
  remember_container = new Gtk::HBox();
	// Add the switch and label into the box
	remember_container->pack_start(*remember_label, false, false, 5);
	remember_container->pack_start(*remember, false, false, 5);
	remember_container->pack_start(*title_separator, false, false, 5); 
	remember_container->pack_start(*title, true, true, 5);
	// Creates other widgets
	timestamp = new Gtk::Label(p->getTimestamp(), Gtk::ALIGN_START);
	message = new Gtk::Label(p->getMessage(), Gtk::ALIGN_START);
	
	// Add all widgets into the main Box
	pack_start(*remember_container, true, true);
	pack_start(*timestamp, true, true, 5);

	if(!p->getImage().empty()){
		image = new Gtk::Image(p->getImage());
		image->set_halign(Gtk::ALIGN_START);
		pack_start(*image, true, true, 5);
	}

	pack_start(*message, true, true, 5);
	post_separator = new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL);
	pack_start(*post_separator, true, true, 5);

	// Tell GTK to refresh the GUI so as to show all added components
	show_all();
}

// getters and setters
std::string PostWidget::getId(){
	return id;
}

std::string PostWidget::getTitle(){
	return title->get_text();
}

std::string PostWidget::getImage(){
	//retrieve image here
	return "";
}

std::string PostWidget::getMessage(){
	return message->get_text();
}

Post* PostWidget::getPost(){
	return post;
}

void PostWidget::toggleSwitch(){
	if(!remember->get_active()){
		post->setRemembered(false);
		post->remove();	
	}else if(remember->get_active()){
		post->setRemembered(true);
		post->save();	
	}
}

#endif
