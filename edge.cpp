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
    vector<string> fileMetadata;

	public:
		EdgeApiServer(AbstractServerConnector &connector, serverVersion_t type);
		
		virtual Json::Value registerNode(const std::string& nodeUrl);		// Record url of nodes, so we can access the node when we are trying to do the check, download or confirm
    virtual Json::Value checkConnection(const std::string& test);
    virtual Json::Value uploadFileMetadata(const std::string& nodeUrl, const std::string& metadata);
    virtual Json::Value downloadFileMetadata(const std::string& nodeUrl);
    virtual Json::Value confirmUploading(const std::string& test);
    virtual Json::Value getUrls(const std::string& callingNode);
};


EdgeApiServer::EdgeApiServer(AbstractServerConnector &connector, serverVersion_t type) : edgeApiServer(connector, type){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "EdgeApiServer created" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
}


Json::Value EdgeApiServer::registerNode(const std::string& nodeUrl) {
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "registerNode called" << endl;
	
  // Return json
	string jsonStr = "{\"status_register\": \"registerNode successful\"}";

	// Todo
  if (find(begin(this->nodeUrls), end(this->nodeUrls), nodeUrl) == end(this->nodeUrls)) {
    cout << "Node on " << nodeUrl << " is registered" << endl;
	  // Push node url into nodeUrls
	  this->nodeUrls.push_back(nodeUrl);
  } else {
    jsonStr = "{\"status_register\": \"registerNode unsuccessful. The URL is occupied. Please enter a new one.\"}";
  }
  
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

Json::Value EdgeApiServer::checkConnection(const std::string& nodeUrl){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "checkConnection called" << endl;
	
	
	// Return json
	string jsonStr = "{\"status_connection\": \"check successful\"}";
	


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



Json::Value EdgeApiServer::uploadFileMetadata(const std::string& nodeUrl, const std::string& metadata){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "uploadFileMetadata called" << endl;
	

  cout << "----------Step 4: Check nodes connection and storage by edge server---------" << endl;
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
	string jsonStr = "{\"status_upload\": \"uploadFileMetadata successful\"}";
	
  if (find(begin(this->fileMetadata), end(this->fileMetadata), metadata) == end(this->fileMetadata)) {
    cout << metadata << " is uploaded" << endl;
	  // Push metadata to fileMetadata
	  this->fileMetadata.push_back(metadata);
  } else {
    jsonStr = "{\"status_register\": \"registerNode unsuccessful. The URL is occupied. Please enter a new one.\"}";
  }

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


Json::Value EdgeApiServer::downloadFileMetadata(const std::string& nodeUrl){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "downloadFileMetadata called" << endl;

  cout << "----------Step 4: Check nodes connection and storage by edge server---------" << endl;
	// Check Connection & Storage
	for(int i = 0; i < this->nodeUrls.size(); i++){
		// Skip the node that triggers this check connection process
		if(nodeUrl != nodeUrls[i]){
			NodeCaller nodecaller{nodeUrls[i]};
			nodecaller.checkConnection("node connection check");
		}
	}


	// Return json
	string jsonStr = "{\"fileMetadata\": \"" + (this->fileMetadata)[0] + "\"}";
	
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


Json::Value EdgeApiServer::confirmUploading(const std::string& confirm_message){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "confirmUploading called : " << confirm_message << endl;


	// Return json
	string jsonStr = "{\"status_confirm\": \"confirm successful\"}";
	
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


Json::Value EdgeApiServer::getUrls(const std::string& callingNode){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "getUrls called from: " << callingNode << endl;

  // Return json
	Json::Value result;

  for(int i = 0; i < this->nodeUrls.size(); i++){
    result["node" + to_string(i+1)] = nodeUrls[i];
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






