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

#include "fbpastpost.h"
#include <iostream>

int main(){
	// Create the Glade application manager
	GladeAppManager gapManager("fbpastpost.glade"); 

	// Create the login and post controllers (see code in fbpastpost.cpp) and pass the Glade application manager, 
	// name of the associated window in Glade, and if it is the top level window. The top level window is
	// the first window opened. The application exits whenever it is closed. There should only be 1 top level window.
	// In cases when multiple top level windows are defined, the last one is set as the top level window.
	LoginController lc(&gapManager, "start_window", true); 
	PostController pc(&gapManager, "posts_window", false);

	// Start the GUI
	gapManager.start();

	// Start will run while the GUI is displayed. Statements after the call to start will only run after the
	// GUI closes

}

