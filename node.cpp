
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
  private:
    vector<string> partFiles;
	public:
		NodeApiServer(AbstractServerConnector &connector, serverVersion_t type);
    virtual Json::Value checkConnection(const std::string& check_messsage);
    virtual Json::Value checkStorage(const std::string& check_messsage);
    virtual Json::Value uploadPartOfFile(const std::string& part_of_file);
    virtual Json::Value downloadFile(const std::string& download_message);
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


Json::Value NodeApiServer::uploadPartOfFile(const std::string& part_of_file){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "uploadPartOfFile called : " << part_of_file << endl;
	
	// Confirm Uploading
	EdgeCaller edgeCaller{edgeServerUrl};
	edgeCaller.confirmUploading("confirm uploading");

	// Return json
	string jsonStr = "{\"status_upload\": \"uploadPartOfFile successful\"}";
	

  //this->partFiles.push_back(part_of_file);

  if (find(begin(this->partFiles), end(this->partFiles), part_of_file) == end(this->partFiles)) {
    cout << "part_of_file " << part_of_file << " is uploaded" << endl;
	  // Push part_of_file into partFiles
	  this->partFiles.push_back(part_of_file);
  } else {
    jsonStr = "{\"status_upload\": \"uploadPartOfFile unsuccessful. This part of file has been already uploaded.\"}";
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



Json::Value NodeApiServer::downloadFile(const std::string& download_message){
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "downloadFile called : " << download_message << endl;


	// Return json
  Json::Value result;
	// string jsonStr = "{\"status_download\": \"downloadFile successful\"}";
	
	// Json::Value result;
	// Json::CharReaderBuilder builder;
	// Json::CharReader *reader = builder.newCharReader();
	// string errors;
	
	// bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &result, &errors);
	// delete reader;
	
	// if(!parsingSuccessful){
	// 	cout << "Failed to parse the Json, errors:" << endl;
	// 	cout << errors << endl;
	// }

  result["status_download"] = "downloadFile successful";
  result["part_of_file"] = this->partFiles[0];
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
			edgeCaller.uploadFileMetadata("http://127.0.0.1:" + to_string(port), "{file metadata}");

      // Let's assume we have nodes with the port 9001, 9002, 9003, 9004

      cout << "----------Step 4 happens in edge server----------" << endl;
      // Checking the connection and storage of all other nodes by edge server
      // If successful, we'll get the other node urls from edge server's returnings

      vector<string> urls = edgeCaller.getUrls("http://127.0.0.1:" + to_string(port));

      cout << "----------Step 5: Upload part(s) of file to all other nodes----------" << endl;
      cout << "call uploadPartOfFile" << endl;

      NodeCaller nodeCaller1{"http://127.0.0.1:" + to_string(port)};
      NodeCaller nodeCaller2{urls[0]};
      NodeCaller nodeCaller3{urls[1]};
      NodeCaller nodeCaller4{urls[2]};

      nodeCaller1.uploadPartOfFile("{upload part1 of file}");
			nodeCaller2.uploadPartOfFile("{upload part2 of file}");
			nodeCaller3.uploadPartOfFile("{upload part3 of file}");
      nodeCaller4.uploadPartOfFile("{upload part4 of file}");
		}
		else if(operation == 2){
      cout << "----------Step 2: Check the edge server connection----------" << endl;
			edgeCaller.checkConnection("connection check test");

      cout << "----------Step 3: Download the file metadata to the current node----------" << endl;
			string fileMetadata = edgeCaller.downloadFileMetadata("http://127.0.0.1:" + to_string(port));
			cout << "The fileMetadata is downloaded: " << fileMetadata << endl;

      // Let's assume we have nodes with the port 9001, 9002, 9003, 9004

      cout << "----------Step 4 happens in edge server----------" << endl;
      // Checking the connection and storage of all other nodes by edge server
			// If successful, we'll get the other node urls, hash value of file, sequence of parts and etc from edge server's returning

      cout << "Get URLs of nodes: " << endl;
      vector<string> urls = edgeCaller.getUrls("http://127.0.0.1:" + to_string(port));

      cout << "----------Step 5: Download other parts of file from all other nodes----------" << endl;
      cout << "call downloadFile" << endl;

      NodeCaller nodeCaller2{urls[0]};
      NodeCaller nodeCaller3{urls[1]};
      NodeCaller nodeCaller4{urls[2]};

			nodeCaller2.downloadFile("download file");
      nodeCaller3.downloadFile("download file");
      nodeCaller4.downloadFile("download file");
		}
		else if(operation == 3){
			break;
		}
	}
	
	
	nodeServer.StopListening();
	return 0;
}


