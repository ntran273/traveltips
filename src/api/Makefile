#driver: driver.cpp oauth2.cpp
#	g++ oauth2.cpp driver.cpp -o driver -std=c++11 -lboost_system -lcrypto -lssl -lcpprest `pkg-config gtkmm-3.0 webkit2gtk-4.0 --cflags --libs`

driver: driver.cpp oauth2.cpp
	g++ oauth2.cpp driver.cpp fbapi.cpp -o driver -std=c++11 -lboost_system -lcrypto -lssl -lcpprest `pkg-config gtkmm-3.0 webkit2gtk-4.0 --cflags --libs`

clean:
	rm driver
