
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
#include "nodeapiserver.h"
#include "edgeCaller.h"
#include "nodeCaller.h"


using namespace jsonrpc;
using namespace std;


// global properties
string edgeServerUrl = "http://127.0.0.1:8080";


class NodeApiServer : public nodeApiServer{
	public:
		NodeApiServer(AbstractServerConnector &connector, serverVersion_t type);
		
        	virtual Json::Value checkConnection(const std::string& test);
        	virtual Json::Value checkStorage(const std::string& test);
        	virtual Json::Value uploadPartOfFile(const std::string& test);
        	virtual Json::Value downloadFile(const std::string& test);
};


NodeApiServer::NodeApiServer(AbstractServerConnector &connector, serverVersion_t type) : nodeApiServer(connector, type){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "NodeApiServer created" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
}


Json::Value NodeApiServer::checkConnection(const std::string& test){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "checkConnection called : " << test << endl;

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


Json::Value NodeApiServer::checkStorage(const std::string& test){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "checkStorage called : " << test << endl;


	// Return json
	string jsonStr = "{\"test\": \"checkStorage successful\"}";
	
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


Json::Value NodeApiServer::uploadPartOfFile(const std::string& test){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "uploadPartOfFile called : " << test << endl;
	
	
	// Confirm Uploading
	EdgeCaller edgeCaller{edgeServerUrl};
	edgeCaller.confirmUploading("confirm uploading");
	
	

	// Return json
	string jsonStr = "{\"test\": \"uploadPartOfFile successful\"}";
	
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



Json::Value NodeApiServer::downloadFile(const std::string& test){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "downloadFile called : " << test << endl;


	// Return json
	string jsonStr = "{\"test\": \"downloadFile successful\"}";
	
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
	
	EdgeCaller edgeCaller{edgeServerUrl};
	
	
	// Start the server
	cout << "Please input the port where you'd like to start your node server: " << endl;
	int port;
	cin >> port;
	getchar();
	
	HttpServer httpserver(port);
	NodeApiServer nodeServer(httpserver, JSONRPC_SERVER_V1V2);

	nodeServer.StartListening();
	edgeCaller.registerNode("http://127.0.0.1:" + to_string(port));
	
	while(true){
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Please choose operation (1. upload, 2.download, 3. stop server): " << endl;
		int operation;
		cin >> operation;
		getchar();

		if(operation == 1){
		 	// The url I pass in is this node's url for edge server to skip the storage-checking of process-triggering node.
			edgeCaller.checkConnection("connection check test");
			edgeCaller.uploadFile("http://127.0.0.1:" + to_string(port));
			
			// If successful, we'll get the other node urls from edge server's returning
			// Here I temporarily assume it's 8082
			cout << "call uploadPartOfFile" << endl;
			NodeCaller nodeCaller{"http://127.0.0.1:8082"};
			nodeCaller.uploadPartOfFile("upload file");
			
			
		}
		else if(operation == 2){
			edgeCaller.checkConnection("connection check test");
			edgeCaller.downloadFile("http://127.0.0.1:" + to_string(port));
			
			// If successful, we'll get the other node urls, hash value of file, sequence of parts and etc from edge server's returning
			NodeCaller nodeCaller{"http://127.0.0.1:8082"};
			nodeCaller.downloadFile("download file");			
		}
		else if(operation == 3){
			break;
		}
	}
	
	
	nodeServer.StopListening();
	return 0;
}


