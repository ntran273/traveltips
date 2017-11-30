main: main.cpp
	g++ main.cpp gui/fbpastpost.cpp gui/gui.cpp db/model.cpp db/db.cpp api/fbapi.cpp api/oauth2.cpp -o main -std=c++11 -lboost_system -lcrypto -lssl -lcpprest `pkg-config gtkmm-3.0 sqlite3 webkit2gtk-4.0 --cflags --libs`

clean:
	rm main
