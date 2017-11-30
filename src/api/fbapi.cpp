#include "fbapi.h"

/* Default variable values */
FbManager* FB::fbManager = NULL;
std::string FB::clientId = "109807839746371";
std::string FB::scope = "user_posts";

/* Specifies the client ID and scope used by the FB manager
	 A new connection will be created whenever the manager is reconfigured	
*/
void FB::configure(std::string clientId, std::string scope){
	FB::clientId = clientId;
	FB::scope = scope;
}

/* Retrieves the current FB manager. A new manager will be created
   if it does not yet exist.
*/
FbManager* FB::getManager(){
	if(FB::fbManager == NULL){
		fbManager = new FbManager(clientId, scope);
	}
	return fbManager;
}

/* Creates an FB manager using the given client ID and scope */
FbManager::FbManager(std::string clientId, std::string scope){
	this->clientId = clientId;
	this->scope = scope;
	apiVersion = "v2.10";
}

/* Remove unicode sequence from json string */
std::string FbManager::clean_json(std::string json){
   std::regex pattern("\\\\u[a-fA-F0-9]{4}");
   return std::regex_replace(json, pattern, " ");
}

/* Method called to add connection listeners that will be called after logging in to Facebook */
void FbManager::addConnectionListener(ConnectionListener* listener){
	connectionListeners.push_back(listener);
}

/* Method called after the user successfully logs in to Facebook */
void FbManager::authorize(std::string param, std::string value){
	accessToken = value;
	for(ConnectionListener* listener: connectionListeners){
		listener->loginSuccess();	
	}
}

/* Retrieves the access token generated after a successful login */
std::string FbManager::getAccessToken(){
	if(accessToken.empty())
		throw UnavailableAccessTokenException();
	else
		return accessToken;
}

/* Initiates the login proces using the OAuth2 protocol */
void FbManager::login(Glib::ustring id=Glib::ustring()){
	uri_builder login("https://www.facebook.com/" + apiVersion + "/dialog/oauth");
	login.append_query("client_id", clientId);
	login.append_query("response_type", "token");
	login.append_query("scope", scope);
	login.append_query("redirect_uri", "https://www.facebook.com/connect/login_success.html");
	auth = new OAuth2(login.to_string(), "access_token");
	auth->init(this, id);
}

/* Retrieves posts from the /me/feed Facebook endpoint */
std::vector<fbposts*> FbManager::getPosts(){
	http_client client(U("https://graph.facebook.com/v2.10"));
  uri_builder builder(U("/me/feed"));
	builder.append_query(U("access_token"), getAccessToken());
	builder.append_query(U("fields"),"message,story,id,description,created_time,attachments,type");
	std::vector<fbposts*> results;
  pplx::task<std::vector<fbposts*>> requestTask = client.request(methods::GET, builder.to_string()).then([&] (http_response response){
		std::string jsonStr = clean_json(response.extract_string().get());
		json::value json = json::value::parse(U(jsonStr));
		json::array data = json.at(U("data")).as_array();
		for (int i = 0; i<data.size(); i++) {
			std::string id = data[i].at(U("id")).as_string();
			std::string message = "";
			std::string att_imgsrc = "";
			std::string att_image = "";

			if (data[i].has_field("message")) {
				message = data[i].at(U("message")).as_string();
			}

			att_imgsrc = data[i].at(U("full_picture")).as_string();

			http_client imgclient(U(att_imgsrc));
			uri_builder imgbuilder(U(""));
			imgbuilder.append_query(U("access_token"), getAccessToken());

			if (FILE *file = fopen(("images/" + id + ".jpg").c_str(), "r")) {
				fclose(file);
				att_image = "images/" + id + ".jpg";
			}
			else {
				pplx::task<void> imgTask = imgclient.request(methods::GET, imgbuilder.to_string()).then([&](http_response response) {
					std::string img = response.extract_string(true).get();
					std::ofstream myfile;
					myfile.open("images/" + id + ".jpg");
					myfile << img;
					myfile.close();
					att_image = "images/" + id + ".jpg";
				});
				imgTask.wait();
			}

			fbposts* temp = new fbposts(id, att_imgsrc, att_image, message);
			results.push_back(temp);
		}
		return results;
  });
  return requestTask.get();
}
