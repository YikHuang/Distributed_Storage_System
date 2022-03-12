
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


Json::Value NodeApiServer::checkConnection(const std::string& check_messsage){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "checkConnection called : " << check_messsage << endl;

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


Json::Value NodeApiServer::checkStorage(const std::string& check_messsage){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "checkStorage called : " << check_messsage << endl;

	// Return json
	string jsonStr = "{\"storage_status\": \"checkStorage successful\"}";
	
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


Json::Value NodeApiServer::uploadPartOfFile(const std::string& upload_message){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "uploadPartOfFile called : " << upload_message << endl;
	
	
	// Confirm Uploading
	EdgeCaller edgeCaller{edgeServerUrl};
	edgeCaller.confirmUploading("confirm uploading");
	
	

	// Return json
	string jsonStr = "{\"status_upload\": \"uploadPartOfFile successful\"}";
	
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



Json::Value NodeApiServer::downloadFile(const std::string& download_message){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "downloadFile called : " << download_message << endl;


	// Return json
	string jsonStr = "{\"status_download\": \"downloadFile successful\"}";
	
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
	
	// Start the client
	cout << "Please input the port where you'd like to start your node server: " << endl;
  Json::Value result;
  int port;

  cout << "----------Step 1: Register the node----------" << endl;
	while (true) {
    cin >> port;
    getchar();
    result = edgeCaller.registerNode("http://127.0.0.1:" + to_string(port));
    if (result == "registerNode successful") {  
      break;
    }
  }
  HttpServer httpserver(port);
  NodeApiServer nodeServer(httpserver, JSONRPC_SERVER_V1V2);
  nodeServer.StartListening();

	while(true){
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Please choose operation (1. upload, 2.download, 3. exit): " << endl;
		int operation;
		cin >> operation;
		getchar();

		if(operation == 1){
      cout << "----------Step 2: Check the edge server connection----------" << endl;
			edgeCaller.checkConnection("connection check test");

      cout << "----------Step 3: Upload the file metadata to edge server----------" << endl;
			edgeCaller.uploadFile("http://127.0.0.1:" + to_string(port));

      // Let's assume we have nodes with the port 9001, 9002, 9003, 9004

      cout << "----------Step 4 happens in edge server----------" << endl;
      // Checking the connection and storage of all other nodes by edge server
      // If successful, we'll get the other node urls from edge server's returnings

      cout << "----------Step 5: Upload part(s) of file to all other nodes----------" << endl;
      cout << "call uploadPartOfFile" << endl;
      NodeCaller nodeCaller2{"http://127.0.0.1:9002"};
      NodeCaller nodeCaller3{"http://127.0.0.1:9003"};
      NodeCaller nodeCaller4{"http://127.0.0.1:9004"};

			nodeCaller2.uploadPartOfFile("upload part of file");
			nodeCaller3.uploadPartOfFile("upload part of file");
      nodeCaller4.uploadPartOfFile("upload part of file");
		}
		else if(operation == 2){
      cout << "----------Step 2: Check the edge server connection----------" << endl;
			edgeCaller.checkConnection("connection check test");

      cout << "----------Step 3: Download the file metadata to the current node----------" << endl;
			edgeCaller.downloadFile("http://127.0.0.1:" + to_string(port));
			
      // Let's assume we have nodes with the port 9001, 9002, 9003, 9004

      cout << "----------Step 4 happens in edge server----------" << endl;
      // Checking the connection and storage of all other nodes by edge server
			// If successful, we'll get the other node urls, hash value of file, sequence of parts and etc from edge server's returning

      cout << "----------Step 5: Download other parts of file from all other nodes----------" << endl;
      cout << "call downloadFile" << endl;
			NodeCaller nodeCaller{"http://127.0.0.1:" + to_string(port)};
			nodeCaller.downloadFile("download file");			
		}
		else if(operation == 3){
			break;
		}
	}
	
	
	nodeServer.StopListening();
	return 0;
}


