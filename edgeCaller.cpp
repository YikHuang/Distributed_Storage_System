
#include "edgeCaller.h"
#include <vector>

#include <stdlib.h>
#include "edgeapiclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>


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


string EdgeCaller::uploadFile(string nodeUrl){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call uploadFile (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.uploadFile(nodeUrl);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_upload"].asString();
}


string EdgeCaller::downloadFile(string nodeUrl){
	
	HttpClient httpclient((this->targetUrl).c_str());
	edgeApiClient edgeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call downloadFile (" << this->targetUrl << ")" << endl;
		jsonValue = edgeApi.downloadFile(nodeUrl);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_download"].asString();
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





