# Required libraries
The api files require a couple of libraries to run; specifically webkitgtk2 and cpprest. You can install the necessary files by using the commands below.

## Ubuntu
    sudo apt-get install libgtkmm-3.0-dev libwebkit2gtk-4.0-dev libcpprest-dev

# Compilation
You will need to make sure that the compiler has access to the libraries when you compile the code. Below is an example showing how you might link the libraries to compile a file called driver.cpp that contains code utilizing the api

    g++ driver.cpp -o driver -std=c++11 -lboost_system -lcrypto -lssl -lcpprest `pkg-config gtkmm-3.0 webkit2gtk-4.0 --cflags --libs`
