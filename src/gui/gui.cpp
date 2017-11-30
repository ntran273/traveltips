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

#include "gui.h"
#include <iostream>

GladeAppManager::GladeAppManager(std::string gladeFile){
  app =  Gtk::Application::create();
	builder = Gtk::Builder::create_from_file(gladeFile);
	isHeld = false;
}

Glib::RefPtr<Gtk::Builder> GladeAppManager::getBuilder(){
	return builder;
}

Glib::RefPtr<Gtk::Application> GladeAppManager::getGtkApplication(){
	return app;
}

void GladeAppManager::addViewController(ViewController* controller){
	addViewController(controller, false);
}

void GladeAppManager::addViewController(ViewController* controller, bool isTopLevel){
	if(isTopLevel){
		topLevelWindow = controller->getWindowName();
		currWindow = topLevelWindow;
	}
	views[controller->getWindowName()] = controller;
}

void GladeAppManager::showView(std::string windowName){
	if(!isHeld && currWindow == topLevelWindow){
		app->hold();
		isHeld = true;
	}

	views[windowName]->getWindow()->set_visible(true);
	currWindow = windowName;

	for(auto v: views){
		if(v.first !=windowName){
			v.second->getWindow()->set_visible(false);		
		}	
	}
}

void GladeAppManager::start(){
	if(!topLevelWindow.empty())
		app->run(*views[topLevelWindow]->getWindow());
	else
		throw TopLevelWindowException();
}
void GladeAppManager::exit(){
	views[topLevelWindow]->getWindow()->set_visible(false);
	if(isHeld)	
		app->release();
}

ViewController::ViewController(GladeAppManager* gapManager, std::string windowName, bool isTopLevel=false){
	this->windowName = windowName;
	this->gapManager = gapManager;
	gapManager->addViewController(this, isTopLevel);
	builder = gapManager->getBuilder();
	builder->get_widget(windowName, this->window);
	this->window->signal_delete_event().connect( sigc::mem_fun(this, &ViewController::clickClose) );
}
