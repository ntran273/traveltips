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

#ifndef GUI_H
#define GUI_H

#include <exception>
#include <gtkmm.h>
#include <gdkmm/event.h>
#include <map>

/* Exceptions */
class TopLevelWindowException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Top-level window has not been set";
  }
};

class BuilderRetrievalException : public std::exception {
	virtual const char* what() const throw(){
		return "Builder has not been assigned by the GladeAppManager via addViewController";
	}
};

class GladeAppManagerRetrievalException : public std::exception {
	virtual const char* what() const throw(){
		return "GladeAppManager has not yet been assigned via addViewController";
	}
};

class WindowRetrievalException : public std::exception {
	virtual const char* what() const throw(){
		return "Window has not yet been assigned via addViewController";
	}
};

class GladeAppManager;

class ViewController {
	protected:
		Glib::RefPtr<Gtk::Builder> builder;
		std::string windowName;
		Gtk::Window* window;
		GladeAppManager* gapManager;
	public:
		ViewController(GladeAppManager*, std::string, bool);
		std::string getWindowName(){ return windowName; };
		Gtk::Window* getWindow(){ return window; };
		virtual bool clickClose(GdkEventAny*) = 0;
};

class GladeAppManager {
	private:
		Glib::RefPtr<Gtk::Application> app;
		Glib::RefPtr<Gtk::Builder> builder;
		std::map<std::string, ViewController*> views;
		std::string topLevelWindow;
		std::string currWindow;
		bool isHeld;
	public:
		GladeAppManager(std::string);
		Glib::RefPtr<Gtk::Builder> getBuilder();
		Glib::RefPtr<Gtk::Application> getGtkApplication();
		void addViewController(ViewController*);
		void addViewController(ViewController*, bool);
		void showView(std::string);
		void start();
		void exit();
};

#endif
