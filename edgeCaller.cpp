
#include "edgeCaller.h"
#include <vector>

#include <stdlib.h>
#include "edgeapiclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <json/value.h>

using namespace jsonrpc;
using namespace std;


EdgeCaller::EdgeCaller(string url){
	this->targetUrl = url;
	cout << "EdgeCaller created" << endl;
}


string EdgeCaller::registerNode(string nodeUrl){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call registerNode (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.registerNode(nodeUrl);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_register"].asString();
}

string EdgeCaller::checkConnection(string check_messsage){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call checkConnection (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.checkConnection(check_messsage);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_connection"].asString();
}


string EdgeCaller::uploadFileMetadata(string nodeUrl, string metadata){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call uploadFileMetadata (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.uploadFileMetadata(nodeUrl, metadata);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_upload"].asString();
}


string EdgeCaller::downloadFileMetadata(string nodeUrl){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call downloadFileMetadata (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.downloadFileMetadata(nodeUrl);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["fileMetadata"].asString();
}


string EdgeCaller::confirmUploading(string confirm_message){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call confirmUploading (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.confirmUploading(confirm_message);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_confirm"].asString();
}

vector<string> EdgeCaller::getUrls(string callingNode) {
  vector<string> urls;

  HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
  Json::Value jsonValue;
	
	try{
		cout << "Call getUrls (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.getUrls(callingNode);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}

  
  for (int i = 0; i < 4; i++) {
    string url = jsonValue["node" + to_string(i+1)].toStyledString();
    url.erase(std::remove(url.begin(), url.end(), '"'), url.end());
    url.erase(std::remove(url.begin(), url.end(), '\n'), url.end());
    urls.push_back(url);
  }

  urls.erase(std::remove(urls.begin(), urls.end(), callingNode), urls.end());

	return urls;
}





