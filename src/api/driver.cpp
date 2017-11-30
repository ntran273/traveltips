#include <cpprest/http_client.h>
#include <cpprest/uri.h>  
#include "oauth2.h"
#include <iostream>
#include "fbapi.h"

using namespace web; 
using namespace web::http;
using namespace web::http::client; 

int main(){
	
	// store image -- requires #include <fstream>
	/*http_client client(U("https://scontent.xx.fbcdn.net/v/t15.0-10/p720x720/22638076_1993531180859552_6418083971032154112_n.jpg?oh=a9bec6155dc4cc437d22b9248a2b7d1b&oe=5AD77683"));
	uri_builder builder(U(""));
	builder.append_query(U("access_token"), "EAACEdEose0cBAA9YyikvRqd51kDv6ZAHiJZAIvxvgHA37jGwpZBI8ZADNaaM6AiK91FMzwUitZCP4ZBx94ZC06sKCve3s6CZAg3Qi50J95MB4ZCriNglpZALjxZBC2lilTmN6ws3ZARMqVgM7PZCfgi4TtdnAeLgrGvz7fIbR4iZAMQqA6uDiCWyMyMZBX4hsW0o1Xzdk0ZD");
	
	pplx::task<void> requestTask = client.request(methods::GET, builder.to_string()).then([] (http_response response){
			std::string img = response.extract_string(true).get();
			std::ofstream myfile;
			myfile.open ("temp.jpg");
			myfile << img;
			myfile.close();
  });
  requestTask.wait();*/
	
	FB::configure("109807839746371", "user_posts");
	FbManager* mgr = FB::getManager();
	mgr->getPosts();

	return 0;
}
