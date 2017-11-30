driver: driver.cpp fbposts.cpp
	g++ driver.cpp fbposts.cpp db.cpp -o driver -std=c++11 `pkg-config sqlite3 --cflags --libs`

clean:
rm driver
