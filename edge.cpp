// For Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>


// For Json-rpc-cpp
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// General
#include <string>
#include <map>
#include <regex>
#include <vector>
#include <algorithm>
#include <iostream>

// External
#include "edgeapiserver.h"
#include "nodeCaller.h"


using namespace jsonrpc;
using namespace std;





class EdgeApiServer : public edgeApiServer{
	private:
		vector<string> nodeUrls;

	public:
		EdgeApiServer(AbstractServerConnector &connector, serverVersion_t type);
		
		virtual Json::Value registerNode(const std::string& nodeUrl);		// Record url of nodes, so we can access the node when we are trying to do the check, download or confirm
        	virtual Json::Value checkConnection(const std::string& test);
        	virtual Json::Value uploadFile(const std::string& nodeUrl);
        	virtual Json::Value downloadFile(const std::string& nodeUrl);
        	virtual Json::Value confirmUploading(const std::string& test);
};


EdgeApiServer::EdgeApiServer(AbstractServerConnector &connector, serverVersion_t type) : edgeApiServer(connector, type){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "EdgeApiServer created" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
}


Json::Value EdgeApiServer::registerNode(const std::string& nodeUrl){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "registerNode called" << endl;
	
	// Todo
	// Push node url into nodeUrls
	this->nodeUrls.push_back(nodeUrl);
	
	// Return json
	string jsonStr = "{\"test\": \"registerNode successful\"}";
	
	Json::Value result;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	string errors;
	
	bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &result, &errors);
	delete reader;
	
	if(!parsingSuccessful){
		cout << "Failed to parse the Json, errors:" << endl;
		cout << errors << endl;
	}
	cout << "--------------------------------------------------------------------------------" << endl;	
	
	return result;	

}

Json::Value EdgeApiServer::checkConnection(const std::string& test){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "checkConnection called" << endl;
	
	
	// Return json
	string jsonStr = "{\"test\": \"check successful\"}";
	
	Json::Value result;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	string errors;
	
	bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &result, &errors);
	delete reader;
	
	if(!parsingSuccessful){
		cout << "Failed to parse the Json, errors:" << endl;
		cout << errors << endl;
	}
	cout << "--------------------------------------------------------------------------------" << endl;	
	
	return result;	

}



Json::Value EdgeApiServer::uploadFile(const std::string& nodeUrl){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "uploadFile called" << endl;
	

	// Check Connection & Storage
	for(int i = 0; i < this->nodeUrls.size(); i++){
		// Skip the node that triggers this check connection process
		if(nodeUrl != nodeUrls[i]){
			NodeCaller nodecaller{nodeUrls[i]};
			nodecaller.checkConnection("node connection check");
			nodecaller.checkStorage("node storage check");
		}
	}
	
	
	// Return json
	string jsonStr = "{\"test\": \"uploadFile successful\"}";
	
	Json::Value result;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	string errors;
	
	bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &result, &errors);
	delete reader;
	
	if(!parsingSuccessful){
		cout << "Failed to parse the Json, errors:" << endl;
		cout << errors << endl;
	}
	cout << "--------------------------------------------------------------------------------" << endl;	
	
	return result;	

}


Json::Value EdgeApiServer::downloadFile(const std::string& nodeUrl){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "downloadFile called" << endl;


	// Check Connection & Storage
	for(int i = 0; i < this->nodeUrls.size(); i++){
		// Skip the node that triggers this check connection process
		if(nodeUrl != nodeUrls[i]){
			NodeCaller nodecaller{nodeUrls[i]};
			nodecaller.checkConnection("node connection check");
		}
	}


	// Return json
	string jsonStr = "{\"test\": \"download successful\"}";
	
	Json::Value result;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	string errors;
	
	bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &result, &errors);
	delete reader;
	
	if(!parsingSuccessful){
		cout << "Failed to parse the Json, errors:" << endl;
		cout << errors << endl;
	}
	cout << "--------------------------------------------------------------------------------" << endl;	
	
	return result;	
}


Json::Value EdgeApiServer::confirmUploading(const std::string& test){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "confirmUploading called : " << test << endl;


	// Return json
	string jsonStr = "{\"test\": \"confirm successful\"}";
	
	Json::Value result;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	string errors;
	
	bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &result, &errors);
	delete reader;
	
	if(!parsingSuccessful){
		cout << "Failed to parse the Json, errors:" << endl;
		cout << errors << endl;
	}
	cout << "--------------------------------------------------------------------------------" << endl;	
	
	return result;	
}


int main(){
	
	// Start the server
	HttpServer httpserver(8080);
	EdgeApiServer edgeServer(httpserver, JSONRPC_SERVER_V1V2);

	edgeServer.StartListening();
	cout << "Hit enter to stop the server" << endl;
	
	// End the server
	getchar();
	edgeServer.StopListening();
	
	return 0;

}






